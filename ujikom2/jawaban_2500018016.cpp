// ============================================// 
// NAMA      : Alea Aminatussyifa
// NIM       : [2500018016]
// QUIZ      : [Penjumlahan]
// TANGGAL   : [24/12/2025]
// ============================================//


#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    if (n == 1) {  
        return 1;
    }
// ❌ KESALAHAN 1: return n * jumlah(n - 1) merupakan rekursi faktorial bukan penjumlahan
// SEBELUM: return n * jumlah(n - 1) merupakan kode yg salah
// PERBAIKAN: return n + jumlah(n - 1) merupakan kode yg benar
   return n + jumlah(n - 1); // ✅ DIPERBAIKI
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
// ❌ KESALAHAN 2: jumlah(angka - 1) membuat nilai input terakhir tidak dihitung
// SEBELUM: jumlah(angka - 1) merupakan kode yang salah
// PERBAIKAN: jumlah(angka) merupakan kode yang benar
   cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;   // ✅ DIPERBAIKI 
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. return n * jumlah(n - 1) (rekursi faktorial) → diperbaiki menjadi return n + jumlah(n - 1)
// 2. jumlah(angka - 1) → diperbaiki menjadi jumlah(angka)
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
