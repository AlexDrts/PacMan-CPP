<div align="center">

# 👾 PacMan-CPP

**Classic Pac-Man reimagined as a Windows console game in C++**

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=flat-square&logo=windows&logoColor=white)
![Visual Studio](https://img.shields.io/badge/Visual%20Studio-5C2D91?style=flat-square&logo=visualstudio&logoColor=white)

</div>

<img width="100%" alt="photo_2026-10-24_23-13-29" src="https://github.com/user-attachments/assets/f07fddab-ecff-4bcf-bfa6-4c66f10d28ea" />

## 🎮 Gameplay

Guide Pac-Man (`C`) through the maze, collect every coin (`.`) and avoid the ghosts (`O`).

- 🟡 Collect all coins to **win**
- 👻 Ghosts chase you — if one catches you, it's **game over**
- 🔁 Exit the left or right edge to wrap around to the other side
- 🎵 Background music and a death sound effect
- 🪙 Live coin counter next to the map

### Controls

| Key | Action |
|---|---|
| `←` `→` `↑` `↓` | Move |
| `Esc` | Quit |

## 🧩 Under the hood

- **OOP:** abstract base class `GameObject` with a virtual `Draw()`, inherited by `Hero` and `Enemy`
- **Game loop** with fixed tick rate and non-blocking keyboard input (`_kbhit` / `_getch`)
- **Ghost AI:** each ghost moves toward the player and avoids walls
- **Map** is built from a text layout (`#` wall, `.` coin, `E` ghost) into a dynamic 2D array
- **Console rendering** with WinAPI: cursor positioning, colors, hidden cursor — only changed cells are redrawn
- **Sound** played on a separate thread via `PlaySound` (winmm)
- Strongly typed `enum class` for tiles, colors and keys

## 📁 Project structure

```
├── main.cpp                  # Entry point, game loop, input
├── project_02.10.2025.h      # Enums, Position, GameObject / Hero / Enemy / Game declarations
├── project_02.10.2025.cpp    # Game logic: map, movement, ghosts, win / lose
├── Entities.cpp              # Hero and Enemy rendering
├── music.cpp                 # Background music thread
├── layout.h                  # Level layout
└── *.wav                     # Music and sound effects
```

## 🚀 How to run

> Windows only (uses WinAPI and `conio.h`)

1. Clone the repository
2. Open `project_02.10.2025.sln` in **Visual Studio**
3. Press **F5** (or **Ctrl + F5**)

Keep the `.wav` files next to the executable so the sounds play.

---

<div align="center">

Made by [Alex](https://github.com/AlexDrts) 🌸

