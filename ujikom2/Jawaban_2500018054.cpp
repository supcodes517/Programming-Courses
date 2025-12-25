// ============================================
// NAMA   : Erwin Agustiansyah muhammad said
// NIM    : 2500018054
// QUIZ   : Quiz Pangkat (quiz_pangkat.cpp)
// TANGGAL: 25/12/2025
// ============================================

#include <iostream>
using namespace std;

/**
 * Fungsi rekursif untuk menghitung pangkat
 * Contoh: 2^3 = 2 * 2 * 2
 */
int hitungPangkat(int x, int y) {
    // ? KESALAHAN 1: Base case salah. Bilangan pangkat 0 harusnya menghasilkan 1.
    // SEBELUM: if (y == 0) return 0;
    // PERBAIKAN:
    if (y == 0) { 
        return 1; // ? DIPERBAIKI: Semua bilangan (kecuali 0) pangkat 0 adalah 1
    }

    // ? KESALAHAN 2: Operasi rekursif salah. Pangkat adalah perkalian berulang.
    // SEBELUM: return x + hitungPangkat(x, y - 1);
    // PERBAIKAN:
    return x * hitungPangkat(x, y - 1); // ? DIPERBAIKI: Menggunakan tanda (*) bukan (+)
}

int main() {
    int basis, eksponen;

    cout << "=== PROGRAM PANGKAT REKURSIF ===" << endl;
    cout << "Masukkan angka basis: ";
    cin >> basis;
    cout << "Masukkan angka pangkat (eksponen): ";
    cin >> eksponen;

    // ? KESALAHAN 3: Kondisi validasi input negatif salah.
    // SEBELUM: if (eksponen > 0)
    // PERBAIKAN:
    if (eksponen < 0) { // ? DIPERBAIKI: Mengecek jika eksponen negatif karena rekursi ini untuk bilangan bulat positif
        cout << "Error: Eksponen tidak boleh negatif!" << endl;
    } else {
        cout << "Hasil dari " << basis << " pangkat " << eksponen << " adalah: ";
        cout << hitungPangkat(basis, eksponen) << endl;
    }

    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base case y == 0 menghasilkan 0, diperbaiki menjadi 1 agar hasil perkalian benar.
// 2. Operator dalam rekursi menggunakan (+) yang seharusnya perkalian (*) untuk fungsi pangkat.
// 3. Logika percabangan di main() diperbaiki untuk menangkap input eksponen negatif.
// ============================================
