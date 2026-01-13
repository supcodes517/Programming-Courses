# Tic Tac Toe Game

**Author:** M Bisri Jhr Dodego 
**NIM:** 2500018045  
**Project:** Tic Tac Toe with Player Management, Scoring, and Leaderboard

---

## Deskripsi

Tic Tac Toe ini adalah game klasik dengan fitur tambahan:  

- Bisa dimainkan **VS Player** atau **VS Komputer**.  
- **Sistem Player** menggunakan `struct` untuk menyimpan data: nama, total games, menang, seri, kalah, dan skor.  
- **Sistem Scoring**:  
  - Menang: +3 poin  
  - Seri: +1 poin  
  - Kalah: +0 poin  
- Data player disimpan di `players.txt` agar bisa diload dan diupdate setiap bermain.  
- Menyediakan **Leaderboard Top 10** berdasarkan skor tertinggi.  

---

## Cara Menjalankan

1. Pastikan file `tictactoe.cpp` dan `players.txt` berada di folder yang sama.  
2. Compile program:  
   ```bash
   g++ tictactoe.cpp -o tictactoe