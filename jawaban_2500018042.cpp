//=============================
//Nama : Ahmad Rasyid Fadhilah
//NIM : 2500018042
//Kelas : A
//Quiz : Penjumlahan
//Tanggal : 25-12-2025
//=============================

#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    if (n == 1) {  
        return 1;
    }
    return n + jumlah(n - 1);  
    //Salahnya adalah karena menggunakan * (perkalian), itu rumus faktorial bukan rumus penjumlahan
    //jadi n*jumlah(n-1) itu kalo gak diganti menjadi n+jumlah(n-1) maka programnya bukan menjumlahkan, tapi menghitung n!
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  
    //Salah kedua karena jumlah(angka -1) itu akan mengurangi angka yang di input, misal: menginput 4, tapi yang dihitung cuman sampai 3
    //dan yang benar adalah jumlah(angka), sehingga ketika hasil outpout nya tidak di kurangi
    
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
