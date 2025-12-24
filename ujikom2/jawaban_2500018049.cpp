// ============================================
// NAMA  : [Muhammad Daffa Khoiro]
// NIM   :  [2500018049]
// QUIZ  : [Quiz Penjumlahan]
// TANGGAL: [24/12/2025]
// ============================================

#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {

    if (n <= 1) { //✅ Diperbaiki  
        return 1;
    }
    // ❌ KESALAHAN 1 : Operasi salah - harus penjumlahan (+), bukan perkalian (*)
    // SEBELUM : return n * jumlah(n - 1);
    // PERBAIKAN :
    return n + jumlah(n - 1);  // ✅ Diperbaiki- menggunakan penjumlahan (+)
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    // ❌ KESALAHAN 2 : memanggil fungsi jumlah dengan angka yang di sebutkan
    // SEBELUM : jumlah(angka - 1);
    // PERBAIKAN :
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl; //✅ Diperbaiki- menghapus "- 1" dari penyebut
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Operasi perkalian (*) → diperbaiki menjadi penjumlahan (+)
// 2. Mengganti jumlah(angka - 1) → diperbaiki menjadi jumlah(angka)
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