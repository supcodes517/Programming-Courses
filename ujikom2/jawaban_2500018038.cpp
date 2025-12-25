// ============================================
// NAMA  : Najib Izyan Fahrezi
// NIM   :  2500018038
// QUIZ  : quiz_penjumlahan.cpp
// TANGGAL: 24/12/2025
// ============================================
#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
// Kesalahan 1: Basis rekursi salah, kondisi rekursi hanya akan memeriksa saat n bernilai 1 dan jika kita masukkan angka selain 1 akan terjadi eror
// Kesalahan 2: operasi rekursif salah, menggunakan perkalian (*), program akan menjalankan faktorial bukan penjumlahan sedangkan yang di minta adalah penjumlahan
// SEBELUM : kesalahan 1: if (n == 1)
// SEBELUM : Kesalahan 2: return n * jumlah (n - 1)
// Perbaikan:
int jumlah(int n) {
    if (n <= 1) {  // Diperbaiki
        return 1;
    }
    return n + jumlah(n - 1);  // Diperbaiki, jika menggunakan perkalian (*) program akan menghitung faktorial bukan penjumlahan 
}

// Kesalahan 3: Pemanggilan fungsi salah, nilai terakhir tidak ikut dihitung sehingga hasil penjumlahan kurang satu angka. Misal kita mnasukan angka 5 yang keluar hanya akan sampai angka 4
// SEBELUM : jumlah(angka-1)
// Perbaikan:
int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  //Diperbaiki, nilai akhir angka tidak dihitung
    
    return 0;
}

/*
Quiz 3: Penjumlahan

Test Case 1
**Input:**
```
5
```

**Expected Output:**
```
Masukkan angka: 5
Jumlah dari 1 hingga 5 adalah: 15
```

**Penjelasan:** 1 + 2 + 3 + 4 + 5 = 15

---

Test Case 2
**Input:**
```
10
```

**Expected Output:**
```
Masukkan angka: 10
Jumlah dari 1 hingga 10 adalah: 55
```

**Penjelasan:** 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10 = 55

---

Test Case 3
**Input:**
```
1
```

**Expected Output:**
```
Masukkan angka: 1
Jumlah dari 1 hingga 1 adalah: 1
```

**Penjelasan:** Hanya 1 angka

---
*/

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Kesalahan basis rekursi if (n == 1) ? diperbaiki if (n <= 1) 
// 2. Operasi perkalian (*) ? diperbaiki menjadi penjumlahan (+)
// 3. KEsalahan fungsi jumlah( angka - 1) ? diperbaiki jumlah(angka)
// ============================================
