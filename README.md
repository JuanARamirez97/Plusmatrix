# Plusmatrix
A lightweight, terminal-based Matrix digital rain effect written in modern C++

`plusmatrix` simulates the iconic falling characters from The Matrix, featuring dynamic terminal resizing, customizable trail colors, frame-rate control, and a clean, low-latency rendering loop using the `ncurses` library.

## Features

* **Classic Visuals:** White "heads" with colored trailing characters.
* **Customizable Colors:** Change the rain color via command-line arguments.
* **Speed Control:** Fine-tune the animation speed by adjusting the frame delay in milliseconds.
* **Responsive:** Automatically handles terminal window resizing without breaking the visual grid.
* **Autocompletion:** Native Bash completion support integrated directly into the CMake installation.
* **Modern C++:** Built using C++20 standard and configured with a robust CMake pipeline.
* **Optimized:** Runs smoothly with minimal CPU usage.

## Prerequisites

To build and run `plusmatrix`, you need:
* A C++20 compatible compiler (e.g., GCC or Clang)
* CMake (3.15 or higher)
* The `ncurses` library development files

**Installing Dependencies:**

* **Fedora / Nobara / RHEL:**
```bash
sudo dnf install ncurses-devel cmake gcc-c++
```

* **Ubuntu / Debian / Pop!_OS:**
```bash
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev cmake g++
```

* **Arch Linux:**
```bash
sudo pacman -S ncurses cmake gcc
```

## Building and Installation

This project uses CMake for building. The recommended approach is to install it locally in your user's `~/.local/bin` directory.

1. **Clone the repository:**
```bash
git clone [https://github.com/JuanARamirez97/Plusmatrix.git](https://github.com/JuanARamirez97/Plusmatrix.git)
cd Plusmatrix
```

2. **Configure the project:**
Set the installation prefix to your local environment and enable release optimizations.
```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=~/.local -DCMAKE_BUILD_TYPE=Release
```
   
3. **Compile the binary:**
```bash
cmake --build build
```

4. **Install the executable:**
```bash
cmake --install build
```

*(Note: Ensure `~/.local/bin` is in your system's `$PATH`. The Bash autocompletion will take effect the next time you open a terminal or source your completion scripts).*

## Usage

Run the program directly from your terminal:
```bash
plusmatrix
```

**Change Colors (`-c`):**
You can customize the color of the digital rain.
```bash
plusmatrix -c cyan
```
*Available Colors:* `green` (Default), `red`, `blue`, `cyan`, `magenta`, `yellow`, `white`.

**Change Speed (`-f`):**
Set the frame delay in milliseconds. Lower numbers make the rain fall faster (Default is 25).
```bash
plusmatrix -f 15
```

**Help Menu (`-h` / `--help`):**
Show all available commands and options right in the terminal.
```bash
plusmatrix --help
```

**Exit:**
Press `q` or `Q` at any time to exit the program and clear the terminal.

## License
Distributed under the MIT License.