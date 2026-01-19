//===================================
//	Nama	: Talitha Yamilla Syahla
//	Nim		: 2500018032
//  Kelas	: A
//	Projek DDP TIC TAC
//===================================
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>
using namespace std;

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

vector<Player> players;
int currentPlayer = -1;

int indexPlayer1 = -1;
int indexPlayer2 = -1;
string hasilPertandinganVsPlayer;

struct Computer {
    int wins;
    int draws;
    int losses;
    int score;
};

Computer komputer;

string hasilPertandinganVsComputer;

void playVsPlayer();
void playVsComputer();
void pilihModePermainan();
void pilihPlayerVsPlayer();
void menuVsComputer();
void tampilkanTutorial();
void hasilVsComputer();
void hasilVsPlayer();
void menuLeaderboard();
void playerMenu();

void tampilanAwal() {
    system("cls");

    cout << endl << endl;
    cout << "            _____ _        _____            _____              " << endl;
    cout << "           |_   _(_) ___  |_   _|_ _  ___  |_   _|__    ___     " << endl;
    cout << "             | | | |/ __|   | |/ _` |/ __|   | |/ _ \\ / _ \\   " << endl;
    cout << "             | | | | (__    | | (_| | (__    | | (_) |  __/    " << endl;
    cout << "             |_| |_|\\___|__| |\\__,|\\___|__|_|\\___/ \\\\________    " << endl;

    cout << endl;
    cout << "                        ===== TIC TAC TOE =====              " << endl;
    cout << "                 Tekan ENTER untuk melanjutkan...            " << endl;

    cin.get(); 
}


void menuUtama() {
    int pilih;
    
    do {
        system("cls");

        cout << endl << endl;
        cout << "   ========================================================================   " << endl;
        cout << "   |                             TIC TAC TOE                              |" << endl;
        cout << "   ========================================================================   " << endl;
        cout << endl;
        
        cout << "                        1. Masuk Menu Player    " << endl;
        cout << "                        2. Keluar               " << endl;
        cout << endl;
        
        cout << "   ========================================================================   " << endl;
        cout << endl;
        
        cout << "   Pilih Menu: ";
        cin >> pilih;

        if (pilih == 1) {
            system("cls");
            playerMenu(); 
        }
        else if (pilih == 2) {
            system("cls");
            cout << "Terima kasih telah bermain!\n";
            Sleep(1500);
        }
        else {
            cout << "Pilihan tidak valid!";
            Sleep(1500);
        }

    } while (pilih != 2);
}

void loadPlayers() {
    ifstream file("players.txt");
    if (!file.is_open()) return;

    players.clear();
    Player p;
    while (file >> p.nama >> p.totalGames >> p.totalWins
                >> p.totalDraws >> p.totalLosses >> p.score) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers() {
    ofstream file("players.txt");
    for (int i = 0; i < players.size(); i++) {
        file << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }
    file.close();
}

void displayGuideBoard() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3 \n";
    cout << "---+---+---\n";
    cout << " 4 | 5 | 6 \n";
    cout << "---+---+---\n";
    cout << " 7 | 8 | 9 \n\n";
}

void displayBoard(char board[3][3]) {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---+---+---\n";
    }
}

bool checkWin(char b[3][3], char p) {
    for (int i = 0; i < 3; i++)
        if (b[i][0] == p && b[i][1] == p && b[i][2] == p) return true;

    for (int j = 0; j < 3; j++)
        if (b[0][j] == p && b[1][j] == p && b[2][j] == p) return true;

    return (b[0][0] == p && b[1][1] == p && b[2][2] == p) ||
           (b[0][2] == p && b[1][1] == p && b[2][0] == p);
}

bool isBoardFull(char b[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (b[i][j] == ' ') return false;
    return true;
}

bool isValidMove(char b[3][3], int pos) {
    if (pos < 1 || pos > 9) return false;
    return b[(pos - 1) / 3][(pos - 1) % 3] == ' ';
}

void makeMove(char b[3][3], int pos, char p) {
    b[(pos - 1) / 3][(pos - 1) % 3] = p;
}

void playVsPlayer() {

    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char turn = 'X';
    int pos;

    Player &p1 = players[indexPlayer1];
    Player &p2 = players[indexPlayer2];

    system("cls");
    displayGuideBoard();
    cout << "\n" << p1.nama << " (X) vs " << p2.nama << " (O)\n";

    while (true) {
        displayBoard(board);

        Player &current = (turn == 'X') ? p1 : p2;
        cout << "\nGiliran " << current.nama << " : ";
        cin >> pos;

        if (!isValidMove(board, pos)) {
            cout << "Posisi tidak valid!\n";
            Sleep(1000);
            system("cls");
            continue;
        }

        makeMove(board, pos, turn);

        if (checkWin(board, turn)) {
            displayBoard(board);

            if (turn == 'X') {
                hasilPertandinganVsPlayer = p1.nama + " MENANG";
                p1.totalWins++; p1.score += 3;
                p2.totalLosses++;
            } else {
                hasilPertandinganVsPlayer = p2.nama + " MENANG";
                p2.totalWins++; p2.score += 3;
                p1.totalLosses++;
            }
            break;
        }

        if (isBoardFull(board)) {
            displayBoard(board);
            hasilPertandinganVsPlayer = "SERI";
            p1.totalDraws++; p2.totalDraws++;
            p1.score++; p2.score++;
            break;
        }

        turn = (turn == 'X') ? 'O' : 'X';
        system("cls");
    }

    p1.totalGames++;
    p2.totalGames++;
    savePlayers();
}


void hasilVsPlayer() {

    system("cls");
    cout << "Menghitung hasil pertandingan...\n";
    Sleep(2000);

    system("cls");
    Player &p1 = players[indexPlayer1];
    Player &p2 = players[indexPlayer2];

    cout << "==================================================" << endl;
    cout << "                 HASIL PERTANDINGAN               " << endl;
    cout << "==================================================" << endl;
    cout << "| HASIL AKHIR : " << setw(34) << left 
         << hasilPertandinganVsPlayer << "|" << endl;
    cout << "==================================================" << endl;

    cout << "| PLAYER 1                                       |" << endl;
    cout << "| Nama               : " << setw(25) << p1.nama << "|" << endl;
    cout << "| Total Score        : " << setw(25) << p1.score << "|" << endl;

    cout << "|------------------------------------------------|" << endl;

    cout << "| PLAYER 2                                       |" << endl;
    cout << "| Nama               : " << setw(25) << p2.nama << "|" << endl;
    cout << "| Total Score        : " << setw(25) << p2.score << "|" << endl;

    cout << "==================================================" << endl;

    cout << "\nTekan ENTER untuk kembali ke menu utama...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void playVsComputer() {
    char board[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    Player &p = players[currentPlayer];
    int pos;

    displayGuideBoard();
    cout << "\n" << p.nama << " (X) vs Komputer (O)\n";

    while (true) {
        displayBoard(board);
        cout << "\nGiliran " << p.nama << " : ";
        cin >> pos;

        if (!isValidMove(board, pos)) {
            cout << "Posisi tidak valid!\n";
            continue;
        }

        makeMove(board, pos, 'X');

        if (checkWin(board, 'X')) {
            displayBoard(board);
            cout << "\n" << p.nama << " MENANG!\n";

            p.totalWins++;
            p.score += 3;

            komputer.losses++;
            break;
        }

        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "\nSERI!\n";

            p.totalDraws++;
            p.score += 1;

            komputer.draws++;
            komputer.score += 1;
            break;
        }

        int c;
        do {
            c = rand() % 9 + 1;
        } while (!isValidMove(board, c));

        makeMove(board, c, 'O');

        if (checkWin(board, 'O')) {
            displayBoard(board);
            cout << "\nKomputer MENANG!\n";

            p.totalLosses++;

            komputer.wins++;
            komputer.score += 3;
            break;
        }
    }

    p.totalGames++;
    savePlayers();
}

void showLeaderboard() {
    cout << "\n===== LEADERBOARD =====\n";
    cout << left << setw(15) << "Nama"
         << setw(6) << "Main"
         << setw(6) << "Win"
         << setw(6) << "Draw"
         << setw(6) << "Lose"
         << setw(6) << "Score" << endl;

    for (int i = 0; i < players.size(); i++) {
        cout << left << setw(15) << players[i].nama
             << setw(6) << players[i].totalGames
             << setw(6) << players[i].totalWins
             << setw(6) << players[i].totalDraws
             << setw(6) << players[i].totalLosses
             << setw(6) << players[i].score << endl;
    }
}

void pilihModePermainan() {
    int mode;

    system("cls");
    cout << "===========================================\n";
    cout << "  SELAMAT DATANG DI PERMAINAN TIC TAC TOE  \n";
    cout << "===========================================\n\n";

    cout << "----- PILIH MODE -----\n";
    cout << "1. Vs Computer\n";
    cout << "2. Vs Player\n";
    cout << "----------------------\n";
    cout << "Masukkan Pilihan Mode Permainan (1-2): ";
    cin >> mode;

    // ===== VALIDASI INPUT =====
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nInput tidak valid!\n";
        Sleep(1500);
        return;
    }

    // ===== MODE VS COMPUTER =====
    if (mode == 1) {
        if (currentPlayer < 0 || currentPlayer >= players.size()) {
            cout << "\nPlayer belum dipilih!\n";
            Sleep(1500);
            return;
        }
        menuVsComputer();
    }

    // ===== MODE VS PLAYER =====
    else if (mode == 2) {
        if (players.size() < 2) {
            cout << "\nMinimal harus ada 2 player untuk mode Vs Player!\n";
            Sleep(2000);
            return;
        }
        pilihPlayerVsPlayer();
    }

    else {
        cout << "\nPilihan tidak valid!\n";
        Sleep(1500);
    }
}


void tampilkanTutorial() {
    cout << "=========================="<<endl;
    cout << "   TUTORIAL TIC TAC TOE   "<<endl;
    cout << "=========================="<<endl;

    cout << "1. SISTEM PERMAINAN\n";
    cout << "- Permainan dimainkan oleh 2 pemain (Player vs Komputer).\n";
    cout << "- Player menggunakan simbol X.\n";
    cout << "- Komputer menggunakan simbol O.\n";
    cout << "- Pemain mengisi papan secara bergantian.\n\n";

    cout << "2. POSISI PAPAN\n";
    cout << " 1 | 2 | 3 \n";
    cout << "---+---+---\n";
    cout << " 4 | 5 | 6 \n";
    cout << "---+---+---\n";
    cout << " 7 | 8 | 9 \n\n";

    cout << "3. KONDISI MENANG\n";
    cout << "- 3 simbol sejajar secara horizontal\n";
    cout << "- 3 simbol sejajar secara vertikal\n";
    cout << "- 3 simbol sejajar secara diagonal\n\n";

    cout << "4. SISTEM PENILAIAN\n";
    cout << "+ Menang : +3 Score\n";
    cout << "+ Seri   : +1 Score\n";
    cout << "+ Kalah  :  0 Score\n\n";

    cout << "Tekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void menuVsComputer() {
    char pilih;

    system("cls");
    cout << "==========================="<<endl;
    cout << "      MODE VS COMPUTER     "<<endl;
    cout << "==========================="<<endl;

    cout << "Apakah Anda Ingin Melihat Tutorial Permainan? (y/n): ";
    cin >> pilih;

    if (pilih == 'y' || pilih == 'Y') {
        system("cls");
        tampilkanTutorial();
    }

    system("cls");
    cout << "Permainan akan dimulai dalam 3 detik...\n";
    Sleep(3000);

    hasilVsComputer();   
}

void hasilVsComputer() {

    system("cls");

    int scoreSebelum = players[currentPlayer].score;

    playVsComputer();

    system("cls");
    cout << "Menghitung hasil pertandingan...\n";
    Sleep(3000);

    system("cls");
    Player &p = players[currentPlayer];

    int scorePertandingan = p.score - scoreSebelum;

    cout << "==================================================" << endl;
    cout << "                 HASIL PERTANDINGAN               " << endl;
    cout << "==================================================" << endl;
    cout << "| HASIL AKHIR : " << setw(34) << left 
         << hasilPertandinganVsComputer << "|" << endl;
    cout << "==================================================" << endl;

    cout << "| PLAYER                                         |" << endl;
    cout << "| Nama               : " << setw(25) << left << p.nama << "|" << endl;
    cout << "| Menang             : " << setw(25) << p.totalWins << "|" << endl;
    cout << "| Seri               : " << setw(25) << p.totalDraws << "|" << endl;
    cout << "| Kalah              : " << setw(25) << p.totalLosses << "|" << endl;
    cout << "| Point Pertandingan : " << setw(25) << scorePertandingan << "|" << endl;
    cout << "| Total Score Player : " << setw(25) << p.score << "|" << endl;

    cout << "|------------------------------------------------|" << endl;

    cout << "| KOMPUTER                                       |" << endl;
    cout << "| Menang             : " << setw(25) << komputer.wins << "|" << endl;
    cout << "| Seri               : " << setw(25) << komputer.draws << "|" << endl;
    cout << "| Kalah              : " << setw(25) << komputer.losses << "|" << endl;
    cout << "| Total Score Komputer: " << setw(24) << komputer.score << "|" << endl;

    cout << "==================================================" << endl;
	savePlayers();
		
    int pilih;
    cout << "\n1. Bermain lagi\n";
    cout << "2. Kembali ke menu utama\n";
    cout << "Pilih: ";
    cin >> pilih;

    if (pilih == 1) {
        hasilVsComputer();
    } else {
        system("cls");
    }
}

void menuLeaderboard() {
    system("cls");

    if (players.empty()) {
        cout << "==================================="<<endl;
        cout << "  LEADERBOARD BELUM MEMILIKI DATA  "<<endl;
        cout << "==================================="<<endl;
        cout << "\nSilakan input data player terlebih dahulu.\n";
        cout << "\nTekan ENTER untuk kembali ke menu utama...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        system("cls");
        return;
    }

    cout << "Menghitung total point permainan...\n";
    Sleep(3000);

    system("cls");
    showLeaderboard();

    cout << "\nTekan ENTER untuk kembali ke menu utama...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    system("cls");
}

void pilihPlayerVsPlayer() {
    // ===== PILIH PLAYER 1 =====
    system("cls");
    cout << "===== PILIH PLAYER 1 =====\n";

    for (int i = 0; i < players.size(); i++) {
        cout << i + 1 << ". " << players[i].nama << endl;
    }

    cout << "Pilih Player 1: ";
    cin >> indexPlayer1;
    indexPlayer1--;

    if (indexPlayer1 < 0 || indexPlayer1 >= players.size()) {
        cout << "Pilihan tidak valid!\n";
        Sleep(2000);
        return;
    }

    // ===== SUB MENU PLAYER 2 =====
    int pilihP2;
    system("cls");
    cout << "===== PLAYER 2 =====\n";
    cout << "1. Tambahkan Player Baru\n";
    cout << "2. Pilih Player yang Sudah Ada\n";
    cout << "Pilih: ";
    cin >> pilihP2;

    // PLAYER 2 BARU
    if (pilihP2 == 1) {
        Player p2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nama Player Baru: ";
        getline(cin, p2.nama);

        p2.totalGames = 0;
        p2.totalWins = 0;
        p2.totalDraws = 0;
        p2.totalLosses = 0;
        p2.score = 0;

        players.push_back(p2);
        indexPlayer2 = players.size() - 1;
        savePlayers();
    }
    // PLAYER 2 LAMA
    else if (pilihP2 == 2) {
        system("cls");
        cout << "===== PILIH PLAYER 2 =====\n";

        for (int i = 0; i < players.size(); i++) {
            if (i != indexPlayer1)
                cout << i + 1 << ". " << players[i].nama << endl;
        }

        cout << "Pilih Player 2: ";
        cin >> indexPlayer2;
        indexPlayer2--;

        if (indexPlayer2 < 0 || indexPlayer2 >= players.size() ||
            indexPlayer2 == indexPlayer1) {
            cout << "Pilihan tidak valid!\n";
            Sleep(2000);
            return;
        }
    } else {
        cout << "Pilihan tidak valid!\n";
        Sleep(2000);
        return;
    }

    hasilVsPlayer();
}



void playerMenu() {
    int menu;
    do {
        cout << "+=========================+"<<endl;
        cout << "|    MENU TIC TAC GAME    |"<<endl;
        cout << "+=========================+"<<endl;
        cout << "1. Player Baru\n";		 
        cout << "2. Pilih Player\n";
        cout << "3. Leaderboard\n";
        cout << "4. Reset Data\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> menu;

        if (menu == 1){
        	Player p;
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
        	
        	cout << "Nama Player: ";
        	getline(cin, p.nama);
        	
        	p.totalGames = 0;
        	p.totalWins = 0;
        	p.totalDraws = 0;
        	p.totalLosses = 0;
        	p.score = 0;
        	
        	players.push_back(p);
        	currentPlayer = players.size() - 1;
        	savePlayers();
        	
        	cout << "\nData player berhasil dibuat.";
			cout << "\nMohon tunggu, sistem sedang menyiapkan permainan...\n";
			Sleep(3000);

        	system("cls");
        	
        	pilihModePermainan();
		}
       	else if (menu == 2) {
    system("cls");

    if (players.size() < 1) {
        cout << "Minimal harus ada 1 player.\n";
        Sleep(2000);
        continue;
    }

    cout << "===== PILIH PLAYER =====\n";
    for (int i = 0; i < players.size(); i++) {
        cout << i + 1 << ". " << players[i].nama << endl;
    }

    cout << "Pilih Player: ";
    cin >> currentPlayer;
    currentPlayer--;

    if (currentPlayer < 0 || currentPlayer >= players.size()) {
        cout << "Pilihan tidak valid!\n";
        Sleep(2000);
        continue;
    }

    system("cls");
    pilihModePermainan();
}


        else if (menu == 3){
        	menuLeaderboard();
		}
		
       else if (menu == 4) {
    		char konfirmasi;
    		
			system("cls");

    	cout << "================================="<<endl;
    	cout << "   KONFIRMASI RESET DATA PLAYER  "<<endl;
    	cout << "================================="<<endl;
    	cout << "Apakah Anda yakin ingin mereset semua data? (y/n): ";
    	cin >> konfirmasi;

    	if (konfirmasi == 'y' || konfirmasi == 'Y') {
        players.clear();
        savePlayers();
        cout << "\nData berhasil di-reset.\n";
    	
		} else {
        cout << "\nReset data dibatalkan.\n";
    }

    	Sleep(2000);
    	system("cls");
}

    } while (menu != 5);
}

int main() {
    srand(time(0));
    loadPlayers();
    tampilanAwal();   
    menuUtama();
	cout << "\nTerima kasih telah bermain!\n";
    return 0;      
    return 0;

}
