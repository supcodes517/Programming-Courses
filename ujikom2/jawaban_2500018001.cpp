// ============================================
// NAMA  :  [Muhammad Arif Rahman]
// NIM   :  [2500018001]
// QUIZ  :  [Penjumlahan]
// TANGGAL: [24/12/2025]
// ============================================

#include <iostream>
using namespace std;

int jumlah(int n) {
    // ❌ KESALAHAN 1: Base case salah - seharusnya n == 0 return 0, bukan n == 1 return 1
    // SEBELUM: if (n == 1) return 1;
    // PERBAIKAN: 
    if (n == 0) {
        return 0;
    } // ✅ DIPERBAIKI

    // ❌ KESALAHAN 2: Operasi salah - harus perkalian (+), bukan perkalian (*)
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    return n + jumlah(n - 1); // ✅ DIPERBAIKI
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // ❌ KESALAHAN 3: Argumen pada pemanggilan fungsi salah - seharusnya angka, bukan angka - 1
    // SEBELUM: jumlah(angka - 1);
    // PERBAIKAN:
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl; // ✅ DIPERBAIKI
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base Case Salah: Seharusnya menggunakan if (n == 0) return 0 agar fungsi berhenti dengan benar saat mencapai angka nol.
// 2. Operasi Rekursi Salah: Menggunakan operator perkalian (*) padahal tujuan fungsi adalah untuk melakukan penjumlahan (+).
// 3. Kesalahan Argumen di Main: Pemanggilan fungsi jumlah(angka - 1) menyebabkan hasil tidak menyertakan angka terakhir yang diinput user, seharusnya jumlah(angka).
// ============================================