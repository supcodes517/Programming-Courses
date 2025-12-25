// ============================================
// NAMA  : [Novalino Dheza Yonansyah]
// NIM   :  [2500018020]
// QUIZ  : [Quiz Penjumlahan]
// TANGGAL: [24/12/2025]
// ============================================

#include <iostream>
using namespace std;

// Fungsi rekursif untuk penjumlahan angka dari 1 sampai nilai input atau n
int jumlah(int n) {
    if (n == 1) {  
        return 1; 
    }
    return n + jumlah(n - 1);
	//kesalahan 1 menggunakan perkalian
	//kode program sebelumnya return n * jumlah(n - 1)
	//perbaikan pada kode programnya perkalian diganti dengan penjumlahan
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    cout << "Jumlah dari 1 hingga " << angka << " adalah: "<< jumlah(angka) << endl; 
	//kesalahan 2 menggunakan - 1 ini tidak menjumlahkan angka terakhir
	//kode sebelumnya jumlah(angka - 1)
	//perbaikan pada kode programnya - 1 nya tidak digunakan agar menjumlahkan nilai terakhirnya
	
	//nilai 5 kalau menggunakan program sebelumnya hasilnya 24 dan jika kode baru hasilnya 15
	//begitu juga nilai nilai lainnya akan menghasilkan nilai yang benar
    
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
