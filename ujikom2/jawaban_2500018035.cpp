// ============================================
// NAMA		: [Andi Fadillah Wardana]
// NIM   	: [2500018035]
// QUIZ  	: [Quiz Penjumlahan]
// TANGGAL	: [Rabu, 24 Desember 2025]
// ============================================

#include <iostream>
using namespace std;

// Fungsi rekursif untuk menghitung penjumlahan 1 sampai n
int jumlah(int n) {
    // BASE CASE
    if (n == 1) {  
        return 1;
    }
    // REKURSIF: n + (n-1)
    return n + jumlah(n - 1);  
// Operator * digunakan sebagai bentuk daripada perkalian atau menentukan nilai (faktorial).
// Soal meminta penjumlahan, bukan faktorial.
// Penggunaan operator bintang (*) sebelumnya membuat program menghitung faktorial, bukan deret penjumlahan.
// Jika dimasukkan nilai 5, maka hasil yang diperoleh adalah 5! yaitu 120.
// Setelah operator tersebut diganti menjadi tanda tambah (+), proses yang dilakukan berubah menjadi penjumlahan,
// sehingga program tidak lagi menghitung faktorial.

}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " 
         << jumlah(angka) << endl;  
// sebelumnya: jumlah(angka - 1) 
// sesudah: jumlah(angka)        
// Pengurangan nilai sebesar 1 membuat perhitungan tidak mencakup angka terakhir.
// Sebagai contoh, ketika memasukkan angka 5, proses perhitungan hanya berjalan sampai angka 4 sehingga hasilnya menjadi tidak sesuai.
    
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


