# Tic Tac Toe - Base Code for Final Project

## 📋 Deskripsi
Ini adalah base code untuk Proyek Akhir Mata Kuliah Dasar Pemrograman.
Program Tic Tac Toe console-based dengan C++ yang menggunakan array 2D.

## ✨ Fitur Base Code
- Array 2D untuk board game (3x3)
- Mode VS Player (2 pemain)
- Mode VS Komputer (AI sederhana)
- Validasi input
- Deteksi kemenangan (baris, kolom, diagonal)
- Deteksi seri/draw
- Option untuk main lagi

## 🎯 Tugas Mahasiswa
Modifikasi program ini dengan menambahkan:

### 1. Sistem Player dengan Struct (25%)
```cpp
struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};
```
### 2. Sistem Scoring (25%)
Menang: +3 poin
Seri: +1 poin
Kalah: +0 poin

### 3. File Management (25%) 
Simpan data player ke players.txt
Load data player dari file
Update data setelah permainan
tutorial: https://github.com/supcodes517/Programming-Courses/blob/main/tictactoe/TUTORIAL_FILE_IO.md 

### 4. Menu Pemilihan Player (25%)
Player baru
Pilih player yang sudah ada
Lihat leaderboard
Keluar

## Expected result pada file ini: 
https://github.com/supcodes517/Programming-Courses/blob/main/tictactoe/EXPECTED%20RESULT.md 

## PENGUMPULAN
### Menggunakan Git Branch
Clone repository ini
Buat branch dengan format: NIM_project
Modifikasi code di branch tersebut
Commit dan push ke branch Anda

### Struktur pengumpulan
```
tictactoe/
├── tictactoe.cpp          # File utama (modified)
├── players.txt            # Data player
├── README.md              # Dokumentasi Anda
└── screenshots/           # (Opsional)
    ├── menu.png
    ├── gameplay.png
    └── leaderboard.png
```

