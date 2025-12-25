// ============================================
// NAMA   : Ryan Dwi Nur Ikhsan
// NIM    : 2500018015
// QUIZ   : Penjumlahan
// TANGGAL: 25/12/2025
// ============================================

#include <iostream>
using namespace std;

int jumlah(int n) {
    // ? KESALAHAN 1: Base case nya kurang aman (hanya n == 1) diganti <= 1 karena takut ada yang masukin negatif atau nol
    // SEBELUM: if (n == 1) return 1;
    // PERBAIKAN:
    if (n <= 1) {                 // ? DIPERBAIKI
        return 1;
    }

    // ? KESALAHAN 2: Operasinya salah (perkalian) jadi * diganti +
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    return n + jumlah(n - 1);     // ? DIPERBAIKI
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;

    // ? KESALAHAN 3: Pemanggilan fungsi salah karena yang ke input ke n itu angka dikurangi 1, contohnya kalau masukin angka 3 malah jadinya 2+1 bukan 3+2+1
    // SEBELUM: jumlah(angka - 1)
    // PERBAIKAN:
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl; // ? DIPERBAIKI

    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base case hanya n == 1 ? diperbaiki menjadi n <= 1
// 2. Operasi perkalian (*) ? diperbaiki menjadi penjumlahan (+)
// 3. Pemanggilan fungsi angka - 1 ? diperbaiki menjadi angka
// ============================================

