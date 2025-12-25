//============================================
// NAMA     : BEMA VALENTINO  AMORTA
// NIM      : 2500018031
// QUIZ     : PENJUMLAHAN
// TANGGAL  : 24-12-2025
//============================================

#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
	
	//KESALAAN 1 : Yang sebelmunya menggunakan if (n == 1) dan seharusnya diubah menjadi (n <= 1) agar tidak terjadi error jika ada inputan nol/negatif
	
	//SEBELUM : if (n == 1) { 
	 
    //PERBAIKAN :
    if (n <= 1) {  // Diperbaiki dan di ubah if (n == 1) seharusnya menjadi if (n <= 1) {
        return 1;
    }
    
    
    
    
    
    
    //KESALAHAN 2 : Sebelumnya menggunakan perkalian (*) dan seharusnya diubah menggunakan penjumlahan (+) bukan perkalian (*) karna ini adalah fungsi rekursif penjumlahan
    
    //SEBELUM : return n + jumlah(n * 1);  
    
    //PERBAIKAN : 
	return n + jumlah(n - 1); // Diperbaiki simbol operasi perhitungannya yang sebelumnya menggunakan (*) menjadi (-)
}







int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    //KESALAHAN 3 : fungsi harus menggunakan jumlah(angka) agar hasil penjumlahan sesuai dengan angka yang dimasukkan jika memakai jumlah(angka - 1) maka perhitungan berhenti satu langkah lebih pendek sehingga hasilnya salah
    
    //SEBELUM : cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka - 1) << endl;  
    
    
    //PERBAIKAN :
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl; // Diperbaiki << jumlah(angka) <<endl;  
    
    return 0;
    
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1.Kondisi Batas: Mengubah if (n == 1) menjadi (n <= 1) agar lebih inklusif.
// 2.Operator Rekursi: Mengganti pengurangan (n - 1) menjadi perkalian (n * 1).
// 3.Nilai Parameter: Menyesuaikan jumlah(angka - 1) menjadi hanya jumlah(angka).
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

