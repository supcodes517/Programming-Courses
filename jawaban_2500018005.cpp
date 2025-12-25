#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif faktorial ini! 
int faktorial(int n) {
//salah = base casenya salah
//   if (n == 0) {
//      return 0;  
// yg bnar =
 if (n == 0 || n == 1) {
    return 1;
    }
// Ksalahan: operasinya salah karna pakai penjumlahan harusnya perkalian
//    return n + faktorial(n - 1);
// yg benar
return n * faktorial(n - 1);
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
//salah : cek bil negatfinya
//   if (angka > 0) {  
// yg bner
if (angka < 0) {
        cout << "Faktorial tidak terdefinisi untuk bilangan negatif!" << endl;
    } else {
        cout << "Faktorial dari " << angka << " adalah: " << faktorial(angka) << endl;
    }
    
    return 0;
}

/*
Quiz 1: Faktorial

Test Case 1
**Input:**
```
5
```

**Expected Output:**
```
Masukkan angka: 5
Faktorial dari 5 adalah: 120
```

**Penjelasan:** 5! = 5 × 4 × 3 × 2 × 1 = 120

---

Test Case 2
**Input:**
```
0
```

**Expected Output:**
```
Masukkan angka: 0
Faktorial dari 0 adalah: 1
```

**Penjelasan:** 0! = 1 (definisi matematis)

---

Test Case 3
**Input:**
```
-3
```

**Expected Output:**
```
Masukkan angka: -3
Faktorial tidak terdefinisi untuk bilangan negatif!
```

**Penjelasan:** Faktorial hanya berlaku untuk bilangan non-negatif

---
*/