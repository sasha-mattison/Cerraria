# Cerraria

A 2D sandbox game implementation inspired by **Terraria**, written in **C++**.

![C++](https://img.shields.org/badge/C++-17%2F20-blue.svg)
![License](https://img.shields.org/badge/License-MIT-green.svg)
![Platform](https://img.shields.org/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)

---

## Overview

**Cerraria** is an open-source, 2D tile-based sandbox adventure game built in C++.

---

## Features

Nothin yet

---

## Tech Stack & Dependencies

- **Language:** C++17 or higher
- **Build System:** CMake (>= 3.15)
- **Graphics/Input/Audio Engine:** [Raylib](https://www.raylib.com/) (or SFML/SDL2 depending on configuration)
- **Compiler:** `gcc` (>= 9), `clang` (>= 10), or MSVC (Visual Studio 2019+)

---

## Getting Started

### Prerequisites

#### Linux (Debian / Ubuntu)

```bash
sudo apt update
sudo apt install build-essential cmake libraylib-dev libx11-dev libxi-dev libgl1-mesa-dev

#### MacOS 

```bash
brew update && upgrade
brew install glm freetype glfw assimp cmake