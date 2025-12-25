#include <iostream>
using namespace std;
// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    if (n == 1) {  
        return 1;
    }
    // kesalahan 1: pada kode sebelumnya menggunakan n * jumlah(n - 1) yang menyebabkan hasilnya menjadi perkalian, maka dari itu diubah menjadi n + jumlah(n - 1) dan hasilnya menjadi penjumlahan
    // Sebelum : return n * jumlah(n - 1);
    // Perbaikan : untuk kesalahan kode sebelumnya menggunakan perkalian dan setelah perbaikan menggunakan penjumlahan
    return n + jumlah(n - 1);
}   

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    // kesalahan 2: pada kode sebelumnya menggunakan angka - 1 yang menyebabkan hasilnya menjadi salah karena tidak termasuk angka terakhir
    // dalam (angka -1) diganti menjadi (angka) saja karena jika tidak diubah maka hasilnya akan salah
    // Sebelum : cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka - 1) << endl;
    // Perbaikan : untuk kesalahan kode sebelumnya mengurangi 1 dari angka masukan sehingga hasilnya salah
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  
    // 
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