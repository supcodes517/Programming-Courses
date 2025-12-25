//***********************************
// Nama		: Talitha Yamilla Syahla	
// Nim		: 2500018032				
// Quiz		: Penjumlahan
// Tanggal	: 24/12/2025	
//***********************************

#include <iostream>
using namespace std;
	// Perbaiki fungsi rekursif penjumlahan ini!
	// Fungsi rekursif untuk menghitung penjumlahan bilangan dari 1 sampai n
int jumlah(int n) {
	// Rekursif
    if (n == 1) { 
        return 1;
    }
    // kesalahan 1: 
	// Jika menggunakan n == 1, maka hasil penjumlahan adalah 1
    // Sebelumnya adalah menggunakan return n * jumlah (n - 1); kondisi ini adalah kondisi faktorial
    return n + jumlah(n - 1); //Perbaikan nya adalah Menggunakan operator (+) karena yang diminta penjumlahan 
}

int main() {
    int angka;
    // Untuk Inputan
    cout << "Masukkan angka: ";
    cin >> angka;
    // Kesalahan 2 : kesalahannya adalah ada pengurangan di variabel angka (angka -1)
    // Sebelum adalah cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka -1) << endl;
    // Perbaikan :
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl; //Perbaikannya adalah menghapus '-1' agar tidak kehilangan angka berikutnya
    
     return 0;
}

	//===================================================================================================
	// RINGKASAN KESALAHAN YANG DITEMUKAN:
	// 1. Program pertama salah karena menggunakan perkalian n * jumlah(n - 1); sehingga hasilnya faktorial
	// 2. Fungsi dipanggil dengan nilai yang sudah dikurangi (angka -1)
	// 3. Sehingga hasil penjumlahan tidak sesuai dengan soalnya
	//===================================================================================================
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
