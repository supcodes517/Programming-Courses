# 📝 PETUNJUK UJIAN KOMPETENSI 2 - FUNGSI REKURSI

## 📚 Informasi
- **Topik**: Fungsi Rekursif C++
- **Repository**: `supcodes517/Programming-Courses`
- **Bahasa**: C++ (100%)

---

## 🎯 Tujuan Ujian

Mahasiswa harus: 
1. ✅ Clone repository ujian
2. ✅ Memilih 1 (satu) quiz case untuk dikerjakan
3. ✅ Menemukan dan memperbaiki kesalahan dalam kode
4. ✅ Menambahkan komentar/catatan pada bagian yang salah
5. ✅ Push hasil perbaikan ke repository dengan branch baru (NIM)

---

## 📋 LANGKAH-LANGKAH PENGERJAAN

### **STEP 1: Clone Repository** 🔽

Buka terminal/command prompt dan jalankan: 

```bash
# Clone repository
git clone https://github.com/supcodes517/Programming-Courses.git

# Masuk ke folder repository
cd Programming-Courses

# Cek apakah sudah masuk ke folder yang benar
pwd  # untuk Linux/Mac
cd   # untuk Windows
```

**Verifikasi:**
```bash
ls -la  # Linux/Mac
dir     # Windows
# Pastikan Anda melihat file-file quiz yang ada di folder ujikom2
```

---

### **STEP 2: Buat Branch Baru dengan NIM Anda** 🌿

```bash
# Format: NIM Anda (contoh: 2500018001)
git checkout -b 2500018XXX

# Contoh jika NIM Anda 2500018123: 
git checkout -b 2500018123

# Verifikasi branch
git branch
# Harus ada tanda * di branch NIM Anda
```

**⚠️ PENTING:**
- Ganti `XXX` dengan 3 digit terakhir NIM Anda
- Pastikan format:  `2500018XXX` (10 digit)
- Branch harus menggunakan NIM, bukan nama! 

---

### **STEP 3: Pilih 1 Case Quiz** 🎲

Tersedia 2 quiz case dan 1 contoh:

| No | File | Topik | Tingkat Kesulitan |
|----|------|-------|-------------------|
| 1  | `quiz_faktorial.cpp` | hanya untuk contoh |
| 3  | `quiz_penjumlahan.cpp` | Penjumlahan | ⭐⭐ Sedang |
| 4  | `quiz_pangkat.cpp` | Pangkat | ⭐⭐ Sedang |

**Pilih salah satu file untuk dikerjakan! **

```bash
# Contoh:  Jika memilih quiz faktorial
cp quiz_faktorial.cpp jawaban_2500018XXX.cpp

# Ganti XXX dengan NIM Anda
```

---

### **STEP 4: Perbaiki Kode dan Tambahkan Komentar** 🔧

Buka file yang sudah Anda copy dengan text editor favorit: 

#### **Format Komentar yang Harus Ditambahkan:**

```cpp
// ============================================
// NAMA  : [Nama Lengkap Anda]
// NIM   :  [2500018XXX]
// QUIZ  : [Nama Quiz yang dipilih]
// TANGGAL: [DD/MM/YYYY]
// ============================================

#include <iostream>
using namespace std;

int faktorial(int n) {
    // ❌ KESALAHAN 1: Base case salah - seharusnya return 1, bukan 0
    // SEBELUM: if (n == 0) return 0;
    // PERBAIKAN: 
    if (n == 0 || n == 1) {  // ✅ DIPERBAIKI
        return 1;  // ✅ Faktorial 0 dan 1 adalah 1
    }
    
    // ❌ KESALAHAN 2: Operasi salah - harus perkalian (*), bukan penjumlahan (+)
    // SEBELUM: return n + faktorial(n - 1);
    // PERBAIKAN:
    return n * faktorial(n - 1);  // ✅ DIPERBAIKI - menggunakan perkalian
}

int main() {
    int angka;
    cout << "Masukkan angka:  ";
    cin >> angka;
    
    // ❌ KESALAHAN 3: Kondisi terbalik - harus angka < 0, bukan angka > 0
    // SEBELUM: if (angka > 0)
    // PERBAIKAN: 
    if (angka < 0) {  // ✅ DIPERBAIKI - cek bilangan negatif
        cout << "Faktorial tidak terdefinisi untuk bilangan negatif!" << endl;
    } else {
        cout << "Faktorial dari " << angka << " adalah: " << faktorial(angka) << endl;
    }
    
    return 0;
}

// ============================================
// RINGKASAN KESALAHAN YANG DITEMUKAN:
// 1. Base case return 0 → diperbaiki menjadi return 1
// 2. Operasi penjumlahan (+) → diperbaiki menjadi perkalian (*)
// 3. Kondisi angka > 0 → diperbaiki menjadi angka < 0
// ============================================
```

#### **📌 Format Komentar Wajib:**

Setiap kesalahan yang ditemukan HARUS diberi komentar dengan format:

```cpp
// ❌ KESALAHAN [nomor]:  [Penjelasan kesalahan]
// SEBELUM: [kode yang salah]
// PERBAIKAN:
[kode yang benar]  // ✅ DIPERBAIKI
```

---

### **STEP 5: Compile dan Test Program** ⚙️

Sebelum push, **WAJIB** test program Anda! 

```bash
# Compile
g++ jawaban_2500018XXX.cpp -o jawaban_2500018XXX

# Jika ada error, perbaiki dulu! 
# Jika sukses, jalankan program: 
./jawaban_2500018XXX   # Linux/Mac
jawaban_2500018XXX. exe # Windows
```

#### **Test dengan Expected Output:**

Gunakan test case dari file `EXPECTED_RESULTS.md`

**Contoh Test untuk Faktorial:**
```bash
# Test 1: Input 5 → Output harus 120
echo "5" | ./jawaban_2500018XXX
# Cek apakah output:  "Faktorial dari 5 adalah: 120"

# Test 2: Input 0 → Output harus 1
echo "0" | ./jawaban_2500018XXX

# Test 3: Input -3 → Output harus error message
echo "-3" | ./jawaban_2500018XXX
```

**✅ Lanjutkan ke STEP 6 hanya jika semua test berhasil!**

---

### **STEP 6: Push ke Repository** 📤

Setelah program diperbaiki dan berhasil ditest: 

```bash
# 1. Cek status file
git status
# Harus muncul file:  jawaban_2500018XXX.cpp

# 2. Add file ke staging
git add jawaban_2500018XXX.cpp

# 3. Commit dengan message yang jelas
git commit -m "Jawaban ujian [NIM] - [Nama Quiz]"

# Contoh: 
git commit -m "Jawaban ujian 2500018123 - Quiz Faktorial"

# 4. Push ke branch NIM Anda
git push origin 2500018XXX

# Contoh:
git push origin 2500018123
```

**Jika ini pertama kali push, mungkin diminta login GitHub:**
```bash
# Jika diminta username dan password:
Username: [username GitHub Anda]
Password: [Personal Access Token - bukan password biasa! ]
```

**Cara membuat Personal Access Token:**
1. Buka:  https://github.com/settings/tokens
2. Click:  "Generate new token (classic)"
3. Pilih scope: `repo` (full control)
4. Copy token dan simpan (tidak bisa dilihat lagi!)

---

### **STEP 7: Verifikasi Submission** ✅

Cek apakah submission berhasil:

1. **Buka browser**, kunjungi: 
   ```
   https://github.com/supcodes517/Programming-Courses
   ```

2. **Cek branch** - klik dropdown branch, cari NIM Anda: 
   ```
   Branch: 2500018XXX
   ```

3. **Verifikasi file** - pastikan file `jawaban_2500018XXX.cpp` ada

4. **Cek commit history**:
   ```
   Click: "Commits" → Lihat commit Anda
   ```

**Screenshot hasil verifikasi untuk bukti! ** 📸

---

## 📊 KRITERIA PENILAIAN

| Aspek | Bobot | Keterangan |
|-------|-------|------------|
| **Menemukan Kesalahan** | 30% | Semua kesalahan ditemukan |
| **Perbaikan Kode** | 40% | Kode diperbaiki dengan benar |
| **Komentar/Catatan** | 20% | Komentar lengkap dan jelas |
| **Program Berjalan** | 10% | Compile dan test berhasil |

### **Breakdown Penilaian:**

#### 1. **Menemukan Kesalahan (30 poin)**
- Menemukan semua kesalahan:  **30 poin**
- Menemukan sebagian:  **15-25 poin**
- Tidak menemukan: **0 poin**

#### 2. **Perbaikan Kode (40 poin)**
- Semua kesalahan diperbaiki dengan benar:  **40 poin**
- Program berjalan tapi ada logic error: **20-35 poin**
- Program tidak berjalan: **0-15 poin**

#### 3. **Komentar/Catatan (20 poin)**
- Format lengkap dan jelas: **20 poin**
- Komentar ada tapi tidak lengkap: **10-15 poin**
- Tidak ada komentar: **0 poin**

#### 4. **Program Berjalan (10 poin)**
- Compile dan semua test pass: **10 poin**
- Compile tapi ada test yang gagal: **5 poin**
- Tidak bisa compile: **0 poin**

**Total: 100 poin**

---

## ⚠️ ATURAN PENTING

### ✅ **BOLEH:**
- Menggunakan Google untuk referensi konsep rekursif
- Menggunakan text editor/IDE apapun
- Test program sebanyak mungkin
- Bertanya ke dosen jika ada masalah teknis Git

### ❌ **TIDAK BOLEH:**
- Copy-paste jawaban dari teman
- Menggunakan AI (ChatGPT, Copilot, dll) untuk memperbaiki kode
- Submit di branch orang lain
- Mengedit file quiz original (harus copy ke file baru)
- Submit lebih dari 1 quiz (pilih 1 saja)

### ⏰ **DEADLINE:**
- **Batas Akhir Push**: 25 Desember 2025
- **Keterlambatan**: -5 poin per hari

---

## 🆘 TROUBLESHOOTING

### **Problem 1: Git clone failed**
```bash
# Error:  Permission denied
# Solusi: Pastikan repository public atau Anda punya akses

# Coba clone dengan HTTPS:
git clone https://github.com/supcodes517/Programming-Courses.git
```

### **Problem 2: Branch sudah ada**
```bash
# Error: branch already exists
# Solusi:  Hapus branch lokal dan buat ulang
git branch -D 2500018XXX
git checkout -b 2500018XXX
```

### **Problem 3: Push rejected**
```bash
# Error: failed to push
# Solusi: Pull dulu, lalu push lagi
git pull origin 2500018XXX
git push origin 2500018XXX
```

### **Problem 4: Lupa NIM yang sudah dipush**
```bash
# Cek branch yang ada di remote
git branch -r
# Atau cek di GitHub web
```

---

## 📞 KONTAK BANTUAN

Jika mengalami kesulitan teknis: 

1. **Git/GitHub Issues**: 
   - Buat issue di repository
   - Tag:  `@supcodes517`

2. **Email Dosen**:
   - Subject: `[UJIAN REKURSIF] - [NIM] - [Masalah]`

---

## 📝 CHECKLIST SEBELUM SUBMIT

Pastikan sudah melakukan semua ini: 

- [x] Clone repository berhasil
- [x] Branch baru dengan NIM sudah dibuat
- [x] Sudah memilih 1 quiz case
- [x] File sudah di-copy dengan nama `jawaban_[NIM].cpp`
- [x] Header komentar sudah diisi lengkap (Nama, NIM, Quiz, Tanggal)
- [x] Semua kesalahan sudah ditemukan
- [x] Semua kesalahan sudah diperbaiki
- [x] Setiap perbaikan sudah diberi komentar dengan format yang benar
- [x] Ringkasan kesalahan sudah ditambahkan di akhir file
- [x] Program berhasil di-compile tanpa error
- [x] Program sudah ditest dengan minimal 3 test case
- [x] Semua test case berhasil (output sesuai expected)
- [x] File sudah di-commit dengan message yang jelas
- [x] File sudah di-push ke branch NIM
- [x] Sudah verifikasi di GitHub web bahwa file ter-upload
- [x] Screenshot bukti submission sudah diambil

---

## 🎯 TIPS SUKSES

1. **Baca kode dengan teliti** - Jangan terburu-buru
2. **Pahami konsep rekursif** - Base case dan recursive case
3. **Test secara bertahap** - Test setiap perbaikan
4. **Komentar yang jelas** - Jelaskan MENGAPA salah dan BAGAIMANA perbaikannya
5. **Double check** - Pastikan semua checklist sudah ✅
6. **Backup kode** - Copy file ke tempat lain sebelum push
7. **Push lebih awal** - Jangan tunggu menit terakhir
8. **Screenshot everything** - Bukti submission penting! 

---

## 🏆 SELAMAT MENGERJAKAN! 

**"Kegagalan adalah kesuksesan yang tertunda.  Debugging adalah jalan ninja programmer!"** 💻🚀
