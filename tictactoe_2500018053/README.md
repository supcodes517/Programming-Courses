# Tic Tac Toe - Base Code for Final Project

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue">
  <img src="https://img.shields.io/badge/Status-Completed-success">
</p>

Project ini menggunakan bahasa **C++**.
Mendukung **Sistem Player dengan Struct** dan **Sistem Scoring**, dengan sistem **File Management**, dan **Menu Pemilihan Player**.

## Requirements

* C++ Compiler (GCC / MinGW / Clang)
* OS: Windows / Linux / macOS
* Terminal / Command Prompt

## Installation

```bash
g++ main.cpp -o tictactoe
./tictactoe
```

Atau compile via IDE (Dev-C++, Code::Blocks, VS Code).

## Fitur Utama

* Menu utama (Player Baru, Pilih Player yang sudah ada, Lihat Leaderboard, dan Exit)
* Mode permainan:

  * VS Player
  * VS Computer
* Board yang menggunakan array 2D
* Sistem skor:

  * Win: +3
  * Draw: +1
  * Lose: 0
* Statistik player:

  * Total Games
  * Wins
  * Draws
  * Losses
  * Total Score
* Auto save ke `players.txt` setiap game selesai

## File Structure

```
tictactoe_2500018053/
├── tictactoe.cpp          # File utama (modified)
├── players.txt            # Data player
├── README.md              # Dokumentasi
└── screenshots/           
    ├── menu.png
    ├── gameplay.png
    ├── leaderboard.png
    ├── seri.png
    ├── menang.png
    └── player win.png
```

**Author:** misuminitt / Muhammad Ridwan Kusumahani
