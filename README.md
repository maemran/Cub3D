# 🧊 Cub3D

![42 Project](https://img.shields.io/badge/42%20Project-Cub3D-purple)
![Language](https://img.shields.io/badge/Made%20with-C-00599C?logo=c)
![Graphics](https://img.shields.io/badge/Graphics-MiniLibX-green)
![Status](https://img.shields.io/badge/Status-Finished-brightgreen)

---

## 🎮 About the Project

**Cub3D** is a **first-person 3D game** inspired by **Wolfenstein 3D**.  
It uses a technique called **Raycasting** to transform a **2D map** into a **3D world**.

This project teaches:
- Computer graphics & rendering 🖥️
- Math behind projections 📐
- Handling input (keyboard/mouse) 🎮
- Efficient algorithms & optimization 🚀

---

## 🧠 Technical Concepts

### 🔷 Raycasting (How we create the 3D world)
Raycasting sends imaginary **rays** from the player’s camera field of view.  
Each ray:
- Moves forward step-by-step
- Stops when it hits a wall
- Measures distance to that wall

📌 **Closer walls** look **bigger**,  
📌 **Farther walls** look **smaller**.

This creates the illusion of 3D from a 2D grid ✅

---

### 📏 DDA Algorithm (Digital Differential Analyzer)

To detect collisions efficiently, we use **DDA**, which:
- Steps ray **grid cell by grid cell**
- Checks **only necessary positions**
- Avoids expensive per-pixel calculations

✅ Ensures:
- **Smooth performance**
- **Fast wall detection**
- **Accurate rendering**

---

### 🗺️ Map Rules

The `.cub` file contains:
- Wall textures
- Floor & ceiling colors
- Map layout

Example:

111111
100001
1000N1
111111


✅ Map requirements:
- Must be **fully closed** by walls (`1`)
- Only **one player** start position (N, S, E, W)
- Valid characters:
  - `1` → Wall  
  - `0` → Empty space  
  - `N S E W` → Player spawn + direction  
  - Space allowed as padding (but boundaries must still be walls)

❌ If the map is invalid → Program exits with an error

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| W / A / S / D | Move forward / left / backward / right |
| ← / → | Rotate view direction |
| ESC | Exit the game |

Smooth movement and rotation for a realistic FPS feeling 🎮

---

## 🛠️ Installation & Execution

### 📌 Compile

```bash
make

