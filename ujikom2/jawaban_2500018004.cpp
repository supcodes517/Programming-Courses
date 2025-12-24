// ============================================
// NAMA  : Jehan Arsyad Setyawan
// NIM   : 2500018004
// QUIZ  : Quiz Pangkat
// TANGGAL: 12/24/2025
// ============================================

#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif pangkat ini!
int pangkat(int basis, int eksponen) {
    // ❌ Kesalahan 1  : Seharunya base case nya adalah b==0, tetap bisa dijalankan asal input eksponen bukan angka <=0
    // Sebelum      : if (eksponen == 1) { return basis; }
    // Perbaikan    : 
    if (eksponen == 0) {  // ✅ Diperbaiki
        return 1; // ✅ Kembalian 1 ketika nilai eksponen==0
    }

    // ❌ Kesalahan 2  : Rumus eksponen salah, seharusnya perkalian(*) bukan penjumlahan(+)
    // Sebelum      : return basis + pangkat(basis, eksponen - 1);
    // Perbaikan    : 
    return basis * pangkat(basis, eksponen - 1); // ✅ Diperbaiki 
}

int main() {
    int basis, eksponen;
    cout << "Masukkan basis: ";
    cin >> basis;
    cout << "Masukkan eksponen: ";
    cin >> eksponen;
    
    // ❌ Kesalahan 3  : Seharusnya cout setelah basis adalah " pangkat ", bukan " ditambah "
    // Sebelum      : cout << basis << " ditambah " << eksponen << " = " << pangkat(basis, eksponen) << endl;
    // Perbaikan    :
    cout << basis << " pangkat " << eksponen << " = " << pangkat(basis, eksponen) << endl; //✅ Diperbaiki 
    
    return 0;
}

/*
Quiz 4: Pangkat

Test Case 1
**Input:**
```
2
3
```

**Expected Output:**
```
Masukkan basis: 2
Masukkan eksponen: 3
2 pangkat 3 = 8
```

**Penjelasan:** 2³ = 2 × 2 × 2 = 8

---

Test Case 2
**Input:**
```
5
0
```

**Expected Output:**
```
Masukkan basis: 5
Masukkan eksponen: 0
5 pangkat 0 = 1
```

**Penjelasan:** Semua bilangan pangkat 0 = 1

---

Test Case 3
**Input:**
```
10
2
```

**Expected Output:**
```
Masukkan basis: 10
Masukkan eksponen: 2
10 pangkat 2 = 100
```

**Penjelasan:** 10² = 100

---

Test Case 4
**Input:**
```
3
4
```

**Expected Output:**
```
Masukkan basis: 3
Masukkan eksponen: 4
3 pangkat 4 = 81
```

**Penjelasan:** 3⁴ = 3 × 3 × 3 × 3 = 81

---
*/