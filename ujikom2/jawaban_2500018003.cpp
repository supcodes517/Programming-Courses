// ============================================
// NAMA   : Lintang Ayu Cahyani
// NIM    : 2500018003
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
    
    // Kesalahan 1 : Operasi rekursif memakai operator perkalian seharusnya menggunakan penjumlahan.
    // Sebelum : return n * jumlah(n - 1);
    // Perbaikan :
    return n + jumlah(n - 1); // MEMPERBAIKI YANG AWALNYA MEMAKAI OPERATOR * BERUBAH MENJADI + 
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // Kesalahan 2 : Pemanggilan rekursi dikurangi 1 sehingga hasil menjadi kurang satu suku.
    // Sebelum : cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka - 1) << endl;
    // Perbaikan :
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  // MEMPERBAIKI YANG AWALNYA jumlah(angka - 1) MENJADI jumlah(angka)
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN :
// 1. Operasi rekursif menggunakan perkalian (*) ? diperbaiki menjadi penjumlahan (+).
// 2. Pemanggilan fungsi jumlah(angka - 1) ? diperbaiki menjadi jumlah(angka).
// ============================================

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
