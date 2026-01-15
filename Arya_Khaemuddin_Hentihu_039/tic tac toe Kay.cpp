// ARYA KHAEMUDDIN HENTIHU
// 2500018039

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

// --- STRUKTUR DATA ---
struct Player {
    string nama;
    int totalGames = 0;
    int totalWins = 0;
    int totalDraws = 0;
    int totalLosses = 0;
    int score = 0;
};

// --- VARIABEL GLOBAL ---
vector<Player> players;
const string FILE_NAME = "players.txt";
int currentPlayerIndex = -1;

// --- DENGAN ENTER ---
void warningEnter(){ 
    cout << "=========================\n";
    cout << "        WARNING \n";
    cout << "  Pilihan Tidak Valid\n";
    cout << "=========================\n\n";
    
    cout << "Tekan Enter untuk kembali...";
    cin.ignore(); cin.get();
}

// --- WARNING BIASA ---
void warningBiasa(){
	cout << "=========================\n";
    cout << "        WARNING \n";
    cout << "  Pilihan Tidak Valid\n";
    cout << "=========================\n\n";
}

// --- UNTUK PILIH PLAYER KEDUA ---
int pilihPlayerKedua() {
    system("cls");
    cout << "=== PILIH LAWAN (PLAYER 2) ===" << endl;
    cout << left << setw(3) << "No" << "| " 
         << setw(15) << "Nama" << "| " 
         << setw(6) << "Score" << "| " 
         << setw(6) << "Games" << "| " 
         << setw(3) << "W" << "| " 
         << setw(3) << "D" << "| " << "L" << endl;
    cout << "---|----------------|-------|-------|----|----|---" << endl;

    for (int i = 0; i < (int)players.size(); i++) {
        if (i == currentPlayerIndex) {
			string open = "\33[9m";
			string close = "\33[0m";
            cout << open << left << setw(3) << "-" << "| " 
                 << setw(15) << players[i].nama << "| " 
                 << right << setw(5) << players[i].score << " | " 
                 << setw(5) << players[i].totalGames << " | " 
                 << setw(2) << players[i].totalWins << " | " 
                 << setw(2) << players[i].totalDraws << " | " 
                 << setw(2) << players[i].totalLosses << close << " (SEDANG LOGIN)" << endl;
        } else {
            cout << left << setw(3) << i + 1 << "| " 
                 << setw(15) << players[i].nama << "| " 
                 << right << setw(5) << players[i].score << " | " 
                 << setw(5) << players[i].totalGames << " | " 
                 << setw(2) << players[i].totalWins << " | " 
                 << setw(2) << players[i].totalDraws << " | " 
                 << setw(2) << players[i].totalLosses << endl;
        }
    }

    int p;
    cout << "\nPilih lawan (nomor) atau 0 untuk kembali: ";
    cin >> p;

    if (p == 0) return -1;
    if (p > 0 && p <= (int)players.size()) {
        if (p - 1 == currentPlayerIndex) {
            cout << "\n==============================\n";
            cout << "         ! WARNING ! \n";
            cout << " Player Tersebut Sedang Login\n";
            cout << "==============================\n\n";
            
            cout << "Tekan Enter Untuk Kembali...";
            cin.ignore();
            cin.get();
            return pilihPlayerKedua();
        }
        return p - 1;
    } else {
    	cout << endl;
        warningEnter();
        return pilihPlayerKedua();
    }
}

// --- MENU 4 ---
void hapusAllPlayer(){
	ofstream deleteFile(FILE_NAME, ios::trunc);
	system("cls");
	cout << "==========================\n";
	cout << "    Berhasil dihapus\n";
	cout << " Dimohon Untuk Relog Dulu\n";
	cout << "==========================\n\n";		
	
	cout << "Tekan Enter Untuk Keluar Dari Program...";
	cin.ignore();
	cin.get();
	deleteFile.close();
}

void loadPlayers() {
    ifstream inputFile(FILE_NAME.c_str());
    if (!inputFile.is_open()) {
        return;
    }
    players.clear();
    Player temp;
    while (inputFile >> temp.nama >> temp.totalGames >> temp.totalWins 
                     >> temp.totalDraws >> temp.totalLosses >> temp.score) {
        players.push_back(temp);
    }
    inputFile.close();
}

void savePlayer() {
    ofstream outputFile(FILE_NAME.c_str());
    for (int i = 0; i < (int)players.size(); i++) {
        outputFile << players[i].nama << " " << players[i].totalGames << " "
                   << players[i].totalWins << " " << players[i].totalDraws << " "
                   << players[i].totalLosses << " " << players[i].score << endl;
    }
    outputFile.close();
}

// --- FUNGSI UNTUK UPDATE STATISTIK ---
void updateAndShowResult(int result, int p2Idx = -1) {
    if (currentPlayerIndex == -1) return;

    Player& p1 = players[currentPlayerIndex];
    p1.totalGames++;
	
	int poin = 0;
	string teksHasil;
	
    if (p2Idx != -1) { // --- MODE PVP ---
        Player& p2 = players[p2Idx];
        p2.totalGames++;

        if (result == 1) { // --- P1 MENANG ---
        	teksHasil = "MENANG";
        	poin = 3;
            p1.totalWins++; 
			p1.score += 3;
            p2.totalLosses++;
            cout << "\nPEMENANG: " << p1.nama << "!\n";
            
            cout << "\n================================\n";
		    cout << "       HASIL PERTANDINGAN\n";
		    cout << "================================\n";
		    cout << "Hasil:  " << teksHasil << endl;
		    cout << "Score yang didapat: +" << poin << " poin" << endl << endl;
		
		    cout << "Statistik " << p1.nama << ":" << endl;
		    cout << "- Total Games: " << p1.totalGames << endl;
		    cout << "- Wins       : " << p1.totalWins << endl;
		    cout << "- Draws      : " << p1.totalDraws << endl;
		    cout << "- Losses     : " << p1.totalLosses << endl;
		    cout << "- Total Score: " << p1.score << endl << endl;
		    
		    cout << "Data telah disimpan ke file " << FILE_NAME << endl;
        } else if (result == 3) { // --- P2 MENANG ---
        	teksHasil = "MENANG";
        	poin = 3;
            p2.totalWins++; 
			p2.score += 3;
            p1.totalLosses++;
            cout << "\nPEMENANG: " << p2.nama << "!\n";
            
            cout << "\n================================\n";
		    cout << "       HASIL PERTANDINGAN\n";
		    cout << "================================\n";
		    cout << "Hasil:  " << teksHasil << endl;
		    cout << "Score yang didapat: +" << poin << " poin" << endl << endl;
		
		    cout << "Statistik " << p2.nama << ":" << endl;
		    cout << "- Total Games: " << p2.totalGames << endl;
		    cout << "- Wins       : " << p2.totalWins << endl;
		    cout << "- Draws      : " << p2.totalDraws << endl;
		    cout << "- Losses     : " << p2.totalLosses << endl;
		    cout << "- Total Score: " << p2.score << endl << endl;
		    
		    cout << "Data telah disimpan ke file " << FILE_NAME << endl;
        } else { // --- BILA SERI --- 
            p1.totalDraws++; p1.score += 1;
            p2.totalDraws++; p2.score += 1;
            cout << "\nHasil: SERI!\n";
        }
    } else { // --- MODE VS COMPUTER --- 
        if (result == 1) { 
        	teksHasil = "MENANG";
        	poin = 3;
			p1.totalWins++; 
			p1.score += 3; 
			cout << "\nHasil: MENANG!\n"; 
		} else if (result == 2) { 
			teksHasil = "SERI";
			poin = 1;
			p1.totalDraws++; 
			p1.score += 1; 
			cout << "\nHasil: SERI!\n"; 
		} else { 
			teksHasil = "KALAH";
			poin = 0;
			p1.totalLosses++; 
			cout << "\nHasil: KALAH!\n"; 
		}
		
		cout << "\n================================\n";
	    cout << "       HASIL PERTANDINGAN\n";
	    cout << "================================\n";
	    cout << "Hasil:  " << teksHasil << endl;
	    cout << "Score yang didapat: +" << poin << " poin" << endl << endl;
	
	    cout << "Statistik " << p1.nama << ":" << endl;
	    cout << "- Total Games: " << p1.totalGames << endl;
	    cout << "- Wins       : " << p1.totalWins << endl;
	    cout << "- Draws      : " << p1.totalDraws << endl;
	    cout << "- Losses     : " << p1.totalLosses << endl;
	    cout << "- Total Score: " << p1.score << endl << endl;
	    
	    cout << "Data telah disimpan ke file " << FILE_NAME << endl;
    }
    savePlayer();
    
}

// --- LOGIKA GAME ---
void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j];
            if (j < 2) cout << " |";
        }
        cout << "\n";
        if (i < 2) cout << " ---|---|---\n";
    }
    cout << "\n";
}

void displayGuide() {
    cout << "\n Panduan Posisi:\n";
	cout << "  1 | 2 | 3\n";
	cout << " ---|---|---\n";
	cout << "  4 | 5 | 6\n";
	cout << " ---|---|---\n";
	cout << "  7 | 8 | 9\n\n";
}

// --- UNTUK LOADING MASUK GAME
void memuatMasuk() {
    system("cls");

    string title[] = {
        "+============================+ ",
        "|   SEDANG MENYIAPKAN GAME   | ",
        "+============================+\n",
        "SABAR YAK WKWKWK\n\n",
        "Game By Kay"
    };

    CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth  = csbi.dwSize.X;
	int consoleHeight = csbi.dwSize.Y;


    int lines = sizeof(title) / sizeof(title[0]);
    int barWidth = 50;
    int totalHeight = lines + 2 + 1; 

    int paddingTop = (consoleHeight - totalHeight) / 2;
    for(int i = 0; i < paddingTop; i++) cout << "\n";

    for(int i = 0; i < lines; i++) {
        int paddingLeft = (consoleWidth - title[i].length()) / 2;
        if(paddingLeft > 0) cout << string(paddingLeft, ' ');
        cout << title[i] << endl;
    }

    cout << "\n"; 


    int barPaddingLeft = (consoleWidth - barWidth - 6) / 2;
    for(int i = 0; i <= barWidth; i++) {
        cout << string(barPaddingLeft, ' ') << "[";
        for(int j = 0; j < barWidth; j++) {
            if(j < i) cout << "*";
            else cout << " ";
        }
        cout << "] " << (i * 100 / barWidth) << "%\r";
        cout.flush();
        Sleep(30);
    }

    cout << "\n\n";
}

// --- MEMUAT UNTUK MENGHAPUS --- 
void memuatHapus() {
    system("cls");

    string title[] = {
        "+======================+ ",
        "|   SEDANG MENGHAPUS   | ",
        "+======================+\n",
        "SABAR YAK WKWKWK\n\n",
        "Game By Kay"
    };

    CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int consoleWidth  = csbi.dwSize.X;
	int consoleHeight = csbi.dwSize.Y;


    int lines = sizeof(title) / sizeof(title[0]);
    int barWidth = 50;
    int totalHeight = lines + 2 + 1; 

    int paddingTop = (consoleHeight - totalHeight) / 2;
    for(int i = 0; i < paddingTop; i++) cout << "\n";

    for(int i = 0; i < lines; i++) {
        int paddingLeft = (consoleWidth - title[i].length()) / 2;
        if(paddingLeft > 0) cout << string(paddingLeft, ' ');
        cout << title[i] << endl;
    }

    cout << "\n"; 


    int barPaddingLeft = (consoleWidth - barWidth - 6) / 2;
    for(int i = 0; i <= barWidth; i++) {
        cout << string(barPaddingLeft, ' ') << "[";
        for(int j = 0; j < barWidth; j++) {
            if(j < i) cout << "*";
            else cout << " ";
        }
        cout << "] " << (i * 100 / barWidth) << "%\r";
        cout.flush();
        Sleep(30);
    }

    cout << "\n\n";
}

bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ') return false;
    return true;
}

bool isValidMove(char board[3][3], int position) {
    if (position < 1 || position > 9) return false;
    return board[(position - 1) / 3][(position - 1) % 3] == ' ';
}

void makeMove(char board[3][3], int position, char player) {
    board[(position - 1) / 3][(position - 1) % 3] = player;
}

int computerMove(char board[3][3]) {
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            board[(i - 1) / 3][(i - 1) % 3] = 'O';
            if (checkWin(board, 'O')) { board[(i - 1) / 3][(i - 1) % 3] = ' '; return i; }
            board[(i - 1) / 3][(i - 1) % 3] = ' ';
        }
    }
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            board[(i - 1) / 3][(i - 1) % 3] = 'X';
            if (checkWin(board, 'X')) { board[(i - 1) / 3][(i - 1) % 3] = ' '; return i; }
            board[(i - 1) / 3][(i - 1) % 3] = ' ';
        }
    }
    if (isValidMove(board, 5)) return 5;
    int corners[] = {1, 3, 7, 9};
    for (int c : corners) if (isValidMove(board, c)) return c;
    for (int i = 1; i <= 9; i++) if (isValidMove(board, i)) return i;
    return -1;
}

// --- MODE VS PLAYER --- 
int playVsPlayer(int p2Idx) {
    char board[3][3] = {{' ',' ',' '},
						{' ',' ',' '},
						{' ',' ',' '}};
	
	memuatMasuk();
						
    system("cls");
    cout << "=== MODE VS PLAYER ===\n";
    cout << endl;
    cout << "Player 1 : " << players[currentPlayerIndex].nama << " (X) \n";
	cout << "--------- VS --------\n";
	cout << "Player 2 : " << players[p2Idx].nama << " (O)\n";
    displayGuide();
	
    char currentPlayer = 'X';
    int pos;
    displayBoard(board);
    
    while (true) {
        string name = (currentPlayer == 'X') ? players[currentPlayerIndex].nama : players[p2Idx].nama;
        cout << "Giliran " << name << " (" << currentPlayer << ")\nPosisi (1-9): ";
        cin >> pos;
        
        if (!isValidMove(board, pos)) { 
        	cout << endl;
			cout << "===================\n"; 
			cout << "    ! WARNING !\n";
			cout << " INPUT TIDAK VALID \n";
			cout << "===================\n\n"; 
			cout << " Tolong Mengulang...\n";
			continue; 
		}
		
        makeMove(board, pos, currentPlayer);
        displayBoard(board);
        if (checkWin(board, currentPlayer)) return (currentPlayer == 'X') ? 1 : 3;
        if (isBoardFull(board)) return 2;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

// --- MODE VS KOMPUTER --- 
int playVsComputer() {
	
	memuatMasuk();
	
	system("cls");
    char board[3][3] = {
	{' ',' ',' '},
	{' ',' ',' '},
	{' ',' ',' '}};
	
	cout << "================================\n";
	cout << "      TIC TAC TOE GAME\n";
	cout << "================================\n\n";
	
	displayGuide();
	displayBoard(board);
	
	
    int pos;
    while (true) {
        cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (!isValidMove(board, pos)){
        	cout << endl;
			cout << "===================\n"; 
			cout << "    ! WARNING !\n";
			cout << " INPUT TIDAK VALID \n";
			cout << "===================\n\n"; 
			cout << " Tolong Mengulang...\n\n";
        	continue;	
		} 
        makeMove(board, pos, 'X');
        displayBoard(board);
        if (checkWin(board, 'X')) return 1;
        if (isBoardFull(board)) return 2;
		// --- GILIRAN KOMPUTER --- 
		cout << "Komputer sedang berpikir";
		flush(cout);
		
		for (int i = 0; i < 3; i++){
			this_thread::sleep_for(
			chrono::seconds(1));
			cout << (i == 2 ? ".\n" : ".");
			flush(cout);
		}
        int cMove = computerMove(board);
        cout << "Komputer memilih posisi: " << cMove << "\n";
        if (cMove != -1) makeMove(board, cMove, 'O');
		displayBoard(board);
        
        if (checkWin(board, 'O')) return 3;
        if (isBoardFull(board)) return 2;
    }
}

void startGameLoop() {
	bool cekPil = true;
    char playAgain;
    int choice;
    
    do {
        system("cls");
        cout << "Pilih mode permainan:\n";
		cout << "0. Kembali\n";
		cout << "1. VS Player\n";
		cout << "2. VS Komputer\n";
		cout << "Pilihan: ";
        cin >> choice;
        
        if (choice == 0) {
        	break;
		}
		
        if (choice == 1) {
            if (players.size() < 2) {
            	cout << endl;
				cout << "==================================\n";
				cout << "           ! WARNING !\n";
				cout << " BUTUH MINIMAL 2 PLAYER TERDAFTAR\n";
				cout << "==================================\n\n";
                
                cout << "Tekan Enter untuk kembali...";
                cin.ignore();
                cin.get();
				continue;
            }
            int p2Idx = pilihPlayerKedua();
            if (p2Idx != -1) {
                int result = playVsPlayer(p2Idx);
                updateAndShowResult(result, p2Idx);
                
	            while(cekPil){
		        	cout << "\nMain lagi? (y/n): ";
					cin >> playAgain;
					
					if (playAgain != 'n' && playAgain != 'y'){
						cout << endl;
						warningBiasa();
						cekPil = true;
					} else if (playAgain == 'y' || playAgain == 'Y'){
						cekPil = false;
					} else if (playAgain == 'n' || playAgain == 'N'){
						cekPil = false;
					}
				}
            }
        } else if (choice == 2) {
            int result = playVsComputer();
            updateAndShowResult(result);
           
	            while(cekPil){
		        	cout << "\nMain lagi? (y/n): ";
					cin >> playAgain;
					
					if (playAgain != 'n' && playAgain != 'y'){
						cout << endl;
						warningBiasa();
						cekPil = true;
					} else if (playAgain == 'y' || playAgain == 'Y'){
						cekPil = false;
					} else if (playAgain == 'n' || playAgain == 'N'){
						cekPil = false;
					}
				}
        } else {
        	cout << endl;
        	warningEnter();
        	playAgain = 'y';
		}		
    } while (playAgain == 'y' || playAgain == 'Y');
}

void terimaKasih(){
    cout << "=========================\n";
    cout << "        TERIMA KASIH \n";
    cout << "      TELAH BERMAIN <3\n";
    cout << "=========================\n\n";
}

// ---- UNTUK MENU 2 ----
bool pilihPlayer() {
    if (players.empty()) {
    	cout << "==============================\n";
    	cout << "            UPSSS....\n";
        cout << "  Belum ada player terdaftar.\n";
    	cout << "==============================\n\n";
        cout << "Tekan Enter untuk kembali...";
        cin.ignore(); cin.get();
        cout << endl;
        return false;
    }
    
	system("cls");
	
    cout << "=== DAFTAR PLAYER ===" << endl;
    cout << left << setw(3) << "No" << "| " 
         << setw(15) << "Nama" << "| " 
         << setw(6) << "Score" << "| " 
         << setw(6) << "Games" << "| " 
         << setw(3) << "W" << "| " 
         << setw(3) << "D" << "| " << "L" << endl;
    cout << "---|----------------|-------|-------|----|----|---" << endl;

    for (int i = 0; i < (int)players.size(); i++) {
        cout << left << setw(3) << i + 1 << "| " 
             << setw(15) << players[i].nama << "| " 
             << right << setw(5) << players[i].score << " | " 
             << setw(5) << players[i].totalGames << " | " 
             << setw(2) << players[i].totalWins << " | " 
             << setw(2) << players[i].totalDraws << " | " 
             << setw(2) << players[i].totalLosses << endl;
    }

    int p;
    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    cin >> p;

    if (p > 0 && p <= (int)players.size()) {
        currentPlayerIndex = p - 1;
        Player selected = players[currentPlayerIndex];
        
        cout << "\nPlayer dipilih:  " << selected.nama << endl;
        cout << "\nSelamat datang kembali, " << selected.nama << "! " << endl << endl;
        cout << "Statistik Anda:" << endl;
        cout << "- Total Games : " << selected.totalGames << endl;
        cout << "- Wins        : " << selected.totalWins << endl;
        cout << "- Draws       : " << selected.totalDraws << endl;
        cout << "- Losses      : " << selected.totalLosses << endl;
        cout << "- Total Score : " << selected.score << endl << endl;
        
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore(); cin.get();
        return true;
    }else if(p == 0){
    	return false;
	}else{
		cout << endl;
    	warningEnter();
    	return pilihPlayer();
	}
}

// ---- UNTUK MENU 3 ----
void showLeaderboard() {
	cout << endl;
    if (players.empty()) {
    	cout << "========================\n";
    	cout << "         UPSSS....\n";
        cout << " Belum ada data pemain.\n";
    	cout << "========================\n\n";
    } else {
        vector<Player> sorted = players;
        sort(sorted.begin(), sorted.end(), [](const Player& a, const Player& b) {
            return a.score > b.score;
        });

        cout << "===============================" << endl;
		cout << "          LEADERBOARD"<< endl;
		cout << "    Top 10 Players by Score"<< endl;
		cout << "==============================="<< endl << endl;
         
	    cout << left << setw(3) << "Rank" << "| " 
	         << setw(15) << "Nama" << " |" 
	         << setw(6) << "Score" << " |" 
	         << setw(6) << "Games" << " | " 
	         << setw(3) << "W" << "| " 
	         << setw(3) << "D" << "| " << "L" << endl;
	    cout << "----|-----------------|-------|-------|----|----|---" << endl;

    for (int i = 0; i < (int)sorted.size(); i++) {
        cout << left << setw(3) << i + 1 << " | " 
             << setw(15) << sorted[i].nama << " | " 
             << right << setw(5) << sorted[i].score << " | " 
             << setw(5) << sorted[i].totalGames << " | " 
             << setw(2) << sorted[i].totalWins << " | " 
             << setw(2) << sorted[i].totalDraws << " | " 
             << setw(2) << sorted[i].totalLosses << endl;
    }
    
    cout << "\n===============================" << endl;
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore(); cin.get();
}

void menu() {
    int pilihan;
    loadPlayers();
    while (true) {
        system("cls");
        cout << "================================\n";
        cout << "      TIC TAC TOE GAME\n";
        cout << "================================\n\n";
        cout << "1. Player Baru\n";
		cout << "2. Pilih Player yang Sudah Ada\n";
		cout << "3. Lihat Leaderboard\n";
		cout << "4. Hapus All Player\n";
		cout << "5. Keluar\n";
		cout << "--------------------------------\n";
		cout << "Pilihan: ";
        cin >> pilihan;
        if (pilihan == 1) {
            Player pBaru;
            cout << endl;
            
            cout << "=== REGISTRASI PLAYER BARU ===\n";
			cout << "Masukkan nama Anda: ";
            cin >> pBaru.nama;
            players.push_back(pBaru);
            currentPlayerIndex = players.size() - 1;
            savePlayer();
            cout << "\nPlayer baru berhasil dibuat!\n";
			cout << "Selamat datang, " << pBaru.nama << "!\n";
			cout << "\nStatistik Anda:\n";
			cout << "- Total Games : 0\n";
			cout << "- Wins        : 0\n";
			cout << "- Draws       : 0\n";
			cout << "- Losses      : 0\n";
			cout << "- Total Score : 0\n";
			cout << "\nTekan Enter untuk melanjutkan...";
            cin.ignore(); cin.get();
            startGameLoop();
        } else if (pilihan == 2) {
            if (pilihPlayer()) startGameLoop();
        } else if (pilihan == 3) {
        	showLeaderboard();
		} else if (pilihan == 4) {
			char pil;
			
			cout << endl;
			cout << "================================\n";
			cout << "          ! WARNING !\n";
			cout << " SEMUA DATA PLAYER AKAN DIHAPUS\n";
			cout << "================================\n\n";
			
			cout << "Apakah ingin Menghapus ?\n";
			cout << "(y) = Ya Hapus Aja, Buat Penuh Aja\n";
			cout << "(n) = JANGANN!!, Kembali ke menu\n\n";
			
			cout << "Pilihan Anda : ";
			cin >> pil;
			
			if (pil == 'y' || pil == 'Y'){
				memuatHapus();
				hapusAllPlayer();
				break;
			}else if(pil == 'n' || pil == 'N'){
				return menu();
				break;
			}else{
				cout << endl;
				warningEnter();
			}
		} else if (pilihan == 5) {
			cout << endl;
    		terimaKasih();
			break;
		} else {
			cout << endl;
			warningEnter();
		}
    }
}

int main() {
    srand(time(0));
    menu();
    return 0;
}
