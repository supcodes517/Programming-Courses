#include <iostream>
using namespace std;

int jumlah(int n) {
    // ❌ KESALAHAN 1: Base case salah - seharusnya n==0 return 0, bukan n==1 return 1
    // SEBELUM: if (n == 1) return 1;
    // PERBAIKAN: 
    if (n == 0) {  
        return 0; // ✅ DIPERBAIKI
    }
    // ❌ KESALAHAN 2: kesalahn operasi hitung - seharusnya pertamabahan , bukan perkalian
    // SEBELUM:return n * jumlah(n - 1);
    // PERBAIKAN: 
    return n + jumlah(n - 1); // ✅ DIPERBAIKI
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // ❌ KESALAHAN 3: kesalahan pemanggilan fungsi- seharusnya angka, bukan angka -1
    // SEBELUM: jumlah(angka - 1)
    // PERBAIKAN: 
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  // ✅ DIPERBAIKI
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. KESALAHAN : Base case salah - seharusnya n==0 return 0, bukan n==1 return 1
// 2. KESALAHAN : kesalahn operasi hitung - seharusnya pertamabahan , bukan perkalian
// 3. KESALAHAN : kesalahan pemanggilan fungsi- seharusnya angka, bukan angka -1
// ============================================