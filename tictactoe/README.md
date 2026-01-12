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

### 2. Sistem Scoring (15%)
- Menang: +3 poin
- Seri: +1 poin  
- Kalah: +0 poin

### 3. File Management (25%)
- Simpan data player ke `players.txt`
- Load data player dari file
- Update data setelah permainan

### 4. Menu Pemilihan Player (15%)
- Player baru
- Pilih player yang sudah ada
- Lihat leaderboard
- Keluar

### 5. Level Kesulitan AI (20%)
- **Easy**: Random moves
- **Medium**: Block player, random otherwise
- **Hard**: Full AI strategy (sudah ada di base code)

## 🔧 Cara Compile dan Run

```bash
# Compile
g++ tictactoe.cpp -o tictactoe

# Run (Windows)
tictactoe.exe

# Run (Mac/Linux)
./tictactoe
```

## 📦 Format Pengumpulan

### Menggunakan Git Branch
1. Clone repository ini
2. Buat branch dengan format: `NIM_project`
3. Modifikasi code di branch tersebut
4. Commit dan push ke branch Anda

```bash
# Clone repository
git clone https://github.com/supcodes517/Programming-Courses.git

# Masuk ke folder
cd Programming-Courses

# Buat branch dengan NIM Anda
git checkout -b 123456789_project

# Edit file
# ... kerjakan project ...

# Commit
git add .
git commit -m "Implementasi fitur X"

# Push
git push -u origin 123456789_project
```

### Atau Menggunakan VS Code
Lihat panduan lengkap di file dokumentasi proyek.

## 📁 Struktur Pengumpulan

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

## ⏰ Deadline
Lihat pengumuman dari dosen.

## 📧 Kontak
Jika ada pertanyaan, hubungi dosen pengampu.

## 📚 Resources
- [C++ Documentation](https://cplusplus.com/)
- [Git Documentation](https://git-scm.com/doc)
- [VS Code Git Guide](https://code.visualstudio.com/docs/sourcecontrol/overview)

---

**Good luck and happy coding! 🚀**