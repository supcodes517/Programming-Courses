# 📚 Tutorial File I/O C++ untuk Tic-Tac-Toe
## Menyimpan dan Memuat Data Pemain dari File players.txt

---

## 1. Konsep Dasar File I/O

### 🔍 Apa itu File I/O?
File Input/Output (I/O) adalah proses membaca data dari file (input) dan menulis data ke file (output). Dalam C++, kita menggunakan library `<fstream>` untuk operasi file.

### 📚 Library yang Dibutuhkan

```cpp
#include <fstream>  // Untuk file operations
#include <iostream> // Untuk console I/O
#include <string>   // Untuk string operations
#include <vector>   // Untuk menyimpan data pemain
```

### 🎯 Tiga Kelas Utama untuk File I/O

| Kelas | Deskripsi | Kegunaan |
|-------|-----------|----------|
| `fstream` | File stream (input & output) | Membaca DAN menulis file |
| `ifstream` | Input file stream | Hanya untuk MEMBACA file |
| `ofstream` | Output file stream | Hanya untuk MENULIS file |

### 💡 Cara Kerja File Stream

```cpp
// 1. MENULIS ke File (Output)
ofstream outputFile;              // Deklarasi objek
outputFile.open("data.txt");      // Buka file
outputFile << "Hello World";      // Tulis data
outputFile.close();               // Tutup file

// 2. MEMBACA dari File (Input)
ifstream inputFile;               // Deklarasi objek
inputFile.open("data.txt");       // Buka file
string data;
inputFile >> data;                // Baca data
inputFile.close();                // Tutup file
```

### 🚀 Mode Pembukaan File

```cpp
ios::in      // Buka untuk membaca (default untuk ifstream)
ios::out     // Buka untuk menulis (default untuk ofstream)
ios::app     // Append - tambahkan di akhir file
ios::trunc   // Hapus isi file jika sudah ada
ios::binary  // Mode binary
```

**Contoh Penggunaan:**
```cpp
ofstream file("data.txt", ios::app);  // Tambahkan data tanpa menghapus yang lama
```

---

## 2. Format File players.txt

### 📄 Struktur Data Pemain

```cpp
struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};
```

### 📝 Format File: Space-Separated Values

```
nama totalGames totalWins totalDraws totalLosses score
```

### ✅ Contoh File players.txt yang Benar

```
Budi 10 7 2 1 16
Siti 15 10 3 2 23
Ahmad 8 4 2 2 10
Dewi 20 15 3 2 33
Rian 5 3 1 1 7
```

**Penjelasan Format:**
- **Budi**: Nama pemain (tanpa spasi)
- **10**: Total permainan yang dimainkan
- **7**: Total kemenangan
- **2**: Total seri
- **1**: Total kekalahan
- **16**: Skor total (biasanya: wins*2 + draws*1)

### ⚠️ Contoh Format yang SALAH

```
// ❌ SALAH - Nama dengan spasi tanpa penanganan khusus
Budi Santoso 10 7 2 1 16

// ❌ SALAH - Data tidak lengkap
Ahmad 8 4 2

// ❌ SALAH - Menggunakan koma sebagai separator
Dewi,20,15,3,2,33
```

### 💡 Solusi untuk Nama dengan Spasi

```cpp
// Opsi 1: Ganti spasi dengan underscore
Budi_Santoso 10 7 2 1 16

// Opsi 2: Gunakan delimiter khusus (misalnya |)
Budi Santoso|10|7|2|1|16

// Opsi 3: Gunakan format CSV dengan quotes
"Budi Santoso",10,7,2,1,16
```

---

## 3. Fungsi savePlayers()

### 🎯 Tujuan
Menyimpan semua data pemain dari vector ke file players.txt

### 📝 Implementasi Lengkap

```cpp
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

void savePlayers(const vector<Player>& players, const string& filename) {
    // LANGKAH 1: Buat objek ofstream untuk menulis
    ofstream outputFile;
    
    // LANGKAH 2: Buka file dengan mode write (akan overwrite file lama)
    outputFile.open(filename);
    
    // LANGKAH 3: Cek apakah file berhasil dibuka
    if (!outputFile.is_open()) {
        cout << "❌ Error: Tidak dapat membuka file " << filename << endl;
        return;  // Keluar dari fungsi jika gagal
    }
    
    // LANGKAH 4: Loop melalui semua pemain dan tulis ke file
    for (const auto& player : players) {
        outputFile << player.nama << " "
                   << player.totalGames << " "
                   << player.totalWins << " "
                   << player.totalDraws << " "
                   << player.totalLosses << " "
                   << player.score << endl;
    }
    
    // LANGKAH 5: Tutup file setelah selesai
    outputFile.close();
    
    // LANGKAH 6: Konfirmasi berhasil
    cout << "✅ Data berhasil disimpan ke " << filename << endl;
}
```

### 🔍 Penjelasan Detail

#### Langkah 1: Deklarasi ofstream
```cpp
ofstream outputFile;
```
- `ofstream` = Output File Stream
- Digunakan khusus untuk **menulis** ke file
- `outputFile` adalah nama variabel (bisa diganti sesuai keinginan)

#### Langkah 2: Membuka File
```cpp
outputFile.open(filename);
```
- Membuka file dengan nama yang diberikan
- Jika file tidak ada, akan **dibuat otomatis**
- Jika file sudah ada, isinya akan **dihapus** (overwrite)

#### Langkah 3: Validasi
```cpp
if (!outputFile.is_open()) {
    cout << "❌ Error: Tidak dapat membuka file" << endl;
    return;
}
```
- `is_open()` mengecek apakah file berhasil dibuka
- Jika gagal (return false), tampilkan error dan keluar

#### Langkah 4: Menulis Data
```cpp
outputFile << player.nama << " " << player.totalGames << " " ...
```
- Gunakan operator `<<` seperti cout
- Pisahkan data dengan spasi `" "`
- Gunakan `endl` untuk baris baru

#### Langkah 5: Menutup File
```cpp
outputFile.close();
```
- **PENTING**: Selalu tutup file setelah selesai
- Memastikan data tersimpan dengan benar
- Membebaskan resource

### 🎨 Variasi Implementasi

#### Dengan Backup Otomatis:
```cpp
void savePlayersWithBackup(const vector<Player>& players, const string& filename) {
    // Backup file lama
    ifstream checkFile(filename);
    if (checkFile.good()) {
        checkFile.close();
        string backupName = filename + ".backup";
        rename(filename.c_str(), backupName.c_str());
        cout << "📦 Backup dibuat: " << backupName << endl;
    }
    
    // Simpan data baru
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "❌ Error: Tidak dapat membuka file" << endl;
        return;
    }
    
    for (const auto& player : players) {
        outputFile << player.nama << " "
                   << player.totalGames << " "
                   << player.totalWins << " "
                   << player.totalDraws << " "
                   << player.totalLosses << " "
                   << player.score << endl;
    }
    
    outputFile.close();
    cout << "✅ Data berhasil disimpan!" << endl;
}
```

---

## 4. Fungsi loadPlayers()

### 🎯 Tujuan
Membaca data pemain dari file players.txt dan menyimpannya ke dalam vector

### 📝 Implementasi Lengkap

```cpp
vector<Player> loadPlayers(const string& filename) {
    // LANGKAH 1: Buat vector untuk menampung data
    vector<Player> players;
    
    // LANGKAH 2: Buat objek ifstream untuk membaca
    ifstream inputFile;
    
    // LANGKAH 3: Buka file
    inputFile.open(filename);
    
    // LANGKAH 4: Cek apakah file berhasil dibuka
    if (!inputFile.is_open()) {
        cout << "⚠️ File " << filename << " tidak ditemukan." << endl;
        cout << "📝 File baru akan dibuat saat menyimpan data." << endl;
        return players;  // Return vector kosong
    }
    
    // LANGKAH 5: Baca data baris per baris
    Player temp;
    while (inputFile >> temp.nama 
                     >> temp.totalGames 
                     >> temp.totalWins 
                     >> temp.totalDraws 
                     >> temp.totalLosses 
                     >> temp.score) {
        // LANGKAH 6: Tambahkan pemain ke vector
        players.push_back(temp);
    }
    
    // LANGKAH 7: Tutup file
    inputFile.close();
    
    // LANGKAH 8: Konfirmasi berhasil
    cout << "✅ " << players.size() << " pemain berhasil dimuat" << endl;
    
    return players;
}
```

### 🔍 Penjelasan Detail

#### Langkah 1: Persiapan Vector
```cpp
vector<Player> players;
```
- Vector kosong untuk menampung data pemain
- Akan dikembalikan di akhir fungsi

#### Langkah 2-3: Membuka File untuk Membaca
```cpp
ifstream inputFile;
inputFile.open(filename);
```
- `ifstream` = Input File Stream (khusus untuk membaca)
- Membuka file dengan nama yang diberikan

#### Langkah 4: Validasi File
```cpp
if (!inputFile.is_open()) {
    // File tidak ada atau tidak bisa dibuka
    return players;  // Return vector kosong
}
```
- Jika file tidak ada, tidak perlu error fatal
- Return vector kosong (valid untuk aplikasi baru)

#### Langkah 5: Membaca Data
```cpp
while (inputFile >> temp.nama >> temp.totalGames >> ...) {
    players.push_back(temp);
}
```
- **While loop** akan berjalan selama masih ada data
- Operator `>>` membaca data yang dipisahkan spasi/newline
- Otomatis berhenti saat mencapai end of file (EOF)

### 🎨 Variasi dengan Validasi Data

```cpp
vector<Player> loadPlayersWithValidation(const string& filename) {
    vector<Player> players;
    ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        cout << "⚠️ File tidak ditemukan" << endl;
        return players;
    }
    
    Player temp;
    int lineNumber = 0;
    
    while (inputFile >> temp.nama 
                     >> temp.totalGames 
                     >> temp.totalWins 
                     >> temp.totalDraws 
                     >> temp.totalLosses 
                     >> temp.score) {
        lineNumber++;
        
        // VALIDASI DATA
        bool isValid = true;
        
        // Cek nilai negatif
        if (temp.totalGames < 0 || temp.totalWins < 0 || 
            temp.totalDraws < 0 || temp.totalLosses < 0) {
            cout << "⚠️ Baris " << lineNumber << ": Nilai negatif terdeteksi" << endl;
            isValid = false;
        }
        
        // Cek konsistensi
        if (temp.totalWins + temp.totalDraws + temp.totalLosses != temp.totalGames) {
            cout << "⚠️ Baris " << lineNumber << ": Data tidak konsisten" << endl;
            isValid = false;
        }
        
        // Cek nama kosong
        if (temp.nama.empty()) {
            cout << "⚠️ Baris " << lineNumber << ": Nama kosong" << endl;
            isValid = false;
        }
        
        if (isValid) {
            players.push_back(temp);
        } else {
            cout << "❌ Data pada baris " << lineNumber << " diabaikan" << endl;
        }
    }
    
    inputFile.close();
    cout << "✅ " << players.size() << " pemain valid dimuat" << endl;
    
    return players;
}
```

## 5. Troubleshooting

### ❌ Problem 1: File Not Found

**Gejala:**
```
Error: Tidak dapat membuka file players.txt
```

**Penyebab:**
- File belum dibuat
- File berada di direktori yang berbeda
- Tidak ada permission untuk mengakses file

**Solusi:**
```cpp
// Solusi 1: Cek apakah file ada
#include <sys/stat.h>

bool fileExists(const string& filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

if (!fileExists(FILENAME)) {
    cout << "File tidak ditemukan, membuat file baru..." << endl;
    ofstream newFile(FILENAME);
    newFile.close();
}

// Solusi 2: Tampilkan direktori kerja
#include <filesystem>  // C++17
cout << "Working directory: " << filesystem::current_path() << endl;

// Solusi 3: Gunakan path absolut
const string FILENAME = "C:/Users/YourName/Documents/players.txt";
```

---

### ❌ Problem 2: Data Tidak Tersimpan

**Gejala:**
- Program berjalan tanpa error
- Tetapi data tidak ada di file

**Penyebab:**
- Lupa memanggil `close()`
- Program crash sebelum menutup file
- Menulis ke file di lokasi yang salah

**Solusi:**
```cpp
// Solusi 1: Selalu gunakan close()
outputFile.close();

// Solusi 2: Flush buffer secara manual
outputFile << data << endl;
outputFile.flush();  // Paksa tulis ke disk

// Solusi 3: Gunakan scope untuk auto-close
{
    ofstream file(FILENAME);
    file << data;
    // File otomatis close saat keluar dari scope
}

// Solusi 4: Gunakan RAII pattern
void savePlayers(const vector<Player>& players) {
    ofstream file(FILENAME);
    if (!file) {
        throw runtime_error("Cannot open file");
    }
    // File akan otomatis close saat fungsi berakhir
    for (const auto& p : players) {
        file << p.nama << " " << p.score << endl;
    }
}
```

---

### ❌ Problem 3: Data Corrupt / Salah Terbaca

**Gejala:**
```
Budi 10 7 2 1 16
Siti Ahmad Dewi
```

**Penyebab:**
- Format data tidak konsisten
- Ada nama dengan spasi
- Encoding file bermasalah

**Solusi:**
```cpp
// Solusi 1: Gunakan getline untuk nama
while (getline(inputFile, temp.nama, '|')) {  // Delimiter |
    inputFile >> temp.totalGames >> temp.totalWins 
              >> temp.totalDraws >> temp.totalLosses >> temp.score;
    inputFile.ignore();  // Skip newline
    players.push_back(temp);
}

// Format file: Budi Santoso|10|7|2|1|16

// Solusi 2: Validasi setelah membaca
Player temp;
while (inputFile >> temp.nama >> temp.totalGames >> ...) {
    if (temp.totalGames < 0 || temp.totalWins < 0) {
        cerr << "Data corrupt: " << temp.nama << endl;
        continue;  // Skip data ini
    }
    players.push_back(temp);
}

// Solusi 3: Gunakan format CSV
#include <sstream>
string line;
while (getline(inputFile, line)) {
    stringstream ss(line);
    string item;
    Player temp;
    
    getline(ss, temp.nama, ',');
    ss >> temp.totalGames;
    ss.ignore();  // Skip comma
    ss >> temp.totalWins;
    // ... dst
    
    players.push_back(temp);
}
```

---

### ❌ Problem 4: Nama dengan Spasi

**Gejala:**
```cpp
// Input: "Budi Santoso 10 7 2 1 16"
// Result: nama = "Budi", totalGames dibaca sebagai "Santoso"
```

**Penyebab:**
- Operator `>>` berhenti di whitespace
- Spasi dianggap sebagai delimiter

**Solusi Lengkap:**
```cpp
// OPSI 1: Replace spasi dengan underscore saat input
void addPlayer(vector<Player>& players) {
    string nama;
    cout << "Masukkan nama (gunakan _ untuk spasi): ";
    cin >> nama;
    players.push_back(Player(nama));
}
// Input: Budi_Santoso

// OPSI 2: Gunakan getline dan custom delimiter
struct Player {
    string nama;
    int totalGames, totalWins, totalDraws, totalLosses, score;
};

void savePlayers(const vector<Player>& players) {
    ofstream file(FILENAME);
    for (const auto& p : players) {
        file << p.nama << "|" << p.totalGames << "|" 
             << p.totalWins << "|" << p.totalDraws << "|"
             << p.totalLosses << "|" << p.score << endl;
    }
    file.close();
}

vector<Player> loadPlayers() {
    vector<Player> players;
    ifstream file(FILENAME);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        Player temp;
        
        getline(ss, temp.nama, '|');
        ss >> temp.totalGames;
        ss.ignore();  // Skip |
        ss >> temp.totalWins;
        ss.ignore();
        ss >> temp.totalDraws;
        ss.ignore();
        ss >> temp.totalLosses;
        ss.ignore();
        ss >> temp.score;
        
        players.push_back(temp);
    }
    
    file.close();
    return players;
}

// OPSI 3: Gunakan quotes seperti CSV
// Format: "Budi Santoso",10,7,2,1,16
```

---

### ❌ Problem 5: Windows Path Issues

**Gejala:**
```cpp
// Windows path tidak work
string path = "C:\Users\Documents\players.txt";  // ❌ SALAH
```

**Penyebab:**
- Backslash `\` adalah escape character di C++
- Perlu di-escape atau gunakan forward slash

**Solusi:**
```cpp
// Solusi 1: Double backslash
string path = "C:\\Users\\Documents\\players.txt";  // ✅

// Solusi 2: Forward slash (work di Windows juga)
string path = "C:/Users/Documents/players.txt";  // ✅ Recommended

// Solusi 3: Raw string literal (C++11)
string path = R"(C:\Users\Documents\players.txt)";  // ✅

// Solusi 4: Relative path
string path = "data/players.txt";  // ✅ Cross-platform

// Solusi 5: Gunakan filesystem library (C++17)
#include <filesystem>
namespace fs = std::filesystem;
fs::path filePath = fs::current_path() / "data" / "players.txt";
```

---

## 6. Best Practices

### ✅ 1. Selalu Cek is_open()

```cpp
// ❌ JANGAN seperti ini
ofstream file("data.txt");
file << "Hello";  // Bisa gagal tanpa error!

// ✅ LAKUKAN seperti ini
ofstream file("data.txt");
if (!file.is_open()) {
    cerr << "Error: Cannot open file!" << endl;
    return;
}
file << "Hello";
```

---

### ✅ 2. Gunakan Konstanta untuk Nama File

```cpp
// ❌ Hard-coded di mana-mana
void save() {
    ofstream file("players.txt");
    // ...
}
void load() {
    ifstream file("players.txt");
    // ...
}

// ✅ Gunakan konstanta
const string FILENAME = "players.txt";
const string BACKUP_FILENAME = "players.backup.txt";

void save() {
    ofstream file(FILENAME);
    // ...
}
void load() {
    ifstream file(FILENAME);
    // ...
}
```

**Keuntungan:**
- Mudah diubah dari satu tempat
- Tidak typo
- Lebih maintainable

---

### ✅ 3. Backup Sebelum Overwrite

```cpp
void savePlayersWithBackup(const vector<Player>& players) {
    // 1. Backup file lama jika ada
    ifstream checkExist(FILENAME);
    if (checkExist.good()) {
        checkExist.close();
        
        // Copy ke backup
        ifstream src(FILENAME, ios::binary);
        ofstream dst(BACKUP_FILENAME, ios::binary);
        dst << src.rdbuf();
        src.close();
        dst.close();
        
        cout << "📦 Backup created" << endl;
    }
    
    // 2. Simpan data baru
    ofstream file(FILENAME);
    // ... simpan data ...
    file.close();
}
```

---

### ✅ 4. Validasi Data Sebelum Menyimpan

```cpp
bool isValidPlayer(const Player& p) {
    // Cek nama tidak kosong
    if (p.nama.empty()) return false;
    
    // Cek tidak ada nilai negatif
    if (p.totalGames < 0 || p.totalWins < 0 || 
        p.totalDraws < 0 || p.totalLosses < 0) {
        return false;
    }
    
    // Cek konsistensi
    if (p.totalWins + p.totalDraws + p.totalLosses != p.totalGames) {
        return false;
    }
    
    return true;
}

void savePlayers(const vector<Player>& players) {
    ofstream file(FILENAME);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    
    int savedCount = 0;
    for (const auto& p : players) {
        if (isValidPlayer(p)) {
            file << p.nama << " " << p.totalGames << " " << ...;
            savedCount++;
        } else {
            cerr << "Skipping invalid player: " << p.nama << endl;
        }
    }
    
    file.close();
    cout << savedCount << " players saved successfully" << endl;
}
```

---

### ✅ 5. Error Handling yang Proper

```cpp
#include <stdexcept>

void savePlayers(const vector<Player>& players) {
    try {
        ofstream file(FILENAME);
        
        if (!file.is_open()) {
            throw runtime_error("Cannot open file: " + FILENAME);
        }
        
        for (const auto& p : players) {
            file << p.nama << " " << p.totalGames << " " << ...;
            
            if (file.fail()) {
                throw runtime_error("Write error for player: " + p.nama);
            }
        }
        
        file.close();
        cout << "✅ Save successful" << endl;
        
    } catch (const exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        // Bisa tambahkan logging atau recovery mechanism
    }
}
```

---

### ✅ 6. Gunakan Append Mode dengan Hati-hati

```cpp
// Mode Overwrite (default)
ofstream file(FILENAME);  // Hapus isi lama

// Mode Append
ofstream file(FILENAME, ios::app);  // Tambah di akhir

// Use case untuk Append: Logging
void logActivity(const string& activity) {
    ofstream logFile("activity.log", ios::app);
    if (logFile.is_open()) {
        time_t now = time(0);
        logFile << ctime(&now) << ": " << activity << endl;
        logFile.close();
    }
}

// ⚠️ PERHATIAN: Jangan gunakan append untuk data players!
// Karena akan duplicate data setiap kali save
```

---

### ✅ 7. Gunakan Binary Mode untuk Data Besar

```cpp
// Text mode (default) - Human readable
ofstream file("data.txt");

// Binary mode - Lebih cepat, ukuran lebih kecil
ofstream file("data.bin", ios::binary);

// Contoh save binary
struct Player {
    char nama[50];
    int totalGames;
    int totalWins;
    // ...
};

void saveBinary(const vector<Player>& players) {
    ofstream file("players.bin", ios::binary);
    
    if (!file.is_open()) {
        cerr << "Error!" << endl;
        return;
    }
    
    // Tulis jumlah players
    size_t count = players.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    
    // Tulis semua players
    for (const auto& p : players) {
        file.write(reinterpret_cast<const char*>(&p), sizeof(Player));
    }
    
    file.close();
}

// Load binary
vector<Player> loadBinary() {
    vector<Player> players;
    ifstream file("players.bin", ios::binary);
    
    if (!file.is_open()) return players;
    
    // Baca jumlah players
    size_t count;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));
    
    // Baca semua players
    players.resize(count);
    for (auto& p : players) {
        file.read(reinterpret_cast<char*>(&p), sizeof(Player));
    }
    
    file.close();
    return players;
}
```

---

## 7. Checklist Implementasi

### ✅ Checklist File I/O untuk Tic-Tac-Toe

Gunakan checklist ini untuk memastikan implementasi Anda lengkap:

#### 📁 Setup Awal
- [ ] Include semua library yang diperlukan (`<fstream>`, `<vector>`, `<string>`)
- [ ] Definisikan struct `Player` dengan semua field yang diperlukan
- [ ] Buat konstanta untuk nama file (`const string FILENAME = "players.txt"`)

#### 💾 Fungsi savePlayers()
- [ ] Buat objek `ofstream`
- [ ] Buka file dengan `open()` atau di constructor
- [ ] **Validasi:** Cek `is_open()` sebelum menulis
- [ ] Loop melalui vector dan tulis setiap player
- [ ] Gunakan delimiter yang konsisten (spasi/koma/dll)
- [ ] Tambahkan `endl` atau `\n` di akhir setiap baris
- [ ] **Tutup file** dengan `close()`
- [ ] Tampilkan pesan konfirmasi

#### 📂 Fungsi loadPlayers()
- [ ] Buat vector kosong untuk return value
- [ ] Buat objek `ifstream`
- [ ] Buka file dengan `open()` atau di constructor
- [ ] **Validasi:** Cek `is_open()`, return vector kosong jika gagal
- [ ] Loop dengan `while (file >> ...)` untuk membaca data
- [ ] Parse setiap field sesuai format
- [ ] Push setiap player ke vector
- [ ] **Tutup file** dengan `close()`
- [ ] Return vector hasil

#### 🛡️ Error Handling
- [ ] Cek file exists sebelum load
- [ ] Handle file open failure dengan message yang jelas
- [ ] Validasi data setelah membaca (cek nilai negatif, konsistensi)
- [ ] Handle corrupted data (skip atau tampilkan warning)

#### 🎮 Integrasi dengan Program
- [ ] Panggil `loadPlayers()` di awal program (main)
- [ ] Simpan return value ke vector global/local
- [ ] Panggil `savePlayers()` sebelum program exit
- [ ] Tambahkan menu option untuk save manual
- [ ] Tambahkan menu option untuk reload data
- [ ] Auto-save setelah setiap perubahan data (optional)

