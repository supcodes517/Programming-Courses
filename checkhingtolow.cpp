#include <iostream>
using namespace std;

int main() {
    int size;

    cout << "Masukkan ukuran array: ";
    cin >> size;

    int Arr1[size];
    cout << "Masukkan elemen-elemen array:\n";
    for(int i = 0; i < size; i++) {
        cout << "Elemen " << i + 1 << ": ";
        cin >> Arr1[i];
    }


     cout << " Array1: ";
    for(int i = 0;i < size; i++) {
        cout << Arr1[i] << " ";
    }

    int pos = Arr1[0];

    for(int i = 0; i < size ; i++) {
        for(int j = 0;j < size - 1 ; j++) {
            if(Arr1[j] > Arr1[j + 1]) {
                pos = Arr1[j];
                Arr1[j] = Arr1[j + 1];
                Arr1[j + 1] = pos;
            }
        }
    }
    cout << "\n Array2: ";
    for(int i = 0;i < size; i++) {
        cout << Arr1[i] << " ";
    }
    for(int i = 0; i < size ; i++) {
        for(int j = 0;j < size - 1 ; j++) {
            if(Arr1[j] < Arr1[j + 1]) {
                pos = Arr1[j];
                Arr1[j] = Arr1[j + 1];
                Arr1[j + 1] = pos;
            }
        }
    }
    cout << "\n Array3: ";
    for(int i = 0;i < size; i++) {
        cout << Arr1[i] << " ";
    }

}
