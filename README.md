# MySuperMario
# Mario Game Project

A 2D platformer game inspired by classic Super Mario World gameplay, developed in **C++** using the **Raylib** framework.  
This project was created to demonstrate Object-Oriented Programming (OOP) principles, game physics, collision handling, and user interface design.

---

## 📜 Features

- **Multiple Game Modes**
  - Single-player and two-player support
- **Character Selection**
  - 5 characters to choose
- **Gameplay Mechanics**
  - Smooth movement, jumping, ducking, and running
  - Power-ups and collectible items
  - Enemy AI with unique movement patterns
  - Boss fights
- **Physics & Collision**
  - Directional hitbox collision detection
  - Tile-based spatial partitioning for optimized performance
- **Save & Load System**
  - Multi-slot save files using JSON serialization
- **Level Selection**
  - Map selection menu with multiple stages
- **Map Editor**
  - Create and edit custom levels

---

## 🛠️ Technologies Used

- **Language:** C++
- **Graphics Library:** [Raylib](https://www.raylib.com/)
- **Data Storage:** JSON (via [nlohmann/json](https://github.com/nlohmann/json))
- **Design Patterns:**
  - State Pattern (Menu System)
  - Command Pattern (Input Handling)
  - Flyweight Pattern (Resource Management)
  - Mediator Pattern (Collision Handling)
  - Singleton Pattern (Game Manager)
  - Factory Pattern (Entity Creation)
- **Build System:** CMake

---

## 🚀 Installation & Setup

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/mario-game.git
   cd mario-game
