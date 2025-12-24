#include <iostream>
using namespace std;

// Perbaiki fungsi rekursif pangkat ini!
int pangkat(int basis, int eksponen) {
    if (eksponen == 1) {  
        return basis;
    }
    return basis + pangkat(basis, eksponen - 1);  
}

int main() {
    int basis, eksponen;
    cout << "Masukkan basis: ";
    cin >> basis;
    cout << "Masukkan eksponen: ";
    cin >> eksponen;
    
    cout << basis << " ditambah " << eksponen << " = " << pangkat(basis, eksponen) << endl; 
    
    return 0;
}

/*
Quiz 4: Pangkat

Test Case 1
**Input:**
```
2
3
```

**Expected Output:**
```
Masukkan basis: 2
Masukkan eksponen: 3
2 pangkat 3 = 8
```

**Penjelasan:** 2³ = 2 × 2 × 2 = 8

---

Test Case 2
**Input:**
```
5
0
```

**Expected Output:**
```
Masukkan basis: 5
Masukkan eksponen: 0
5 pangkat 0 = 1
```

**Penjelasan:** Semua bilangan pangkat 0 = 1

---

Test Case 3
**Input:**
```
10
2
```

**Expected Output:**
```
Masukkan basis: 10
Masukkan eksponen: 2
10 pangkat 2 = 100
```

**Penjelasan:** 10² = 100

---

Test Case 4
**Input:**
```
3
4
```

**Expected Output:**
```
Masukkan basis: 3
Masukkan eksponen: 4
3 pangkat 4 = 81
```

**Penjelasan:** 3⁴ = 3 × 3 × 3 × 3 = 81

---
*/