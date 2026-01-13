# Expected Result

## Skenario 1: First Time Run (Belum Ada Data Player)
Output:
```
================================
     TIC TAC TOE GAME
================================

File player tidak ditemukan.  Membuat file baru... 

=== MENU UTAMA ===
1. Player Baru
2. Pilih Player yang Sudah Ada
3. Lihat Leaderboard
4. Keluar

Pilihan Anda: 1

=== REGISTRASI PLAYER BARU ===
Masukkan nama Anda: Budi

Player baru berhasil dibuat! 
Selamat datang, Budi! 

Statistik Anda:
- Total Games: 0
- Wins: 0
- Draws: 0
- Losses: 0
- Total Score: 0

Tekan Enter untuk melanjutkan...
```

## Skenario 2: Gameplay - Player VS Komputer (MENANG)
Output:
```
================================
     TIC TAC TOE GAME
================================

Panduan Posisi:
 1 | 2 | 3
---|---|---
 4 | 5 | 6
---|---|---
 7 | 8 | 9


   |   |  
---|---|---
   |   |  
---|---|---
   |   |  

Giliran Anda (X)
Masukkan posisi (1-9): 5

 X |   |  
---|---|---
   | X |  
---|---|---
   |   |  

Komputer sedang berpikir... 
Komputer memilih posisi:  1

 O |   |  
---|---|---
   | X |  
---|---|---
   |   |  

Giliran Anda (X)
Masukkan posisi (1-9): 9

 O |   |  
---|---|---
   | X |  
---|---|---
   |   | X

Komputer sedang berpikir... 
Komputer memilih posisi:  3

 O |   | O
---|---|---
   | X |  
---|---|---
   |   | X

Giliran Anda (X)
Masukkan posisi (1-9): 7

 O |   | O
---|---|---
   | X |  
---|---|---
 X |   | X

Komputer sedang berpikir... 
Komputer memilih posisi: 8

 O |   | O
---|---|---
   | X |  
---|---|---
 X | O | X

Giliran Anda (X)
Masukkan posisi (1-9): 4

 O |   | O
---|---|---
 X | X |  
---|---|---
 X | O | X

Komputer sedang berpikir... 
Komputer memilih posisi: 6

 O |   | O
---|---|---
 X | X | O
---|---|---
 X | O | X

Giliran Anda (X)
Masukkan posisi (1-9): 2

 O | X | O
---|---|---
 X | X | O
---|---|---
 X | O | X

🎉 ANDA MENANG! 🎉

================================
       HASIL PERTANDINGAN
================================
Hasil:  MENANG
Score yang didapat: +3 poin

Statistik Budi:
- Total Games: 1
- Wins: 1
- Draws: 0
- Losses: 0
- Total Score: 3

Data telah disimpan ke file players. txt

Main lagi? (y/n): y
```

## Skenario 3: Gameplay - Player VS Komputer (SERI)
Output:
```
================================
     TIC TAC TOE GAME
================================

Panduan Posisi:
 1 | 2 | 3
---|---|---
 4 | 5 | 6
---|---|---
 7 | 8 | 9


   |   |  
---|---|---
   |   |  
---|---|---
   |   |  

Giliran Anda (X)
Masukkan posisi (1-9): 5

   |   |  
---|---|---
   | X |  
---|---|---
   |   |  

Komputer sedang berpikir...
Komputer memilih posisi: 1

 O |   |  
---|---|---
   | X |  
---|---|---
   |   |  

[...  gameplay berlanjut ...]

 O | X | X
---|---|---
 X | X | O
---|---|---
 O | O | X

SERI! Tidak ada yang menang. 

================================
       HASIL PERTANDINGAN
================================
Hasil: SERI
Score yang didapat: +1 poin

Statistik Budi:
- Total Games:  2
- Wins: 1
- Draws: 1
- Losses: 0
- Total Score: 4

Data telah disimpan ke file players.txt

Main lagi? (y/n): y
```

## Skenario 4: Gameplay - Player VS Komputer (KALAH)
Output:
```
================================
     TIC TAC TOE GAME
================================

Panduan Posisi:
 1 | 2 | 3
---|---|---
 4 | 5 | 6
---|---|---
 7 | 8 | 9


   |   |  
---|---|---
   |   |  
---|---|---
   |   |  

Giliran Anda (X)
Masukkan posisi (1-9): 1

 X |   |  
---|---|---
   |   |  
---|---|---
   |   |  

Komputer sedang berpikir...
Komputer memilih posisi: 5

 X |   |  
---|---|---
   | O |  
---|---|---
   |   |  

[... gameplay berlanjut ...]

 X | X | O
---|---|---
   | O |  
---|---|---
 O |   |  

💻 KOMPUTER MENANG! 💻

================================
       HASIL PERTANDINGAN
================================
Hasil: KALAH
Score yang didapat: +0 poin

Statistik Budi:
- Total Games:  3
- Wins: 1
- Draws: 1
- Losses: 1
- Total Score: 4

Data telah disimpan ke file players.txt

Main lagi? (y/n): n
```

## Skenario 5: Gameplay - Player VS Player
Output:
```
=== PILIH MODE PERMAINAN ===
1. VS Player
2. VS Komputer

Pilihan Anda: 1

Mode VS Player dipilih!
Player 1: X
Player 2: O

Tekan Enter untuk memulai... 

================================
     TIC TAC TOE GAME
================================

Panduan Posisi:
 1 | 2 | 3
---|---|---
 4 | 5 | 6
---|---|---
 7 | 8 | 9


   |   |  
---|---|---
   |   |  
---|---|---
   |   |  

Giliran Player X
Masukkan posisi (1-9): 5

   |   |  
---|---|---
   | X |  
---|---|---
   |   |  

Giliran Player O
Masukkan posisi (1-9): 1

 O |   |  
---|---|---
   | X |  
---|---|---
   |   |  

[... gameplay berlanjut ...]

 O |   | X
---|---|---
   | X |  
---|---|---
 X |   | O

🎉 Player X MENANG! 🎉

================================
       HASIL PERTANDINGAN
================================
Hasil untuk Budi: MENANG
Score yang didapat: +3 poin

Statistik Budi:
- Total Games: 4
- Wins: 2
- Draws: 1
- Losses: 1
- Total Score: 7

Data telah disimpan ke file players.txt

Main lagi? (y/n): n
```

## Skenario 6: Pilih Player yang Sudah Ada
Output:
```
================================
     TIC TAC TOE GAME
================================

=== MENU UTAMA ===
1. Player Baru
2. Pilih Player yang Sudah Ada
3. Lihat Leaderboard
4. Keluar

Pilihan Anda: 2

=== DAFTAR PLAYER ===
No | Nama           | Score | Games | W  | D  | L
---|----------------|-------|-------|----|----|---
1  | Budi           |  36   |  16   | 11 | 3  | 2
2  | Ani            |  25   |  12   | 8  | 1  | 3
3  | Citra          |  17   |  9    | 5  | 2  | 2
4  | Doni           |  15   |  8    | 4  | 3  | 1
5  | Eka            |  12   |  7    | 3  | 3  | 1

Pilih player (1-5) atau 0 untuk kembali: 2

Player dipilih:  Ani

Selamat datang kembali, Ani! 

Statistik Anda:
- Total Games: 12
- Wins: 8
- Draws: 1
- Losses: 3
- Total Score: 25

Tekan Enter untuk melanjutkan...
```

## Skenario 7: Lihat Leaderboard
Output:
```
================================
     TIC TAC TOE GAME
================================

=== MENU UTAMA ===
1. Player Baru
2. Pilih Player yang Sudah Ada
3. Lihat Leaderboard
4. Keluar

Pilihan Anda: 3

================================
        LEADERBOARD
  Top 10 Players by Score
================================

Rank | Nama           | Score | Games | W  | D  | L  | 
-----|----------------|-------|-------|----|----|----|
  1  | Budi           |  36   |  16   | 11 | 3  | 2  | 
  2  | Ani            |  25   |  12   | 8  | 1  | 3  |  
  3  | Citra          |  17   |  9    | 5  | 2  | 2  | 
  4  | Doni           |  15   |  8    | 4  | 3  | 1  | 
  5  | Eka            |  12   |  7    | 3  | 3  | 1  | 
  6  | Fajar          |  10   |  6    | 3  | 1  | 2  | 
  7  | Gita           |   8   |  5    | 2  | 2  | 1  | 
  8  | Hendra         |   7   |  4    | 2  | 1  | 1  | 
  9  | Indah          |   6   |  4    | 2  | 0  | 2  | 
 10  | Joko           |   4   |  3    | 1  | 1  | 1  | 

================================

Tekan Enter untuk kembali ke menu...
```

## Summary Output Requirements
✅ Yang HARUS Ada:
- [] Menu Utama dengan 4 pilihan
- [] Registrasi Player Baru - input nama
- [] Pemilihan Player Lama - list player + pilih
- [] Leaderboard - top 10 sorted by score
- [] Pilihan Mode Game - VS Player atau VS Komputer
- [] Panduan Posisi - numbering 1-9
- [] Display Board - dengan format grid ASCII
- [] Giliran Player - jelas siapa yang main
- [] Komputer Thinking - message saat komputer berpikir
- [] Hasil Akhir - Menang/Seri/Kalah dengan emoji
- [] Update Score - tampilkan score yang didapat
- [] Statistik Player - games, wins, draws, losses, score
- [] Konfirmasi Save - notifikasi data tersimpan
- [] Main Lagi? - opsi untuk bermain lagi
- [] Input Validation - error handling untuk semua input
- [] Exit Message - pesan perpisahan
