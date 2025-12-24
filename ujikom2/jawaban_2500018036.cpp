// ============================================
// NAMA  : Muhammad Azril Achdi
// NIM   : 2500018036
// QUIZ  : Quiz Penjumlahan
// TANGGAL: 24/12/2025
// ============================================

#include <iostream>
using namespace std;

int jumlah(int n) {
    // KESALAHAN 1: Base case kurang aman
    // SEBELUM: if (n == 1) return 1;
    // PERBAIKAN:
    if (n == 0) {  // DIPERBAIKI
        return 0;
    }
    
    // KESALAHAN 2: Operasi salah, harusnya penjumlahan, bukan perkalian
    // SEBELUM: return n * jumlah(n - 1);
    // PERBAIKAN:
    return n + jumlah(n - 1);  // DIPERBAIKI ganti * jadi +
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // KESALAHAN 3: Pemanggilan fungsi salah, kurang 1 angka
    // SEBELUM: jumlah(angka - 1)
    // PERBAIKAN:
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  // DIPERBAIKI
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base case n==1 return 1 → diperbaiki menjadi n==0 return 0
// 2. Operasi perkalian (*) → diperbaiki menjadi penjumlahan (+)
// 3. Pemanggilan jumlah(angka-1) → diperbaiki menjadi jumlah(angka)
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