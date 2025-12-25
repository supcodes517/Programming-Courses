// ============================================
// NAMA  : [Rizky Sri Mulyani]
// NIM   :  [2500018011]
// QUIZ  : [Penjumlahan]
// TANGGAL: [25/12/2025]
// ============================================

#include <iostream>
using namespace std;

//Fungsi untuk hitung penjumlahan 1 - n
int penjumlahan(int n) {
    // SALAH: seharusnya return 0, bukan 1
    // SEBELUM: if (n == 0) return 0;
    // PERBAIKAN: 
    if (n == 0 ) {  
        return 0;  // Penjumlahan harus dari 0
    }
    
    // SALAH: Opeerasi bilangan salah, harus penjumlahan (+), bukan perkalian (*)
    // SEBELUM: return n + penjumlahan(n - 1);
    return n + penjumlahan(n - 1);  //PERBAIKAN - menggunakan penjumlahan
}

int main() {
    int angka;
    cout << "Masukkan angka:  ";
    cin >> angka;
    
    // SALAH : Terbalik harus angka > 0, bukan angka < 0
    // SEBELUM: if (angka > 0)
    // PERBAIKAN
    if (angka < 0) {  
	// PERBAIKAN : Tidak ada bilangan negatif
        cout << "Penjumlahan tidak bisa untuk bilangan negatif!" << endl;
    } else {
        cout << "Hasil penjumlahan dari 1 sampai " << angka << " adalah: " << penjumlahan(angka) << endl;
    }
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base case return 1 ? diperbaiki menjadi return 0
// 2. Operasi perkalian (*) ? diperbaiki menjadi penjumlahan (+)
// 3. Kondisi angka < 0 ? diperbaiki menjadi angka > 0
// ============================================
