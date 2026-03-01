@echo off

if exist sysinfo (
    echo Updating repository...
    cd sysinfo
    git pull
) else (
    echo Cloning repository...
    git clone https://github.com/Betong1337/sysinfo.git
    cd sysinfo
)

echo Building...
make

if exist sysinfo.exe (
    echo Running...
    sysinfo.exe
) else (
    echo Build failed.
)

pause