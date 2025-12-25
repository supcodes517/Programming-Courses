// ============================================
// NAMA  : Alfarina Chusnaini Nurlatifah
// NIM   : 2500018041
// QUIZ  : Pangkat
// TANGGAL: 25/12/2025
// ============================================
#include <iostream>
using namespace std;

int pangkat(int basis, int eksponen) {
	// Kesalahan 1 : Base case salah dan tidak lengkap
    // Sebelum : if (eksponen == 1) return basis;
    // Perbaikan :
    if (eksponen == 0) {  // DIPERBAIKI
        return 1; // Semua bilangan pangkat 0 = 1, DIPERBAIKI
    }
    // Kesalahan 2 : Operasi salah karena menggunakan penjumlahan (+)
    // Sebelum : return basis + pangkat(basis, eksponen - 1);
    // Perbaikan :
    return basis * pangkat(basis, eksponen - 1); // DIPERBAIKI  
}

int main() {
    int basis, eksponen;
    cout << "Masukkan basis: ";
    cin >> basis;
    cout << "Masukkan eksponen: ";
    cin >> eksponen;
    
    // Kesalahan 3 : Output menggunakan kata "ditambah"
    // Sebelum : cout << basis << " ditambah " << eksponen << " = ...";
    // Perbaikan :
    cout << basis << " pangkat " << eksponen << " = " << pangkat(basis, eksponen) << endl; // DIPERBAIKI 
    
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

**Penjelasan:** 34 = 3 × 3 × 3 × 3 = 81

---
*/
