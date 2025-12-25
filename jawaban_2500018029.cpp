#include <iostream>
using namespace std;
// baik pak ini kode yg telah saya buat 
int jumlah(int n) {
    if (n == 1) {
        return 1; 
    }
    return n + jumlah(n - 1); 
    // kesalahan 1, yg awalnya menggunakan perkalian * itu salah,tapi ketika saya mencoba menggunakan penjumlahan + itu baru benar
    // retrun n * jumlah( n - 1 );
    // perbaikannya saya ganti pake penjumlahan
}

int main() {
    int angka;

    cout << "Masukkan angka: ";
    cin >> angka;

    cout << "Jumlah dari 1 hingga " << angka << " adalah: "<< jumlah(angka) << endl;
    // kesalahan 2,jadi yg didalam kurung itukan ada tuisan angka - 1,maka saya hapus
    //ini kode sebelumnya: jumlah ( angka - 1 ) <<endl;
    // perbaikanya brrti saya ga perlu pakek - 1 nya itu akan mengurangi hasil eksekusi angka terakhirnya tersebut
    // contoh nilainya 5 maka kalo misal pakek code yg sebelumnya dia mengeksekusi 1+2+3+4,dan kalo misal saya pake kode setelahnya yg telah saya ubah itu baru dia bakal mengeksekusi 1+2+3+4+5
    return 0;
}

