//======================================================
// NAMA:  Dwi Purnama Citra
// NIM:   2500018055
// QUIZ: Penjumlahan
// TANGGAL: 25/12/2025
//======================================================

#include <iostream>
using namespace std;

int jumlah(int n) {
    // Fungsi mengembalikan jumlah dari 1 sampai n secara rekursif.
    // ❌ KESALAHAN 1: Basis kasus tidak lengkap.
    // SEBELUM: if (n == 1) { return 1; }
    // PERBAIKAN:
    // if (n <= 1) {
    //     return n;  // ✅ DIPERBAIKI
    // }
    // Penjelasan: basis harus menangani n==1 dan juga n==0 (jika terjadi),
    // sehingga fungsi tetap benar untuk semua n >= 0.
    // ❌ KESALAHAN 2: Operasi rekursif salah (menghasilkan faktorial).
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    // return n + jumlah(n - 1);  // ✅ DIPERBAIKI
    if (n <= 1) {
        // Jika n adalah 1 (atau 0), kembalikan n langsung.
        // Jadi jumlah(1)=1 dan jumlah(0)=0 (berguna bila input 0).
        return n;
    }
    // Rekursif: jumlah(1..n) = n + jumlah(1..(n-1))
    return n + jumlah(n - 1);
}
 
int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    // ❌ KESALAHAN 4: Tidak ada validasi untuk input negatif.
    // SEBELUM: (tidak ada pemeriksaan terhadap nilai negatif)
    // PERBAIKAN:
    // if (angka < 1) {
    //     cerr << "Error: masukan harus bilangan bulat positif (>=1)." << endl; // ✅ DIPERBAIKI
    //     return 1;
    // }
    // Penjelasan: jika pengguna memasukkan angka negatif (mis. -3), program seharusnya
    // memberi pesan kesalahan daripada menghitung jumlah.
    if (angka < 1) {
        cerr << "Error: masukan harus bilangan bulat positif (>=1)." << endl;
        return 1;
    }
     
    // ❌ KESALAHAN 3: Pemanggilan fungsi mengurangi satu (off-by-one).
    // SEBELUM: cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka - 1) << endl;
    // PERBAIKAN:
    // cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  // ✅ DIPERBAIKI
    // Perbaikan: panggil jumlah(angka) agar mencakup seluruh bilangan 1..angka
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  
     
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Basis kasus hanya memeriksa `n == 1` → diperbaiki menjadi `if (n <= 1) return n;`
// 2. Operasi rekursif menggunakan perkalian (`*`) sehingga menghasilkan faktorial →
//    diperbaiki menjadi penjumlahan (`+`) untuk menghitung jumlah 1..n
// 3. Pemanggilan fungsi di `main` menggunakan `jumlah(angka - 1)` (off-by-one) →
//    diperbaiki menjadi `jumlah(angka)`
// 4. Tidak ada validasi input negatif → diperbaiki dengan menampilkan pesan error
//    dan menghentikan program bila input < 1
// ============================================
