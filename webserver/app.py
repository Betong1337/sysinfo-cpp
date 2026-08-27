from flask import Flask, request, render_template, redirect, url_for, jsonify
import sqlite3
from datetime import datetime, timezone

app = Flask(__name__)

DATABASE = "monitor.db"


# ---------------------------------------------------------
# Database
# ---------------------------------------------------------

def get_db():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn


def init_db():
    conn = get_db()

    conn.executescript("""
        CREATE TABLE IF NOT EXISTS servers (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            ip TEXT UNIQUE NOT NULL,
            hostname TEXT NOT NULL,
            uptime TEXT NOT NULL,
            disk TEXT NOT NULL,
            ram TEXT NOT NULL,
            swap TEXT NOT NULL DEFAULT 'Unknown',
            last_seen TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS services (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT UNIQUE NOT NULL,
            description TEXT DEFAULT ''
        );

        CREATE TABLE IF NOT EXISTS server_services (
            server_id INTEGER NOT NULL,
            service_id INTEGER NOT NULL,
            PRIMARY KEY (server_id, service_id),
            FOREIGN KEY (server_id) REFERENCES servers(id) ON DELETE CASCADE,
            FOREIGN KEY (service_id) REFERENCES services(id) ON DELETE CASCADE
        );
    """)

    columns = conn.execute(
        "PRAGMA table_info(servers)"
    ).fetchall()

    column_names = [column["name"] for column in columns]

    if "swap" not in column_names:
        conn.execute("""
            ALTER TABLE servers
            ADD COLUMN swap TEXT NOT NULL DEFAULT 'Unknown'
        """)

    conn.commit()
    conn.close()


# ---------------------------------------------------------
# Helpers
# ---------------------------------------------------------

def now():
    return datetime.now(timezone.utc)


def is_online(last_seen):
    last = datetime.fromisoformat(last_seen)

    # Heartbeat every 10 minutes.
    # Give the client 5 extra minutes before marking it offline.
    return (now() - last).total_seconds() < 15 * 60


def get_server_services(conn, server_id):
    return conn.execute("""
        SELECT services.*
        FROM services
        JOIN server_services
            ON services.id = server_services.service_id
        WHERE server_services.server_id = ?
        ORDER BY services.name
    """, (server_id,)).fetchall()


# ---------------------------------------------------------
# Dashboard
# ---------------------------------------------------------

@app.route("/")
def dashboard():
    conn = get_db()

    servers = conn.execute("""
        SELECT *
        FROM servers
        ORDER BY hostname
    """).fetchall()

    server_data = []

    for server in servers:
        services = get_server_services(conn, server["id"])

        server_data.append({
        "server": server,
        "services": services,
        "online": is_online(server["last_seen"]),
        "last_seen": time_ago(server["last_seen"])
        })

    conn.close()

    online_count = sum(1 for s in server_data if s["online"])

    return render_template(
        "dashboard.html",
        servers=server_data,
        total=len(server_data),
        online=online_count,
        offline=len(server_data) - online_count
    )


# ---------------------------------------------------------
# Server details
# ---------------------------------------------------------

@app.route("/server/<int:server_id>")
def server(server_id):
    conn = get_db()

    server = conn.execute("""
        SELECT *
        FROM servers
        WHERE id = ?
    """, (server_id,)).fetchone()

    if server is None:
        conn.close()
        return "Server not found", 404

    services = get_server_services(conn, server_id)

    conn.close()

    return render_template(
    "server.html",
    server=server,
    services=services,
    online=is_online(server["last_seen"]),
    last_seen=time_ago(server["last_seen"])
    )


# ---------------------------------------------------------
# C++ agent endpoint
# ---------------------------------------------------------

@app.route("/server", methods=["POST"])
def server_info():

    data = request.get_json(silent=True)

    if not data:
        return jsonify({
            "status": "error",
            "message": "Invalid JSON"
        }), 400

    required = [
        "hostname",
        "uptime",
        "disk",
        "ram",
        "swap"
    ]

    for field in required:
        if field not in data:
            return jsonify({
                "status": "error",
                "message": f"Missing field: {field}"
            }), 400

    hostname = str(data["hostname"])
    uptime = str(data["uptime"])
    disk = str(data["disk"])
    ram = str(data["ram"])
    swap = str(data["swap"])

    # IP of the machine sending the request
    ip = request.remote_addr

    timestamp = now().isoformat()

    conn = get_db()

    existing = conn.execute("""
        SELECT id
        FROM servers
        WHERE ip = ?
    """, (ip,)).fetchone()

    if existing:

        conn.execute("""
            UPDATE servers
            SET
            hostname = ?,
            uptime = ?,
            disk = ?,
            ram = ?,
            swap = ?,
            last_seen = ?
        WHERE ip = ?
        """, (
        hostname,
        uptime,
        disk,
        ram,
        swap,
        timestamp,
        ip
        ))

    else:

        conn.execute("""
            INSERT INTO servers (
                ip,
                hostname,
                uptime,
                disk,
                ram,
                swap,
                last_seen
            )
            VALUES (?, ?, ?, ?, ?, ?, ?)
            """, (
            ip,
            hostname,
            uptime,
            disk,
            ram,
            swap,
            timestamp
        ))

    conn.commit()
    conn.close()

    print(f"[+] Received data from {hostname} ({ip})")

    return jsonify({
        "status": "ok"
    }), 200

def time_ago(timestamp):
    last = datetime.fromisoformat(timestamp)

    if last.tzinfo is None:
        last = last.replace(tzinfo=timezone.utc)

    seconds = int((now() - last).total_seconds())

    if seconds < 60:
        return f"{seconds}s ago"

    minutes = seconds // 60

    if minutes < 60:
        return f"{minutes}m ago"

    hours = minutes // 60

    if hours < 24:
        return f"{hours}h {minutes % 60}m ago"

    days = hours // 24

    return f"{days}d {hours % 24}h ago"


# ---------------------------------------------------------
# Admin
# ---------------------------------------------------------

@app.route("/admin")
def admin():

    conn = get_db()

    servers = conn.execute("""
        SELECT *
        FROM servers
        ORDER BY hostname
    """).fetchall()

    services = conn.execute("""
        SELECT *
        FROM services
        ORDER BY name
    """).fetchall()

    server_data = []

    for server in servers:

        assigned = get_server_services(
            conn,
            server["id"]
        )

        server_data.append({
            "server": server,
            "services": assigned,
            "online": is_online(server["last_seen"])
        })

    conn.close()

    return render_template(
        "admin.html",
        servers=server_data,
        services=services
    )


# ---------------------------------------------------------
# Create service
# ---------------------------------------------------------

@app.route("/admin/service/create", methods=["POST"])
def create_service():

    name = request.form.get("name", "").strip()
    description = request.form.get(
        "description",
        ""
    ).strip()

    if not name:
        return redirect(url_for("admin"))

    conn = get_db()

    try:

        conn.execute("""
            INSERT INTO services (
                name,
                description
            )
            VALUES (?, ?)
        """, (
            name,
            description
        ))

        conn.commit()

    except sqlite3.IntegrityError:
        pass

    conn.close()

    return redirect(url_for("admin"))


# ---------------------------------------------------------
# Delete service
# ---------------------------------------------------------

@app.route("/admin/service/<int:service_id>/delete", methods=["POST"])
def delete_service(service_id):

    conn = get_db()

    conn.execute("""
        DELETE FROM server_services
        WHERE service_id = ?
    """, (service_id,))

    conn.execute("""
        DELETE FROM services
        WHERE id = ?
    """, (service_id,))

    conn.commit()
    conn.close()

    return redirect(url_for("admin"))


# ---------------------------------------------------------
# Assign service
# ---------------------------------------------------------

@app.route(
    "/admin/server/<int:server_id>/service",
    methods=["POST"]
)
def assign_service(server_id):

    service_id = request.form.get(
        "service_id",
        type=int
    )

    if service_id is None:
        return redirect(url_for("admin"))

    conn = get_db()

    try:

        conn.execute("""
            INSERT INTO server_services (
                server_id,
                service_id
            )
            VALUES (?, ?)
        """, (
            server_id,
            service_id
        ))

        conn.commit()

    except sqlite3.IntegrityError:
        # Already assigned
        pass

    conn.close()

    return redirect(url_for("admin"))


# ---------------------------------------------------------
# Remove service assignment
# ---------------------------------------------------------

@app.route(
    "/admin/server/<int:server_id>/service/<int:service_id>/remove",
    methods=["POST"]
)
def remove_service(server_id, service_id):

    conn = get_db()

    conn.execute("""
        DELETE FROM server_services
        WHERE server_id = ?
        AND service_id = ?
    """, (
        server_id,
        service_id
    ))

    conn.commit()
    conn.close()

    return redirect(url_for("admin"))


# ---------------------------------------------------------
# Delete server
# ---------------------------------------------------------

@app.route(
    "/admin/server/<int:server_id>/delete",
    methods=["POST"]
)
def delete_server(server_id):

    conn = get_db()

    conn.execute("""
        DELETE FROM server_services
        WHERE server_id = ?
    """, (server_id,))

    conn.execute("""
        DELETE FROM servers
        WHERE id = ?
    """, (server_id,))

    conn.commit()
    conn.close()

    return redirect(url_for("admin"))


# ---------------------------------------------------------
# API
# ---------------------------------------------------------

@app.route("/api/servers")
def api_servers():

    conn = get_db()

    servers = conn.execute("""
        SELECT *
        FROM servers
        ORDER BY hostname
    """).fetchall()

    result = []

    for server in servers:

        services = get_server_services(
            conn,
            server["id"]
        )

        result.append({
            "id": server["id"],
            "ip": server["ip"],
            "hostname": server["hostname"],
            "uptime": server["uptime"],
            "disk": server["disk"],
            "ram": server["ram"],
            "swap": server["swap"],
            "last_seen": server["last_seen"],
            "online": is_online(server["last_seen"]),
            "services": [
                service["name"]
                for service in services
            ]
        })

    conn.close()

    return jsonify(result)


# ---------------------------------------------------------
# Start
# ---------------------------------------------------------

if __name__ == "__main__":

    init_db()

    app.run(
        host="0.0.0.0",
        port=5000,
        debug=True
    )