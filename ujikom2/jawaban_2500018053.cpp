// ============================================
// NAMA   : Muhammad Ridwan Kusumahani
// NIM    : 2500018053
// QUIZ   : Penjumlahan
// TANGGAL: 24/12/2025
// ============================================

#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    // Kesalahan 1 : Basis rekursi engga cukup robust karena cuma n == 1
    // Kalau validasi input di main() di hilangkan, n <= 0 bisa bikin rekursi infinity loop
    // Sebelum : if (n == 1) return 1; 
    // Perbaikan :
    if (n <= 1) {  // Diperbaiki : berhenti ketika n 1 atau lebih kecil
        return n;
    }

    // Kesalahan 2 : Operasi rekursif pakai perkalian, seharusnya penjumlahan.
    // Sebelum : return n * jumlah(n - 1);
    // Perbaikan :
    return n + jumlah(n - 1);  // Diperbaiki : pake penjumlahan
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // Kesalahan 3 : Pemanggilan rekursi dikurangi 1 sehingga hasil kurang satu
    // Sebelum : cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka - 1) << endl;
    // Perbaikan :
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  // Diperbaiki : pemanggilan fungsi harus sama dengan angka input
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN :
// 1. Basis rekursi hanya ngatasin n == 1 → diganti jadi n <= 1
// 2. Operasi rekursif pakai perkalian (*) → diganti jadi penjumlahan (+)
// 3. Pemanggilan fungsi jumlah(angka - 1) → digaanti jadi jumlah(angka)
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
