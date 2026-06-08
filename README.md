# 🧩 Procedural Maze Lab: Godot & C++ Hybrid

<!-- ![C++](https://img.shields.io/badge/C++-00599C?logo=c%2B%2B&logoColor=white) -->
![Godot Engine](https://img.shields.io/badge/Godot-478CBF?logo=godotengine&logoColor=white)
<!-- ![GDScript](https://img.shields.io/badge/GDScript-355570?logo=godotengine&logoColor=white) -->
<!-- ![SCons](https://img.shields.io/badge/SCons-LightGrey?logo=python&logoColor=black) -->

## 📖 About
**Procedural Maze Lab** is a high-performance maze generation tool built to demonstrate the power of hybrid game architecture. The project delegates heavy algorithmic calculations to a **C++** (via GDExtension), while leveraging **Godot 4's** rendering, UI, and input systems using GDScript.

This approach ensures absolute optimal performance even for massive grid sizes, completely decoupling the generation logic from the main game thread. It features live animated generation, dynamic controls, and interactive camera navigation.

## 🛠 Tech Stack
* **Game Engine:** Godot 4.6
* **Core Logic:** Modern C++ (GDExtension)
* **Visualisation:** GDScript
* **Build System:** SCons
* **Compiler:** MSVC / GCC

## ✨ Technical Highlights & Features

### ⚙️ Hybrid C++ / Godot Architecture
* **GDExtension Integration:** Heavy generation algorithms are written in C++ and compiled into a dynamic library (`.dll`/`.so`), natively hooked into Godot without the overhead of inter-process communication.
* **Strategy Design Pattern:** The algorithms are abstracted behind a `MazeStrategy` interface. This allows seamless switching between different generation logics at runtime, keeping the codebase strictly adherent to the Open-Closed Principle (OCP).
* **Modern C++ Memory Safety:** Engineered using `std::vector` and Smart Pointers (`std::unique_ptr`), ensuring zero memory leaks during continuous procedural generation.
* **Single Responsibility Principle (SRP):** Clean codebase separation between UI controllers, camera controllers, and the C++ wrapper.

### 🧵 Multithreading & Live Animation
* **Non-Blocking UI:** Maze generation runs entirely on Godot's `WorkerThreadPool`. The UI remains fully responsive even when calculating complex algorithms on large grids.
* **Live Step-by-Step Rendering:** The C++ backend records the generation history, allowing the GDScript frontend to animate the maze-carving process in real-time.
* **Dynamic Speed Control:** Users can adjust the animation delay on-the-fly using the UI slider.

### 🕹️ Interactive Features & Algorithms
* **Interchangeable Generation Algorithms:**
  * **Randomized Depth-First Search (DFS):** Utilizes stack-based backtracking to carve "perfect mazes" (guaranteed single path between any two points without loops).
  * **Cellular Automata:** Uses neighbor-counting rules and smoothing iterations to generate organic, natural-looking cave formations.
* **Custom Camera System:** Built-in Pan & Zoom mechanics allowing players to smoothly navigate and inspect massive mazes.

## 🎮 Controls

| Action | Input |
| :--- | :--- |
| **Pan Camera (Drag)** | `Right Mouse Button` or `Middle Mouse Button` |
| **Zoom In / Out** | `Mouse Scroll Wheel` |

## 🚀 Quick Start

### 1. Prerequisites
* [Godot Engine 4.x](https://godotengine.org/)
* C++ Compiler (Visual Studio / MinGW / GCC)
* [Python & SCons](https://scons.org/) (For compiling the C++ library)

### 2. Clone & Compile
```bash
git clone https://github.com/OsherBerGit/Procedural-Maze-Lab.git
cd Procedural-Maze-Lab
scons
```

*(Note: Compiling is required to build the GDExtension library for your OS).*

### 3. Run the Project
* Open Godot Engine.
* Click **Import** and select the `client/project.godot` file.
* Press **F5** to run the scene, configure your maze settings in the sidebar, and click **Generate!**

### 📁 Project Structure
```text
📦 Procedural-Maze-Lab
├── 📂 src/              # C++ Source Code
│   ├── 📂 core/         # Maze Generation Algorithms & Types
│   └── 📂 gdextension/  # Godot API Wrapper & Method Bindings
├── 📂 client/           # Godot Project Root
│   ├── 📂 bin/          # Compiled C++ shared libraries (.dll/.so)
│   ├── 📂 scenes/       # Godot Scenes (UI, Main)
│   ├── 📂 scripts/      # GDScript files (Camera, UI, Main Logic)
│   └── 📂 assets/       # Tilemaps & Sprites
└── 📜 SConstruct        # Build configuration for SCons
```

---
### 🎨 Credits
*Pixel art textures and tilesets provided by piiixl.itch.io.*