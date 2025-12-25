#include <iostream>
using namespace std;

// ============================================
// NAMA   : Hanif Nur Faizi
// NIM    : 2500018024
// QUIZ   : Quiz 3 – Penjumlahan Rekursif
// TANGGAL: 25/12/2025
// ============================================

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    // ❌ KESALAHAN 1: Operasi salah (perkalian)
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    if (n == 1) {
        return 1;
    }
    return n + jumlah(n - 1);   // ✅ DIPERBAIKI
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;

    // ❌ KESALAHAN 2: Pemanggilan fungsi salah
    // SEBELUM: jumlah(angka - 1)
    // PERBAIKAN:
    cout << "Jumlah dari 1 hingga " << angka
         << " adalah: " << jumlah(angka) << endl;   // ✅ DIPERBAIKI

    return 0;
}

// ============================================
// RINGKASAN KESALAHAN:
// 1. Operasi perkalian (*) → diperbaiki menjadi penjumlahan (+)
// 2. Argumen fungsi (angka - 1) → diperbaiki menjadi (angka)
// ============================================
