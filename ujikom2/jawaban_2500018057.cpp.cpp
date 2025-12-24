//=======================
//Nama :M.Gilang ramadhan
//Nim :2500018057
//Kelas: A
//quiz :Penjumlahan
//Tanggal : 24-12-2025
//=======================


#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif penjumlahan ini!
int jumlah(int n) {
    if (n == 1) {  
        return 1;
    }
    //kesalahan pertama adalah operasi sebelumnya menggunakan * pada return n*jumlah(n-1) 
    //Jadi perbaikan yang saya lakukan dalah mengubah tanda * menjadi tanda + jadi perbaikannya adalah return+jumlah(n-1)
    //jadi tanda bintang sebelumnya menyebabkan program menjadi faktorial bukan deret penjumlahan
    //yang dimana kalo kita inputkan angka 5 maka hasilnya adalah faktorial dari 5 yaitu 120
    //dan setelah di rubah menjadi tanda + maka akan menjadi operasi penjumlahan bukan faktorial
    return n + jumlah(n - 1);  
}

int main() {
    int angka;
    cout << "Masukkan angka: ";
    cin >> angka;
    
  //disini saya menambahkan perintah if yang berfungsi untuk semisal inputnya adalah minus maka program akan eror  
    if(angka<1){
    	cout<<"Eror operasi menggunakan angka minus tidak dapat dilakukan"<<endl;
	}else{
	
    
    cout << "Jumlah dari 1 hingga " << angka << " adalah: " << jumlah(angka) << endl;  
    //kesalahan kedua adalah di jumlah(angka -1) yang mana saya melakukan perubahan menjadi jumlah(angka) dan menghapus -1
    //karena kalo kita menggunakan -1 program akan melakukan operaasi matematika 5-1=4 yang mengakibatkan program dimulai dari 4 bukan 5
}
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
