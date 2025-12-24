// ============================================
// NAMA   : Nayla Nurika Salsabila
// NIM    : 2500018010
// QUIZ   : Penjumlahan
// TANGGAL: 24/12/2025
// ============================================


#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    if (n == 1) {  
        return 1;
    }
// ❌KESALAHAN 1: harusnya menggunakan operasi penjumlahan (+) bukan perkalian (*)
// SEBELUM: return n * jumlah(n - 1);
// PERBAIKAN:
	return n + jumlah(n - 1);   // ✅DIPERBAIKI
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
// ❌KESALAHAN 2: pada "jumlah(angka-1)" seharusnya tidak menggunakan -1
// SEBELUM: cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka-1) << endl; 
// PERBAIKAN:
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;   // ✅DIPERBAIKI
    
    return 0;
}
// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. mengubah return pada fungsi rekrusif dari * menjadi +
// 2. diubah pada "jumlah(angka-1)" seharusnya tidak menggunakan -1
// ============================================
