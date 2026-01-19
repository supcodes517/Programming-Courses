#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>

using namespace std;

struct Player {
    string name;
    int totalGames;
    int wins;
    int draws;
    int losses;
    int totalScore;
};

vector<Player> players;
Player* currentPlayer = NULL;
Player* player1 = NULL;
Player* player2 = NULL;
const string FILENAME = "players.txt";
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void setColor(int color) {
    SetConsoleTextAttribute(hConsole, color);
}

void clearScreen() {
    system("cls");
}

void showLoading() {
    setColor(11); 
    cout << "\n\t\tLoading ";
    for(int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(300);
    }
    cout << "\n";
    setColor(7); 
}

void showHeader() {
    setColor(14); 
    cout << "\n";
    cout << "\t================================================\n";
    cout << "\t|                                              |\n";
    cout << "\t|             TIC TAC TOE GAME                 |\n";
    cout << "\t|                                              |\n";
    cout << "\t================================================\n\n";
    setColor(7); 
}

void showMenu() {
    setColor(10); 
    cout << "\t================================================\n";
    cout << "\t|               MENU UTAMA                     |\n";
    cout << "\t================================================\n";
    
    if (currentPlayer) {
        setColor(11); 
        cout << "\t|  Player aktif: " << left << setw(32) << currentPlayer->name << "|\n";
        setColor(10); 
        cout << "\t------------------------------------------------\n";
    }
    
    setColor(10); 
    cout << "\t|  1.  [+] Player Baru                         |\n";
    cout << "\t|  2.  [=] Pilih Player Lama                   |\n";
    cout << "\t|  3.  [#] Lihat Leaderboard                   |\n";
    cout << "\t|  4.  [>] Main Game                           |\n";
    cout << "\t|  5.  [X] Keluar                              |\n";
    cout << "\t================================================\n\n";
    setColor(7);
}

void pressEnterToContinue() {
    setColor(8); 
    cout << "\n\t--> Tekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
    setColor(7); 
}

void loadPlayers() {
    ifstream file(FILENAME.c_str());
    players.clear();
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            Player p;
            getline(ss, p.name, ',');
            ss >> p.totalGames >> p.wins >> p.draws >> p.losses >> p.totalScore;
            players.push_back(p);
        }
        file.close();
    }
}

void savePlayers() {
    ofstream file(FILENAME.c_str());
    for (size_t i = 0; i < players.size(); i++) {
        file << players[i].name << "," 
             << players[i].totalGames << " " 
             << players[i].wins << " " 
             << players[i].draws << " " 
             << players[i].losses << " " 
             << players[i].totalScore << endl;
    }
    file.close();
}

int findPlayerByName(const string& name) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].name == name) {
            return i;
        }
    }
    return -1;
}

void createNewPlayer() {
    clearScreen();
    showHeader();
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|           REGISTRASI PLAYER BARU             |\n";
    cout << "\t================================================\n\n";
    
    setColor(14); 
    cout << "\t[*] Masukkan nama Anda: ";
    setColor(10); 
    string name;
    getline(cin, name);
    
    if (findPlayerByName(name) != -1) {
        setColor(12); 
        cout << "\n\t[!] Nama sudah digunakan. Silakan pilih nama lain.\n";
        pressEnterToContinue();
        return;
    }
    
    Player newPlayer;
    newPlayer.name = name;
    newPlayer.totalGames = 0;
    newPlayer.wins = 0;
    newPlayer.draws = 0;
    newPlayer.losses = 0;
    newPlayer.totalScore = 0;
    
    players.push_back(newPlayer);
    currentPlayer = &players[players.size() - 1];
    savePlayers();
    
    setColor(10); 
    cout << "\n\t[+] Player baru berhasil dibuat!\n";
    setColor(14); 
    cout << "\t[*] Selamat datang, " << name << "!\n\n";
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|                STATISTIK ANDA                |\n";
    cout << "\t================================================\n\n";
    
    setColor(7); 
    cout << "\t   Total Games: " << currentPlayer->totalGames << endl;
    cout << "\t   Wins       : " << currentPlayer->wins << endl;
    cout << "\t   Draws      : " << currentPlayer->draws << endl;
    cout << "\t   Losses     : " << currentPlayer->losses << endl;
    cout << "\t   Total Score: " << currentPlayer->totalScore << endl;
    
    pressEnterToContinue();
}

Player* selectPlayerFromList(const string& prompt) {
    clearScreen();
    showHeader();
    
    if (players.empty()) {
        setColor(12); 
        cout << "\n\t[!] Belum ada player yang terdaftar.\n";
        cout << "\t    Silakan buat player baru terlebih dahulu.\n";
        pressEnterToContinue();
        return NULL;
    }
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|            DAFTAR PLAYER TERDAFTAR           |\n";
    cout << "\t================================================\n\n";
    
    setColor(14); 
    cout << "\t" << left << setw(5) << "No" << setw(15) << "Nama" << setw(10) << "Score" 
         << setw(8) << "Games" << setw(5) << "W" << setw(5) << "D" << setw(5) << "L" << endl;
    
    setColor(8); 
    cout << "\t" << string(53, '-') << endl;
    
    for (size_t i = 0; i < players.size(); i++) {
        setColor(7); 
        cout << "\t" << left << setw(5) << i+1 << setw(15) << players[i].name 
             << setw(10) << players[i].totalScore << setw(8) << players[i].totalGames
             << setw(5) << players[i].wins << setw(5) << players[i].draws 
             << setw(5) << players[i].losses << endl;
    }
    
    setColor(14); 
    cout << "\n\t" << prompt << " (1-" << players.size() << ") atau 0 untuk membatalkan: ";
    
    int choice;
    cin >> choice;
    
    if (choice == 0) {
        cin.ignore();
        return NULL;
    }
    
    if (choice >= 1 && choice <= (int)players.size()) {
        Player* selected = &players[choice-1];
        setColor(10); 
        cout << "\n\t[+] Player dipilih: " << selected->name << "\n";
        cin.ignore();
        pressEnterToContinue();
        return selected;
    } else {
        setColor(12); 
        cout << "\n\t[!] Pilihan tidak valid!\n";
        cin.ignore();
        pressEnterToContinue();
        return NULL;
    }
}

void selectExistingPlayer() {
    Player* selected = selectPlayerFromList("--> Pilih player");
    if (selected) {
        currentPlayer = selected;
        
        clearScreen();
        showHeader();
        setColor(10); 
        cout << "\n\t[+] Player dipilih: " << currentPlayer->name << "\n\n";
        cout << "\t[*] Selamat datang kembali, " << currentPlayer->name << "!\n\n";
        
        setColor(11); 
        cout << "\t================================================\n";
        cout << "\t|                STATISTIK ANDA                |\n";
        cout << "\t================================================\n\n";
        
        setColor(7); 
        cout << "\t   Total Games: " << currentPlayer->totalGames << endl;
        cout << "\t   Wins       : " << currentPlayer->wins << endl;
        cout << "\t   Draws      : " << currentPlayer->draws << endl;
        cout << "\t   Losses     : " << currentPlayer->losses << endl;
        cout << "\t   Total Score: " << currentPlayer->totalScore << endl;
        
        pressEnterToContinue();
    }
}

void showLeaderboard() {
    clearScreen();
    showHeader();
    
    if (players.empty()) {
        setColor(12); 
        cout << "\n\t[!] Belum ada data player.\n";
        pressEnterToContinue();
        return;
    }
    
    vector<Player> sortedPlayers = players;
    for (size_t i = 0; i < sortedPlayers.size() - 1; i++) {
        for (size_t j = i + 1; j < sortedPlayers.size(); j++) {
            if (sortedPlayers[i].totalScore < sortedPlayers[j].totalScore) {
                Player temp = sortedPlayers[i];
                sortedPlayers[i] = sortedPlayers[j];
                sortedPlayers[j] = temp;
            }
        }
    }
    
    setColor(14); 
    cout << "\t================================================\n";
    cout << "\t|                 LEADERBOARD                  |\n";
    cout << "\t|            TOP 10 PLAYERS BY SCORE           |\n";
    cout << "\t================================================\n\n";
    
    if (sortedPlayers.size() > 0) {
        setColor(6);
        cout << "\t      TOP PLAYER: " << sortedPlayers[0].name << " - " 
             << sortedPlayers[0].totalScore << " poin\n\n";
    }
    
    setColor(11); 
    cout << "\t" << left << setw(7) << "Rank" << setw(15) << "Nama" << setw(10) << "Score" 
         << setw(8) << "Games" << setw(5) << "W" << setw(5) << "D" << setw(5) << "L" << endl;
    
    setColor(8); 
    cout << "\t" << string(55, '=') << endl;
    
    int limit = min(10, (int)sortedPlayers.size());
    for (int i = 0; i < limit; i++) {
        if (i == 0) setColor(14); 
        else if (i == 1) setColor(7); 
        else if (i == 2) setColor(6); 
        else setColor(7); 
        
        cout << "\t" << left << setw(7) << i+1 << setw(15) << sortedPlayers[i].name 
             << setw(10) << sortedPlayers[i].totalScore << setw(8) << sortedPlayers[i].totalGames
             << setw(5) << sortedPlayers[i].wins << setw(5) << sortedPlayers[i].draws 
             << setw(5) << sortedPlayers[i].losses << endl;
    }
    
    setColor(14); 
    cout << "\n\t================================================\n";
    cout << "\t|               END OF LEADERBOARD               |\n";
    cout << "\t==================================================\n";
    
    pressEnterToContinue();
}

void displayBoard(const vector<char>& board, bool showGuide = false) {
    if (showGuide) {
        setColor(11); 
        cout << "\n\t      Panduan Posisi:\n";
        setColor(7); 
        cout << "\t        1 | 2 | 3 \n";
        cout << "\t       ---+---+---\n";
        cout << "\t        4 | 5 | 6 \n";
        cout << "\t       ---+---+---\n";
        cout << "\t        7 | 8 | 9 \n";
    }
    
    setColor(14); 
    cout << "\n\t      Papan Permainan:\n";
    setColor(7); 
    cout << "\t        " << (board[0] == ' ' ? " " : string(1, board[0])) 
         << " | " << (board[1] == ' ' ? " " : string(1, board[1])) 
         << " | " << (board[2] == ' ' ? " " : string(1, board[2])) << " \n";
    cout << "\t       ---+---+---\n";
    cout << "\t        " << (board[3] == ' ' ? " " : string(1, board[3])) 
         << " | " << (board[4] == ' ' ? " " : string(1, board[4])) 
         << " | " << (board[5] == ' ' ? " " : string(1, board[5])) << " \n";
    cout << "\t       ---+---+---\n";
    cout << "\t        " << (board[6] == ' ' ? " " : string(1, board[6])) 
         << " | " << (board[7] == ' ' ? " " : string(1, board[7])) 
         << " | " << (board[8] == ' ' ? " " : string(1, board[8])) << " \n\n";
}

char checkWinner(const vector<char>& board) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i+1] && board[i] == board[i+2]) {
            return board[i];
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (board[i] != ' ' && board[i] == board[i+3] && board[i] == board[i+6]) {
            return board[i];
        }
    }
    
    if (board[0] != ' ' && board[0] == board[4] && board[0] == board[8]) {
        return board[0];
    }
    if (board[2] != ' ' && board[2] == board[4] && board[2] == board[6]) {
        return board[2];
    }
    
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') return ' ';
    }
    
    return 'D';
}

int getComputerMove(const vector<char>& board) {
    vector<int> emptyCells;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') emptyCells.push_back(i);
    }
    
    for (size_t i = 0; i < emptyCells.size(); i++) {
        vector<char> tempBoard = board;
        tempBoard[emptyCells[i]] = 'O';
        if (checkWinner(tempBoard) == 'O') return emptyCells[i];
    }
    
    for (size_t i = 0; i < emptyCells.size(); i++) {
        vector<char> tempBoard = board;
        tempBoard[emptyCells[i]] = 'X';
        if (checkWinner(tempBoard) == 'X') return emptyCells[i];
    }
    
    if (board[4] == ' ') return 4;
    
    int corners[] = {0, 2, 6, 8};
    for (int i = 0; i < 4; i++) {
        for (size_t j = 0; j < emptyCells.size(); j++) {
            if (emptyCells[j] == corners[i]) return corners[i];
        }
    }
    
    srand(time(NULL));
    return emptyCells[rand() % emptyCells.size()];
}

void showGameResult(int result, int pointsEarned) {
    setColor(14); 
    cout << "\n\t=================================================\n";
    cout << "\t|               HASIL PERTANDINGAN               |\n";
    cout << "\t==================================================\n\n";
    
    switch(result) {
        case 1:
            setColor(10);
            cout << "\t        ANDA MENANG!\n\n";
            break;
        case 0:
            setColor(11);
            cout << "\t        SERI!\n\n";
            break;
        case -1:
            setColor(12);
            cout << "\t        KOMPUTER MENANG!\n\n";
            break;
    }
    
    setColor(14); 
    cout << "\t        Score yang didapat: ";
    setColor(10); 
    cout << "+" << pointsEarned << " poin\n\n";
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|       STATISTIK " << currentPlayer->name;
    for(int i = 0; i < 35 - currentPlayer->name.length(); i++) cout << " ";
    cout << "|\n";
    cout << "\t================================================\n\n";
    
    setColor(7); 
    cout << "\t   Total Games: " << currentPlayer->totalGames << endl;
    cout << "\t   Wins       : " << currentPlayer->wins << endl;
    cout << "\t   Draws      : " << currentPlayer->draws << endl;
    cout << "\t   Losses     : " << currentPlayer->losses << endl;
    cout << "\t   Total Score: " << currentPlayer->totalScore << endl << endl;
    
    setColor(10); 
    cout << "\t        Data telah disimpan ke file " << FILENAME << endl;
}

void showGameResultForTwoPlayers(int result, Player* p1, Player* p2) {
    setColor(14); 
    cout << "\n\t=================================================\n";
    cout << "\t|               HASIL PERTANDINGAN               |\n";
    cout << "\t==================================================\n\n";
    
    switch(result) {
        case 1:
            setColor(10);
            cout << "\t        " << p1->name << " (X) MENANG!\n\n";
            break;
        case 2:
            setColor(10);
            cout << "\t        " << p2->name << " (O) MENANG!\n\n";
            break;
        case 0:
            setColor(11);
            cout << "\t        SERI!\n\n";
            break;
    }
    
    if (result == 1) {
        setColor(14); 
        cout << "\t        Score yang didapat " << p1->name << ": +3 poin\n";
        cout << "\t        Score yang didapat " << p2->name << ": +0 poin\n\n";
    } else if (result == 2) {
        setColor(14); 
        cout << "\t        Score yang didapat " << p1->name << ": +0 poin\n";
        cout << "\t        Score yang didapat " << p2->name << ": +3 poin\n\n";
    } else {
        setColor(14); 
        cout << "\t        Score yang didapat " << p1->name << ": +1 poin\n";
        cout << "\t        Score yang didapat " << p2->name << ": +1 poin\n\n";
    }
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|       STATISTIK " << p1->name;
    for(int i = 0; i < 35 - p1->name.length(); i++) cout << " ";
    cout << "|\n";
    cout << "\t================================================\n\n";
    
    setColor(7); 
    cout << "\t   Total Games: " << p1->totalGames << endl;
    cout << "\t   Wins       : " << p1->wins << endl;
    cout << "\t   Draws      : " << p1->draws << endl;
    cout << "\t   Losses     : " << p1->losses << endl;
    cout << "\t   Total Score: " << p1->totalScore << endl << endl;
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|       STATISTIK " << p2->name;
    for(int i = 0; i < 35 - p2->name.length(); i++) cout << " ";
    cout << "|\n";
    cout << "\t================================================\n\n";
    
    setColor(7); 
    cout << "\t   Total Games: " << p2->totalGames << endl;
    cout << "\t   Wins       : " << p2->wins << endl;
    cout << "\t   Draws      : " << p2->draws << endl;
    cout << "\t   Losses     : " << p2->losses << endl;
    cout << "\t   Total Score: " << p2->totalScore << endl << endl;
    
    setColor(10); 
    cout << "\t        Data telah disimpan ke file " << FILENAME << endl;
}

void playVsComputer() {
    vector<char> board(9, ' ');
    char humanSymbol = 'X';
    char computerSymbol = 'O';
    bool humanTurn = true;
    
    while (true) {
        clearScreen();
        showHeader();
        displayBoard(board, true);
        
        char winner = checkWinner(board);
        if (winner != ' ') {
            if (winner == 'D') {
                currentPlayer->totalGames++;
                currentPlayer->draws++;
                currentPlayer->totalScore += 1;
                showGameResult(0, 1);
            } else if (winner == humanSymbol) {
                currentPlayer->totalGames++;
                currentPlayer->wins++;
                currentPlayer->totalScore += 3;
                showGameResult(1, 3);
            } else {
                currentPlayer->totalGames++;
                currentPlayer->losses++;
                showGameResult(-1, 0);
            }
            savePlayers();
            break;
        }
        
        if (humanTurn) {
            setColor(14); 
            cout << "\t      Giliran Anda (X)\n";
            int position;
            
            while (true) {
                setColor(10); 
                cout << "\t--> Masukkan posisi (1-9): ";
                setColor(7); 
                cin >> position;
                
                if (cin.fail() || position < 1 || position > 9) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    setColor(12); 
                    cout << "\t[!] Posisi tidak valid! Masukkan angka 1-9.\n";
                    continue;
                }
                
                if (board[position-1] != ' ') {
                    setColor(12); 
                    cout << "\t[!] Posisi sudah terisi! Pilih posisi lain.\n";
                    continue;
                }
                break;
            }
            
            board[position-1] = humanSymbol;
            humanTurn = false;
        } else {
            setColor(11);
            cout << "\t      Komputer sedang berpikir";
            for(int i = 0; i < 3; i++) {
                cout << ".";
                Sleep(500);
            }
            cout << "\n";
            
            int computerMove = getComputerMove(board);
            board[computerMove] = computerSymbol;
            
            setColor(12); 
            cout << "\t      Komputer memilih posisi: " << computerMove + 1 << "\n\n";
            humanTurn = true;
            
            displayBoard(board);
            setColor(8); 
            cout << "\t--> Tekan Enter untuk melanjutkan...";
            cin.ignore();
            cin.get();
        }
    }
}

void showGameModeMenu() {
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|             PILIH MODE PERMAINAN             |\n";
    cout << "\t================================================\n\n";
    
    setColor(14); 
    cout << "\t      1.  VS Player (2 Pemain)\n";
    cout << "\t      2.  VS Komputer\n";
    cout << "\t      3.  Kembali ke Menu Utama\n\n";
    
    setColor(10); 
    cout << "\t--> Pilihan Anda: ";
    setColor(7);
}

void playVsPlayer() {
    clearScreen();
    showHeader();
    
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|               MODE VS PLAYER                 |\n";
    cout << "\t================================================\n\n";
    
    setColor(14); 
    cout << "\n\t[*] Memilih Player 1 (X):\n";
    player1 = selectPlayerFromList("--> Pilih Player 1");
    if (!player1) return;
    
    setColor(14); 
    cout << "\n\t[*] Memilih Player 2 (O):\n";
    player2 = selectPlayerFromList("--> Pilih Player 2");
    if (!player2) return;
    
    if (player1 == player2) {
        setColor(12); 
        cout << "\n\t[!] Tidak boleh memilih player yang sama!\n";
        pressEnterToContinue();
        return;
    }
    
    clearScreen();
    showHeader();
    setColor(11); 
    cout << "\t================================================\n";
    cout << "\t|               MODE VS PLAYER                 |\n";
    cout << "\t================================================\n\n";
    
    setColor(10); 
    cout << "\t[+] Player 1 (X): " << player1->name << "\n";
    cout << "\t[+] Player 2 (O): " << player2->name << "\n\n";
    
    setColor(14); 
    cout << "\t--> Tekan Enter untuk memulai permainan...";
    cin.ignore();
    cin.get();
    
    vector<char> board(9, ' ');
    bool player1Turn = true;
    
    while (true) {
        clearScreen();
        showHeader();
        setColor(11); 
        cout << "\t================================================\n";
        cout << "\t|               MODE VS PLAYER                 |\n";
        cout << "\t================================================\n\n";
        
        setColor(10); 
        cout << "\t    Player 1 (X): " << player1->name << "\n";
        cout << "\t    Player 2 (O): " << player2->name << "\n\n";
        
        displayBoard(board, true);
        
        char winner = checkWinner(board);
        if (winner != ' ') {
            if (winner == 'D') {
                player1->totalGames++;
                player1->draws++;
                player1->totalScore += 1;
                
                player2->totalGames++;
                player2->draws++;
                player2->totalScore += 1;
                
                showGameResultForTwoPlayers(0, player1, player2);
            } else if (winner == 'X') {
                player1->totalGames++;
                player1->wins++;
                player1->totalScore += 3;
                
                player2->totalGames++;
                player2->losses++;
                
                showGameResultForTwoPlayers(1, player1, player2);
            } else if (winner == 'O') {
                player1->totalGames++;
                player1->losses++;
                
                player2->totalGames++;
                player2->wins++;
                player2->totalScore += 3;
                
                showGameResultForTwoPlayers(2, player1, player2);
            }
            savePlayers();
            break;
        }
        
        if (player1Turn) {
            setColor(14); 
            cout << "\t      Giliran " << player1->name << " (X)\n";
        } else {
            setColor(14); 
            cout << "\t      Giliran " << player2->name << " (O)\n";
        }
        
        int position;
        
        while (true) {
            setColor(10); 
            cout << "\t--> Masukkan posisi (1-9): ";
            setColor(7); 
            cin >> position;
            
            if (cin.fail() || position < 1 || position > 9) {
                cin.clear();
                cin.ignore(10000, '\n');
                setColor(12); 
                cout << "\t[!] Posisi tidak valid! Masukkan angka 1-9.\n";
                continue;
            }
            
            if (board[position-1] != ' ') {
                setColor(12); 
                cout << "\t[!] Posisi sudah terisi! Pilih posisi lain.\n";
                continue;
            }
            break;
        }
        
        board[position-1] = player1Turn ? 'X' : 'O';
        player1Turn = !player1Turn;
    }
}

void playGame() {
    if (currentPlayer == NULL) {
        setColor(12); 
        cout << "\n\t[!] Silakan pilih atau buat player terlebih dahulu!\n";
        pressEnterToContinue();
        return;
    }
    
    char playAgain = 'y';
    
    do {
        clearScreen();
        showHeader();
        showGameModeMenu();
        
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            playVsPlayer();
        } else if (choice == 2) {
            playVsComputer();
        } else if (choice == 3) {
            cin.ignore();
            return;
        } else {
            setColor(12); 
            cout << "\n\t[!] Pilihan tidak valid!\n";
            cin.ignore();
            pressEnterToContinue();
            return;
        }
        
        setColor(14); 
        cout << "\n\t--> Main lagi? (y/n): ";
        setColor(7); 
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cin.ignore();
}

int main() {
    srand(time(NULL));
    SetConsoleTitle("TIC TAC TOE GAME - By Dev Team");
    
    ifstream file(FILENAME.c_str());
    if (!file.is_open()) {
        clearScreen();
        showHeader();
        setColor(11); 
        cout << "\n\t[!] File player tidak ditemukan. Membuat file baru...\n";
        showLoading();
        file.close();
        ofstream newFile(FILENAME.c_str());
        newFile.close();
    } else {
        file.close();
    }
    
    loadPlayers();
    
    while (true) {
        clearScreen();
        showHeader();
        showMenu();
        
        setColor(10); 
        cout << "\t--> Pilihan Anda: ";
        setColor(7); 
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                createNewPlayer();
                break;
            case 2:
                selectExistingPlayer();
                break;
            case 3:
                showLeaderboard();
                break;
            case 4:
                playGame();
                break;
            case 5:
                clearScreen();
                showHeader();
                setColor(14); 
                cout << "\n\t================================================\n";
                cout << "\t|           TERIMA KASIH TELAH BERMAIN!          |\n";
                cout << "\t|                                                |\n";
                cout << "\t|              Sampai jumpa lagi!                |\n";
                cout << "\t==================================================\n\n";
                setColor(7); 
                cout << "\n";
                Sleep(2000);
                return 0;
            default:
                setColor(12);
                cout << "\n\t[!] Pilihan tidak valid!\n";
                pressEnterToContinue();
        }
    }
    
    return 0;
}
