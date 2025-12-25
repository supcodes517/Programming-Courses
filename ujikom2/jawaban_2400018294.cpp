// ============================================
// NAMA   : Betrand Erlangga
// NIM    : 2400018294
// QUIZ   : penjumlahan.cpp
// TANGGAL: 24/12/2025
// ============================================

#include <iostream>
using namespace std;

// Fungsi rekursif untuk menghitung penjumlahan dari 1 hingga n
int jumlah(int n) {
    // KESALAHAN 1: Base casenya sudah ada, tappi penjelasannya kurang jelas
    // SEBELUM: if (n == 1) return 1;
    // PERBAIKAN:
    if (n == 1) {  
        return 1;  // DIPERBAIKI: Jika n sama dengan 1, langsung dikembalikan 1 karena ini titik berhenti rekursi
    }

    // KESALAHAN 2: Pada kode awal memakai perkalian (*), padahal seharusnya penjumlahan
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    return n + jumlah(n - 1);  // DIPERBAIKI: Menambahkan n dengan hasil jumlah dari angka sebelumnya
}

int main() {
    int angka;

    // Buat pengguna memasukkan angka
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // KESALAHAN 3: Pemanggilan fungsi sebelumnya menggunakan jumlah(angka - 1) sehingga hasilnya kurang
    // SEBELUM: cout << jumlah(angka - 1);
    // PERBAIKAN:
    cout << "Jumlah dari 1 hingga " << angka << " adalah: "
         << jumlah(angka) << endl;  // DIPERBAIKI: Memanggil jumlah(angka) agar menghitung semua angka hingga input

    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base case sudah ada, tetapi penjelasannya kurang jelas → diperbaiki menjadi dijelaskan bahwa jika n == 1, rekursi berhenti dan mengembalikan 1
// 2. Operator perkalian (*) digunakan untuk menghitung jumlah → diperbaiki menjadi menggunakan operator penjumlahan (+) agar menghitung total penjumlahan
// 3. Pemanggilan fungsi jumlah(angka - 1) menyebabkan hasil penjumlahan tidak lengkap → diperbaiki menjadi jumlah(angka) agar semua angka dari 1 hingga input dijumlahkan
// ============================================
