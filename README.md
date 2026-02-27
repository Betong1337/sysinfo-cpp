# sysinfo-cpp

## REFACTOR IN PROGRSS

I'm refactoring the whole project to work on windows and mac aswell. So if you want to use the linux version you can
download find it under `sysinfo-linux` in this repo.

**sysinfo-cpp** is a lightweight system information tool written in C++, inspired by fastfetch but with a simpler implementation. It displays system information in the terminal and can also show ASCII-art depending on your Linux distribution.

## Features

- Display information about the operating system, kernel, CPU, GPU, RAM, disk, swap, uptime, hostname, and user.  
- Easy integration of ASCII-art for different distributions.  
- Simple to contribute with your own distributions.  
- Minimal and fast, with no external dependencies.

![Description of image](https://i.imgur.com/XKxbnTh.png)

## Commands

| Command       | Description |
|---------------|------------|
| `--os`        | Display operating system |
| `--kernel`    | Display kernel version |
| `--cpu`       | Display CPU information |
| `--gpu`       | Display GPU information |
| `--ram`       | Display RAM status |
| `--disk`      | Display disk usage |
| `--swap`      | Display swap usage |
| `--uptime`    | Display system uptime |
| `--hostname`  | Display the computer's hostname |
| `--username`  | Display the current user |
| `--version` / `-v` | Display program version (v0.1) |

If an invalid command is provided, a usage message will be displayed.

## ASCII-art

The program can display ASCII-art based on your Linux distribution.

- If no specific ASCII-art is available, `"Linux"` will be shown.  
- To add your own distribution:
  1. Find or create ASCII-art using a website like [ASCII Art Generator](https://www.ascii-art.de/) or similar.  
  2. Copy the result into a text file.  
  3. Name the file with the distribution name, capitalized (e.g., `Ubuntu.txt` or `Fedora.txt`).  
  4. Place the file in `src/asciiart/`.

The program will automatically display the new ASCII-art when running. Contributions with more ASCII-art distributions are welcome!

## Compile / Build

To compile sysinfo-cpp:

1. Open a terminal and navigate to the project folder.
2. When in the project folder write: `make`.
3. `./sysinfo` to run.

## License

This project is licensed under the **MIT License**.