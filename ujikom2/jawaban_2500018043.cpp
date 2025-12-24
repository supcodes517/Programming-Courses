// ============================================
// NAMA  : [Naufal Azka Putra Amaludin]
// NIM   :  [2500018043]
// QUIZ  : [Penjumlahan]
// TANGGAL: [23/12/2025]
// ============================================

#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    // ❌ Kesalahan 1: ketika diinputkan 1 tidak menampilkan angka 1 melainkan program langsung selesai.
    // SEBELUM: if (n == 1)
    // PERBAIKAN: 
    if (n <= 1) {  // ✅ DIPERBAIKI
        return n;
    }
    // ❌ KESALAHAN 2: mengubah operator perkalian (*) menjadi operator penjumlahan (+).
    // SEBELUM: return n * jumlah(n - 1);
    // SESUDAH: 
    return n + jumlah(n - 1); // ✅ DIPERBAIKI 
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;

    // ❌ KESALAHAN 3: pada jumlah(angka - 1) terdapat kesalahan yang setiap penjumlahan 1-5 atau 1-10 Selalu dikurangi 1.
    // SEBELUM: jumlah(angka - 1)
    // SESUDAH: 
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  // ✅ DIPERBAIKI
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Mengubah operator relasional dari (n == 1) menjadi (n <= 1)
// 2. Mengubah operator perkalian (*) menjadi operator penjumlahan (+).
// 3. Mengubah jumlah(angka - 1) menjadi jumlah(angka)
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