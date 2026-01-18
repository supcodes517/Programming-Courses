#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <string>

using namespace std;

// ================= STRUCT PLAYER =================
struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

// ================= GLOBAL DATA =================
vector<Player> players;

int skorPlayer = 0;
int skorComputer = 0;

// ================= LOAD PLAYER DATA =================
void loadPlayerData() {
    ifstream file("player_data.txt");
    if (!file) return;

    Player p;
    while (file >> p.nama >> p.totalGames >> p.totalWins
                >> p.totalDraws >> p.totalLosses >> p.score) {
        players.push_back(p);
    }
    file.close();
}

// ================= SAVE PLAYER DATA =================
void savePlayerData() {
    ofstream file("player_data.txt");
    
    for(int i = 0; i < players.size(); i++){
    	
    	file << players[i].nama << " "
    	
    		 	<< players[i].totalGames << " "
    		 	
    		 		<< players[i].totalWins << " "
    		 		
    		 			<< players[i].totalDraws << " "
    		 			
    		 				<< players[i].totalLosses << " "
    		 				
    		 					<< players[i].score << endl;
	}
	
    file.close();
}



// ================= UTIL DASAR =================
void delay3() {
    Sleep(3000);
}

// ================= PROTOTYPE GAME =================
void menuUtama();
void tutorialPermainan();

void resetBoard();
void tampilBoard();
bool cekMenang(char simbol);
bool cekSeri();

void mulaiPermainan();
void menuModeBermain();
int menuLevel();
void panduanGame();
void loadingEnteringGame();

void vsComputerEasy();
void vsComputerMedium();
void vsComputerHard();

void vs2Player();
void tampilDaftarPlayer();
void resetDataPlayer();

int pilihAtauTambahPlayer();
int pilihPemain();       
int aiMediumMove(char ai, char player);
int aiHardMove(char ai, char player);

void tampilSkorVsComputer();
void tampilLeaderboard();
void simpanLeaderboardKeFile();
int menuSetelahGame();

void loadingBesar();
void tampilThankYou();
bool konfirmasiKeluar();

//=========================================================

void tekanEnter() {
    cin.ignore(1000, '\n');
    cin.get();
}

// ================= DAFTAR PLAYER =================
void tampilDaftarPlayer() {
    cout << "\n================ DAFTAR PLAYER ================\n";
    if (players.empty()) {
        cout << "Belum ada player yang tersimpan.\n";
        return;
    }

    for (int i = 0; i < players.size(); i++) {
        cout << i + 1 << ". " << players[i].nama << endl;
    }
    cout << "===============================================\n";
}

// ==================== TAMPILAN LEADERBOARD ====================
void tampilLeaderboard() {
    loadingBesar(); // <-- PANGGIL LOADING TIC TAC TOE DISINI

    system("cls");

    if (players.empty()) {
        cout << "Belum ada data player.\n";
        system("pause");
        return;
    }

    // Urutkan berdasarkan skor (DESC)
    for (int i = 0; i < players.size() - 1; i++) {
        for (int j = i + 1; j < players.size(); j++) {
            if (players[j].score > players[i].score) {
                swap(players[i], players[j]);
            }
        }
    }

    cout << "==================== LEADERBOARD ====================\n";
    cout << left
         << setw(4)  << "No"
         << setw(12) << "Nama"
         << setw(8)  << "Main"
         << setw(8)  << "Menang"
         << setw(8)  << "Seri"
         << setw(8)  << "Kalah"
         << setw(6)  << "Skor" << endl;
    cout << "-----------------------------------------------------\n";

    for (int i = 0; i < players.size(); i++) {
        cout << setw(4)  << i + 1
             << setw(12) << players[i].nama
             << setw(8)  << players[i].totalGames
             << setw(8)  << players[i].totalWins
             << setw(8)  << players[i].totalDraws
             << setw(8)  << players[i].totalLosses
             << setw(6)  << players[i].score << endl;
    }

    cout << "=====================================================\n";

    system("pause");
}

void resetDataPlayer() {
    system("cls");

    char konfirmasi;
    cout << "=========================================\n";
    cout << "        KONFIRMASI RESET DATA\n";
    cout << "=========================================\n";
    cout << "PERINGATAN!\n";
    cout << "Semua data player dan leaderboard\n";
    cout << "akan DIHAPUS PERMANEN.\n\n";
    cout << "Apakah Anda yakin? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        players.clear();                

        ofstream file("player_data.txt");
        file.close();

        loadingBesar();

        cout << "\nData berhasil direset.\n";
        cout << "Tekan ENTER untuk kembali ke menu...\n";
        tekanEnter();
    }
    else {
        cout << "\nReset data dibatalkan.\n";
        cout << "Tekan ENTER untuk kembali ke menu...\n";
        tekanEnter();
    }
}



// =============== SIMPAN FILE ===============
void simpanLeaderboardKeFile() {
    ofstream file("leaderboard.txt");

    file << "No Nama Main Menang Seri Kalah Skor\n";

    for (int i = 0; i < players.size(); i++) {
        file << i + 1 << " "
             << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }

    file.close();
}



// ================= PILIH / TAMBAH PLAYER =================
int pilihAtauTambahPlayer() {
    int pilihan;

    while (true) {
        system("cls");
        cout << "============== PLAYER ==============\n";
        cout << "1. Pilih player yang sudah ada\n";
        cout << "2. Tambah player baru\n";
        cout << "====================================\n";
        cout << "Masukkan pilihan (1-2): ";
        cin >> pilihan;

        if (pilihan == 1) {
            if (players.empty()) {
                cout << "\nBelum ada player tersimpan. Silakan tambah player baru.\n";
                system("pause");
                continue;
            }

            tampilDaftarPlayer();
            cout << "Pilih nomor player: ";
            int idx;
            cin >> idx;

            if (idx < 1 || idx > players.size()) {
                cout << "\nPilihan tidak valid!\n";
                system("pause");
                continue;
            }

            return idx - 1;
        }
        else if (pilihan == 2) {
            Player p;
            cout << "Masukkan nama player baru: ";
            cin >> p.nama;

            p.totalGames = 0;
            p.totalWins = 0;
            p.totalDraws = 0;
            p.totalLosses = 0;
            p.score = 0;

            players.push_back(p);
            return players.size() - 1;
        }
        else {
            cout << "\nPilihan tidak valid! Silakan pilih 1 atau 2.\n";
            system("pause");
        }
    }
}


// ================= TUTORIAL VISUAL =================
void tutorialPermainan() {
    system("cls");

    cout << "============================================================\n";
    cout << "                    TUTORIAL PERMAINAN\n";
    cout << "                      TIC TAC TOE\n";
    cout << "============================================================\n\n";

    cout << "Permainan ini dimainkan pada papan 3 x 3 berbentuk kotak.\n";
    cout << "Setiap pemain bergiliran mengisi satu kotak kosong.\n\n";

    cout << "SIMBOL PEMAIN:\n";
    cout << "O  = Pemain Pertama\n";
    cout << "X  = Pemain Kedua / Komputer\n\n";

    cout << "------------------------------------------------------------\n";
    cout << "         CONTOH PAPAN KOSONG DENGAN NOMOR POSISI\n";
    cout << "------------------------------------------------------------\n\n";

    cout << "     |     |     \n";
    cout << "  1  |  2  |  3  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  4  |  5  |  6  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  7  |  8  |  9  \n\n";

    cout << "Angka 1 - 9 digunakan untuk memilih posisi.\n\n";
    system("pause");
    system("cls");

    cout << "------------------------------------------------------------\n";
    cout << "                 CONTOH LANGKAH PEMAIN O\n";
    cout << "------------------------------------------------------------\n\n";

    cout << "Pemain O memilih posisi 5 (tengah)\n\n";

    cout << "     |     |     \n";
    cout << "     |     |     \n";
    cout << "_____|_____|_____\n";
    cout << "     |  O  |     \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n\n";

    system("pause");
    system("cls");

    cout << "------------------------------------------------------------\n";
    cout << "                 CONTOH KONDISI MENANG\n";
    cout << "------------------------------------------------------------\n\n";

    cout << "  O  |  O  |  O  \n";
    cout << "_____|_____|_____\n";
    cout << "  X  |     |     \n";
    cout << "_____|_____|_____\n";
    cout << "  X  |     |     \n\n";

    cout << "MENANG terjadi jika simbol sejajar:\n";
    cout << "- Horizontal\n";
    cout << "- Vertikal\n";
    cout << "- Diagonal\n\n";

    system("pause");
    system("cls");

    cout << "------------------------------------------------------------\n";
    cout << "                  CONTOH KONDISI SERI\n";
    cout << "------------------------------------------------------------\n\n";

    cout << "  O  |  X  |  O  \n";
    cout << "_____|_____|_____\n";
    cout << "  X  |  O  |  X  \n";
    cout << "_____|_____|_____\n";
    cout << "  X  |  O  |  X  \n\n";

    cout << "Jika semua kotak terisi dan tidak ada pemenang,\n";
    cout << "maka hasilnya adalah SERI.\n\n";

    cout << "------------------------------------------------------------\n";
    cout << "                    SISTEM PENILAIAN\n";
    cout << "------------------------------------------------------------\n";
    cout << "MENANG : +3 POIN\n";
    cout << "SERI   : +1 POIN\n";
    cout << "KALAH  : +0 POIN\n\n";

    cout << "TUTORIAL SELESAI.\n";
    cout << "Tekan ENTER untuk kembali ke menu...\n";
    tekanEnter();
}

void loadingBesar() {
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10); 

    cout << "\n\n\n";

    const char* title[] = {
        " ¦¦¦¦¦¦¦¦¦+ ¦¦¦+ ¦¦¦¦¦¦+     ¦¦¦¦¦¦¦¦¦+ ¦¦¦¦¦+   ¦¦¦¦¦¦+     ¦¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+ ",
        " +--¦¦¦+--+ ¦¦¦ ¦¦+----+     +--¦¦¦+-- ¦¦¦+--¦¦+¦¦+----+     +--¦¦¦+--+ ¦¦+---¦¦+ ¦¦+----+ ",
        "    ¦¦¦     ¦¦¦ ¦¦¦             ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦             ¦¦¦     ¦¦¦   ¦¦¦ ¦¦¦¦¦+   ",
        "    ¦¦¦     ¦¦¦ ¦¦¦             ¦¦¦    ¦¦+--¦¦¦ ¦¦¦             ¦¦¦     ¦¦¦   ¦¦¦ ¦¦+--+   ",
        "    ¦¦¦     ¦¦¦+ ¦¦¦¦¦¦+        ¦¦¦    ¦¦¦  ¦¦¦+ ¦¦¦¦¦¦+        ¦¦¦   +  ¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+ ",
        "    +-+    +---+ +-----+       +---+   +-+  +-+ +--------+    +------+  +--------+ +-------+ "
    };

    for (int i = 0; i < 6; i++) {
        cout << title[i] << endl;
        Sleep(180); 
    }

    cout << "\n\n";

    cout << "                                INITIALIZING GAME";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(400);
    }

    cout << "\n\n";

    for (int i = 0; i <= 100; i++) {
        cout << "\r               [";
        int bar = i / 2;

        for (int j = 0; j < bar; j++) cout << "*";
        for (int j = bar; j < 50; j++) cout << " ";

        cout << "]  " << i << "%";
        Sleep(22); 
    }

    SetConsoleTextAttribute(hConsole, 7); 
    Sleep(600);
    system("cls");
}

// ================= MENU UTAMA =================
void menuUtama() {
    system("cls");
    cout << "===========================================\n";
    cout << "  SELAMAT DATANG DI PERMAINAN TIC TAC TOE \n";
    cout << "===========================================\n\n";
    cout << endl;
    
    cout << "---------- MENU UTAMA ----------\n";
    cout << "1. Mulai Bermain \n";
    cout << "2. Leaderboard\n";
    cout << "3. Reset Data\n";
    cout << "4. Keluar\n\n";
    cout << endl;
    
    cout << "=================================\n";
    cout << "Masukkan menu pilihan Anda (1-4): ";
}

//==================== CLOSE PROGRAM ====================
void tampilThankYou() {
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10); 

    vector<string> lines;

    lines.push_back("  _______ _                 _   _   _                     ");
    lines.push_back(" |__   __| |               | | | | | |                    ");
    lines.push_back("    | |  | |__   __ _ _ __ | |_| |_| | ___  _ __ ___      ");
    lines.push_back("    | |  | '_ \\ / _` | '_ \\| __| __| |/ _ \\| '__/ _ \\     ");
    lines.push_back("    | |  | | | | (_| | | | | |_| |_| | (_) | | |  __/     ");
    lines.push_back("    |_|  |_| |_|\\__,_|_| |_|\\__|\\__|_|\\___/|_|  \\___|     ");
    lines.push_back("");
    lines.push_back("  _______ _    _   _   _   _   _   _   _   _           ");
    lines.push_back(" |__   __| |  | | | | | | | | | | | | | | | | |          ");
    lines.push_back("    | |  | |__| | | | | | | | | | | | | | | | |          ");
    lines.push_back("    | |  |  __  | | | | | | | | | | | | | | | |          ");
    lines.push_back("    | |  | |  | | | |_| |_| |_| |_| |_| |_| |_|          ");
    lines.push_back("    |_|  |_|  |_|  \\___/ \\___/ \\___/ \\___/              ");
    lines.push_back("");
    lines.push_back("                 TIC TAC TOE                             ");

    // Animasi masuk per baris
    for (int i = 0; i < (int)lines.size(); i++) {
        for (int j = 0; j < (int)lines[i].size(); j++) {
            cout << lines[i][j];
            Sleep(6); 
        }
        cout << "\n";
        Sleep(40); 
    }

    cout << "\n\n";
    SetConsoleTextAttribute(hConsole, 7); 
    Sleep(3000); 
}




//=============== KONFIRMASI CLOSE PROGRAM ===============
bool konfirmasiKeluar() {
    system("cls");

    char pilih;
    cout << "=================================\n";
    cout << "        KONFIRMASI KELUAR\n";
    cout << "=================================\n";
    cout << "Apakah Anda yakin ingin keluar?\n";
    cout << "(y/n): ";
    cin >> pilih;

    if (pilih == 'y' || pilih == 'Y') {
        savePlayerData();  
        tampilThankYou();
        return true;       
    }
    else {
        return false;      
    }
}


// ================= MAIN (AWAL) =================
int main() {
    srand(time(0));
    loadPlayerData();
    
    loadingBesar();

    int pilihan;
    do {
        menuUtama();
        cin >> pilihan;

        if (pilihan == 1) {
    		loadingBesar(); 

    		char tut;
    		
    		system("cls");
    		
    		cout << "Apakah Anda ingin melihat tutorial bermain? (y/n): ";
    		cin >> tut;

    		if (tut == 'y' || tut == 'Y') {
        	tutorialPermainan();
			
			loadingBesar();
				
			}
    		mulaiPermainan();
		}
        else if (pilihan == 2) {
            tampilLeaderboard();
        }

        else if (pilihan == 3) {
            resetDataPlayer();
        }
        
        else if (pilihan == 4){
        	if (konfirmasiKeluar()){
        		break;
			}
		}

    } while (true);

    return 0;
}
// ================= PAPAN PERMAINAN =================
char board[10];

void resetBoard() {
    for (int i = 1; i <= 9; i++) {
        board[i] = ' ';
    }
}

// ================= TAMPIL PAPAN =================
void tampilBoard() {
    system("cls");
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << board[1] << "  |  " << board[2] << "  |  " << board[3] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[4] << "  |  " << board[5] << "  |  " << board[6] << "  \n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[7] << "  |  " << board[8] << "  |  " << board[9] << "  \n\n";
}

// ================= CEK MENANG =================
bool cekMenang(char simbol) {
    return (
        (board[1] == simbol && board[2] == simbol && board[3] == simbol) ||
        (board[4] == simbol && board[5] == simbol && board[6] == simbol) ||
        (board[7] == simbol && board[8] == simbol && board[9] == simbol) ||
        (board[1] == simbol && board[4] == simbol && board[7] == simbol) ||
        (board[2] == simbol && board[5] == simbol && board[8] == simbol) ||
        (board[3] == simbol && board[6] == simbol && board[9] == simbol) ||
        (board[1] == simbol && board[5] == simbol && board[9] == simbol) ||
        (board[3] == simbol && board[5] == simbol && board[7] == simbol)
    );
}

// ================= CEK SERI =================
bool cekSeri() {
    for (int i = 1; i <= 9; i++) {
        if (board[i] == ' ')
            return false;
    }
    return true;
}

// ================= MODE BERMAIN =================
void menuModeBermain() {
	
    system("cls");
    
    cout << "=============================================\n";
    cout << "              SELAMAT DATANG!\n";
	cout << "        MARI TUNJUKKAN PERMAINAN ANDA\n";
    cout << "=============================================\n";

    cout << "------------- MODE BERMAIN -------------\n";
    cout << "1. Vs Computer\n";
    cout << "2. Vs 2 Player\n\n";
    cout << endl;
    
    cout << "Masukkan Mode Permainan Anda (1-2): ";
}

// ================= MENU LEVEL =================
int menuLevel() {
    int lvl;
    system("cls");
    cout << "==============================\n";
    cout << "    PERMAINAN VS COMPUTER\n";
    cout << "==============================\n\n";
    cout << "1. Easy\n";
    cout << "2. Medium\n";
    cout << "3. Hard\n\n";
    cout << "Masukkan Pilihan (1-3): ";
    cin >> lvl;
    return lvl;
}

// ================= PANDUAN SEBELUM GAME =================
void panduanGame() {
  system("cls");
cout << "=================================\n";
cout << "        PANDUAN BERMAIN\n";
cout << "=================================\n\n";

cout << "O  = Pemain Pertama\n";
cout << "X  = Pemain Kedua / Computer\n\n";

cout << "---------------------------------\n";
cout << "Tekan ENTER untuk memulai permainan\n";
cout << "---------------------------------\n";

cin.ignore();
cin.get();

loadingEnteringGame();

}


// ===== LOADING KHUSUS SETELAH TUTORIAL =====
void loadingEnteringGame() {
    system("cls");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10); 
    cout << "\n\n";

    const char* enterGame[] = {
        " ¦¦¦¦¦¦¦+¦¦¦+   ¦¦+¦¦¦¦¦¦¦¦+¦¦¦¦¦¦¦+¦¦¦¦¦¦+ ¦¦+¦¦¦+   ¦¦+ ¦¦¦¦¦¦+ ",
        " ¦¦+----+¦¦¦¦+  ¦¦¦+--¦¦+--+¦¦+----+¦¦+--¦¦+¦¦¦¦¦¦¦+  ¦¦¦¦¦+----+ ",
        " ¦¦¦¦¦+  ¦¦+¦¦+ ¦¦¦   ¦¦¦   ¦¦¦¦¦+  ¦¦¦¦¦¦++¦¦¦¦¦+¦¦+ ¦¦¦¦¦¦  ¦¦¦+",
        " ¦¦+--+  ¦¦¦+¦¦+¦¦¦   ¦¦¦   ¦¦+--+  ¦¦+--¦¦+¦¦¦¦¦¦+¦¦+¦¦¦¦¦¦   ¦¦¦",
        " ¦¦¦¦¦¦¦+¦¦¦ +¦¦¦¦¦   ¦¦¦   ¦¦¦¦¦¦¦+¦¦¦  ¦¦¦¦¦¦¦¦¦ +¦¦¦¦¦+¦¦¦¦¦¦++",
        " +------++-+  +---+   +-+   +------++-+  +-++-++-+  +---+ +-----+ "
    };

    for (int i = 0; i < 6; i++) {
        cout << "   " << enterGame[i] << endl;
        Sleep(170);
    }

    cout << "\n";

    cout << "                            PREPARING MATCH";
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(400);
    }

    cout << "\n\n";

    
    for (int i = 0; i <= 100; i++) {
        cout << "\r          [";
        int bar = i / 2;

        for (int j = 0; j < bar; j++) cout << "#";
        for (int j = bar; j < 50; j++) cout << " ";

        cout << "] " << i << "%";
        Sleep(20);
    }

    SetConsoleTextAttribute(hConsole, 7); 
    Sleep(500);
    system("cls");
}

// ================= PILIH PEMAIN =================
int pilihPemain() {
    int pilih;
    system("cls");
    cout << "--------------------------------\n";
    cout << "1. Player pertama\n";
    cout << "2. Player kedua\n";
    cout << "--------------------------------\n";
    cout << "Masukkan Pilihan (1-2): ";
    cin >> pilih;
    return pilih;
}

// ================= CONTROLLER GAME =================
void mulaiPermainan() {
    int mode;
    menuModeBermain();
    cin >> mode;

    if (mode == 1) { 
        int level = menuLevel();
        panduanGame();

        if (level == 1) {
            vsComputerEasy();
        }
        else if (level == 2) {
            vsComputerMedium();
        }
        else if (level == 3) {
            vsComputerHard();
        }
    }
    else if (mode == 2) {
    	panduanGame();
    	vs2Player();
	}
}


// ================= VS COMPUTER EASY =================
void vsComputerEasy() {
    resetBoard();
    char player = 'O';
    char computer = 'X';
    int langkah;

    while (true) {
        tampilBoard();
        cout << "Giliran Player (O)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> langkah;

        if (langkah < 1 || langkah > 9 || board[langkah] != ' ')
            continue;

        board[langkah] = player;

        if (cekMenang(player)) {
            tampilBoard();
            cout << "PLAYER MENANG!\n";
            skorPlayer += 3;
            break;
        }

        if (cekSeri()) {
            tampilBoard();
            cout << "HASIL SERI!\n";
            skorPlayer += 1;
            skorComputer += 1;
            break;
        }

        // COMPUTER EASY (RANDOM)
        do {
            langkah = rand() % 9 + 1;
        } while (board[langkah] != ' ');
        board[langkah] = computer;

        if (cekMenang(computer)) {
            tampilBoard();
            cout << "COMPUTER MENANG!\n";
            skorComputer += 3;
            break;
        }
    }

    int pilihan;
    
        tampilSkorVsComputer();

        pilihan = menuSetelahGame();

        if (pilihan == 1) {
    		loadingEnteringGame();   
    return;                  
		
		}else if (pilihan == 2) {
    		loadingBesar();         
    return;                  
		
		}

}


// ================= SISTEM PENILAIAN =================
void tampilSkorVsComputer() {
    cout << "\n-----------------------------------\n";
    cout << "HASIL PENILAIAN:\n";
    cout << "Player   : " << skorPlayer << " poin\n";
    cout << "Computer : " << skorComputer << " poin\n";
    cout << "-----------------------------------\n";
}

void tampilSkorVs2Player(Player &p1, Player &p2) {
    cout << "\n======================================\n";
    cout << "        HASIL PERTANDINGAN\n";
    cout << "========================================\n";

    cout << left << setw(12) << "Nama"
         << setw(8) << "Menang"
         << setw(8) << "Seri"
         << setw(8) << "Kalah"
         << setw(6) << "Skor\n";

    cout << "---------------------------------------\n";

    cout << setw(12) << p1.nama
         << setw(8) << p1.totalWins
         << setw(8) << p1.totalDraws
         << setw(8) << p1.totalLosses
         << setw(6) << p1.score << endl;

    cout << setw(12) << p2.nama
         << setw(8) << p2.totalWins
         << setw(8) << p2.totalDraws
         << setw(8) << p2.totalLosses
         << setw(6) << p2.score << endl;

    cout << "=======================================\n";
}



// ================= MENU SETELAH GAME =================
int menuSetelahGame() {
    int pilih;
    cout << "\n-----------------------------------\n";
    cout << "1. Bermain kembali\n";
    cout << "2. Kembali ke menu utama\n";
    cout << "-----------------------------------\n";
    cout << "Masukkan pilihan (1-2): ";
    cin >> pilih;
    return pilih;
}

// ================= AI MEDIUM =================
int aiMediumMove(char ai, char player) {
    
    for (int i = 1; i <= 9; i++) {
        if (board[i] == ' ') {
            board[i] = ai;
            if (cekMenang(ai)) {
                board[i] = ' ';
                return i;
            }
            board[i] = ' ';
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (board[i] == ' ') {
            board[i] = player;
            if (cekMenang(player)) {
                board[i] = ' ';
                return i;
            }
            board[i] = ' ';
        }
    }

    int move;
    do {
        move = rand() % 9 + 1;
    } while (board[move] != ' ');
    return move;
}

// ================= AI HARD =================
int aiHardMove(char ai, char player) {
    // Menang
    for (int i = 1; i <= 9; i++) {
        if (board[i] == ' ') {
            board[i] = ai;
            if (cekMenang(ai)) {
                board[i] = ' ';
                return i;
            }
            board[i] = ' ';
        }
    }

    for (int i = 1; i <= 9; i++) {
        if (board[i] == ' ') {
            board[i] = player;
            if (cekMenang(player)) {
                board[i] = ' ';
                return i;
            }
            board[i] = ' ';
        }
    }

    if (board[5] == ' ')
        return 5;

    int sudut[4] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        if (board[sudut[i]] == ' ')
            return sudut[i];
    }

    int move;
    do {
        move = rand() % 9 + 1;
    } while (board[move] != ' ');
    return move;
}

// ================= VS COMPUTER MEDIUM =================
void vsComputerMedium() {
    system("cls");
    resetBoard();

    char player = 'O';
    char computer = 'X';
    int langkah;
    bool gameOver = false;

    while (!gameOver) {
        tampilBoard(); 

        cout << "Giliran Player (O)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> langkah;

        if (langkah < 1 || langkah > 9 || board[langkah] != ' ') {
            cout << "Posisi tidak valid!\n";
            Sleep(700);
            system("cls");
            continue;
        }

        board[langkah] = player;

        if (cekMenang(player)) {
            system("cls");
            tampilBoard();
            cout << "Player MENANG!\n";
            skorPlayer += 3;  
            gameOver = true;
        }
        else if (cekSeri()) {
            system("cls");
            tampilBoard();
            cout << "Permainan SERI!\n";
            skorPlayer += 1;
            skorComputer += 1;
            gameOver = true;
        }
        else {
            
            int aiMove = aiMediumMove(computer, player);
            board[aiMove] = computer;

            if (cekMenang(computer)) {
                system("cls");
                tampilBoard();
                cout << "Computer MENANG!\n";
                skorComputer += 3;
                gameOver = true;
            }
        }

        system("cls");
    }

    tampilSkorVsComputer();


    int ulang = menuSetelahGame();

    if (ulang == 1) {
        loadingEnteringGame();   
        return;
    }
    else if (ulang == 2) {
        loadingBesar();         
        return;
    }
}



// ================= VS COMPUTER HARD =================
void vsComputerHard() {
    resetBoard();
    char player = 'O';
    char computer = 'X';
    int langkah;

    while (true) {
        tampilBoard();
        cout << "Giliran Player (O)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> langkah;

        if (langkah < 1 || langkah > 9 || board[langkah] != ' ')
            continue;

        board[langkah] = player;

        if (cekMenang(player)) {
            tampilBoard();
            cout << "PLAYER MENANG!\n";
            skorPlayer += 3;
            break;
        }

        if (cekSeri()) {
            tampilBoard();
            cout << "HASIL SERI!\n";
            skorPlayer += 1;
            skorComputer += 1;
            break;
        }

        langkah = aiHardMove(computer, player);
        board[langkah] = computer;

        if (cekMenang(computer)) {
            tampilBoard();
            cout << "COMPUTER MENANG!\n";
            skorComputer += 3;
            break;
        }
    }

    tampilSkorVsComputer();


    int ulang = menuSetelahGame();

    if (ulang == 1) {
        loadingEnteringGame(); 
        return;                
    }
    else if (ulang == 2) {
        loadingBesar();       
        return;                
    }
}

void vs2Player() {
    resetBoard();

    cout << "========== SET UP PLAYER ==========\n";
    cout << "Pilih Player 1 (O) \n";
    int idxp1 = pilihAtauTambahPlayer();

    int idxp2;
    while (true) {
        cout << "Pilih Player 2 (X) \n";
        idxp2 = pilihAtauTambahPlayer();

        if (idxp2 == idxp1) {
            cout << "\nPlayer 2 tidak boleh sama dengan Player 1!\n";
            system("pause");
            continue;
        }
        break;
    }

    Player &p1 = players[idxp1];
    Player &p2 = players[idxp2];

    p1.totalGames++;
    p2.totalGames++;

    skorPlayer = 0;
    skorComputer = 0;

    char player1 = 'O';
    char player2 = 'X';

    int langkah;
    bool giliranPlayer1 = true;

    while (true) {
        tampilBoard();

        if (giliranPlayer1)
            cout << "Giliran " << p1.nama << " (O)\n";
        else
            cout << "Giliran " << p2.nama << " (X)\n";

        cout << "Masukkan posisi (1-9): ";
        cin >> langkah;

        if (langkah < 1 || langkah > 9 || board[langkah] != ' ') {
            cout << "\nPosisi tidak valid!\n";
            Sleep(700);
            continue;
        }

        board[langkah] = giliranPlayer1 ? player1 : player2;

        if (cekMenang(giliranPlayer1 ? player1 : player2)) {
            tampilBoard();

            if (giliranPlayer1) {
                cout << p1.nama << " MENANG!\n";
                p1.totalWins++;
                p2.totalLosses++;
                p1.score += 3;
            } else {
                cout << p2.nama << " MENANG!\n";
                p2.totalWins++;
                p1.totalLosses++;
                p2.score += 3;
            }
            break;
        }

        if (cekSeri()) {
            tampilBoard();
            cout << "HASIL SERI!\n";
            p1.totalDraws++;
            p2.totalDraws++;
            p1.score++;
            p2.score++;
            break;
        }

        giliranPlayer1 = !giliranPlayer1;
    }

    tampilSkorVs2Player(p1, p2);


    int pilihan = menuSetelahGame();

    if (pilihan == 1) {
        loadingEnteringGame();
        vs2Player(); 
    }
    else {
        loadingBesar();
        savePlayerData();
    }
}
