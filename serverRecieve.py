from flask import Flask, request

app = Flask(__name__)

@app.route("/server", methods=["POST"])
def server_info():
    data = request.json

    print("Received:")
    print(data)

    return {"status": "ok"}, 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)