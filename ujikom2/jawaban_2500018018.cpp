// =====================================
// NAMA     : Fathir Aryoseto
// NIM      : 2500018018
// QUIZ     : Penjumlahan
// TANGGAL  : 25/12/2025
// =====================================

#include <iostream>
using namespace std;

int jumlah(int n) {
    if (n == 1) {  
        return 1;
    }
    // KESALAHAN 1: Menggunakan tanda '*' yang perupakan faktorial, seharusnya '+'
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    return n + jumlah(n - 1);  
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    cout << "Jumlah dari 1 hingga " << angka 
    // KESALAHAN 2: Pemanggilan fungsi jumlah salah
    // SEBELUM: jumlah(angka - 1)
    // PERBAIKAN:
         << " adalah: " << jumlah(angka) << endl;  
    
    return 0;
}

// =========================================================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Operasi perkalian ('*') > diganti menjadi penjumlahan ('+') 
// 2. Pemanggilan fungsi jumlah(angka - 1) > diganti menjadi jumlah(angka)
// =========================================================================

