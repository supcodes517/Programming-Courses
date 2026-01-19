// ============================================
// NAMA   : Nayla Aulia Nanda Anjali
// NIM    : 2500018021
// QUIZ   : Pangkat
// TANGGAL: 25/12/2025
// ============================================

#include <iostream>
using namespace std;


int pangkat (int basis, int eksponen) {
	 
	// KESALAHAN 1: Base case seharusnya menggunnakan if (eksponen == 0), bukan 1 dan return 1, bukan 0
    // SEBELUM: if (eksponen == 1) return basis;  
    if (eksponen == 0) {   
        return 1; // DIPERBAIKI - pangkat 0 harus menghasilkan 1
    }
    
    // KESALAHAN 2: Penggunaan operasi seharusnya perkalian (*), bukan penjumlahan (+)
    // SEBELUM: return basis + pangkat(basis, eksponen - 1);
    return basis * pangkat (basis, eksponen - 1);  // DIPERBAIKI - menggunakan perkalian sebagai pangkat
}

int main() {
    int basis, eksponen;
    cout << "Masukkan basis: ";
    cin >> basis;
    cout << "Masukkan eksponen: ";
    cin >> eksponen;
    
    
    // KESALAHAN 3: Output harus menampilkan "pangkat" bukan "ditambah
    // SEBELUM: " ditambah "
    cout << basis << " pangkat " // DIPERBAIKI - mengubah kata "ditambah" menjadi "pangkat"
		 << eksponen << " = " 
		 << pangkat (basis, eksponen) << endl; 
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Kesalahan 1: eksponen == 1 seharusnya adalah eksponen 0 dan pada return basis diperbaiki menjadi return 1
// 2. Pada kesalahan 2, operasi penjumlahan (+) diperbaiki menjadi perkalian (*)
// 3. Kesalahan 3: output-an seharusnya adalah "pangkat", bukan "ditambah"
// ============================================
