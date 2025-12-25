#include <iostream>
using namespace std;

// Fungsi rekursif untuk menghitung penjumlahan dari 1 sampai angka yang ingin dimasukan/angka n
int jumlah(int n) {
    if (n == 1) {  
        return 1;  
        // jika n = 1, maka dia akan dikembalikan 1
    }
    return n + jumlah(n - 1); 
    // Perbaikan dari kode tersebut adalah mengganti perkalian menjadi penjumlahan
	// Kesalahan 1 adalah sebelumnya menggunakan perkalian * itu adalah faktorial, diganti dengan penjumlahan +.
	// contoh kode sebelumnya adalah return n * jumlah (n - 1)
	
	//jika dia menggunakan perkalian, maka akan mengeksekusi perkalian, jadi diganti dengan penjumlahan agar dia mengeksekusi penjumlahan
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    cout << "Jumlah dari 1 hingga " << angka << " adalah: "
         << jumlah(angka) << endl;
    // Perbaikan dari kode tersebut adalah agar menghitung dari 1 sampai angka, fungsi harus dipanggil dengan angka.
    //kode sebelumnya adalah jumlah(angka - 1);
	//kesalahan 2 adalah kode ini dapat mengurangi nilai pada penjumlahan yang seharusnya 15 menjadi 24
    
    
    //jika menggunakan jumlah(angka - 1) maka hasil dari eksekusi nya akan berkurang 1 semisal 5 maka hanya sampai 4 saja
	//begitu juga jika nilai inputnya 10 maka hasilnya 55, jadi dia akan mengurangi seharusnya nilai nya 55 maka hasilnya nanti akan salah
	//dan jika inputnya 1 yang seharusnya hasilnya hanya 1
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
