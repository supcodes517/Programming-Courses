// NAMA : MIZANI ALRIYZQI
// NIM : 25000018037


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <thread>
#include <chrono>
#include <limits>
#include <iomanip>

using namespace std;

const string FILENAME = "players.txt";

struct Player {
    string nama;
    int totalGames = 0;
    int totalWins = 0;
    int totalDraws = 0;
    int totalLosses = 0;
    int score = 0;
};



char board[3][3];
vector<Player> players;
int currentPlayerIndex = -1;

void pause() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void resetBoard() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printGuide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void printTitleCenter(string title[], int lines) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    int consoleWidth  = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // ===== CENTER VERTIKAL =====
    int paddingTop = (consoleHeight - lines) / 2;
    for (int i = 0; i < paddingTop; i++) cout << endl;

    // ===== CENTER HORIZONTAL =====
    for (int i = 0; i < lines; i++) {
        int paddingLeft = (consoleWidth - title[i].length()) / 2;
        if (paddingLeft > 0)
            cout << string(paddingLeft, ' ');
        cout << title[i] << endl;
    }
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {

            if (board[i][j] == 'X') {
                setColor(12);
                cout << 'X';
            }
            else if (board[i][j] == 'O') {
                setColor(9);
                cout << 'O';
            }
            else {
                setColor(7);
                cout << ' ';
            }

            setColor(7);

            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---+---+---\n";
    }
    cout << "\n";
}


vector<Player> loadPlayers() {
    vector<Player> data;
    ifstream file(FILENAME);

    if (!file.is_open())
        return data;

    Player p;
    string line;

    while (getline(file, line)) {
        if (line.find("NAMA") != string::npos)
            p.nama = line.substr(line.find(":") + 2);
        else if (line.find("GAMES") != string::npos)
            p.totalGames = stoi(line.substr(line.find(":") + 2));
        else if (line.find("WINS") != string::npos)
            p.totalWins = stoi(line.substr(line.find(":") + 2));
        else if (line.find("DRAWS") != string::npos)
            p.totalDraws = stoi(line.substr(line.find(":") + 2));
        else if (line.find("LOSS") != string::npos)
            p.totalLosses = stoi(line.substr(line.find(":") + 2));
        else if (line.find("SCORE") != string::npos)
            p.score = stoi(line.substr(line.find(":") + 2));
        else if (line == "---") {
            data.push_back(p);
            p = Player();
        }
    }

    file.close();
    return data;
}



void savePlayers() {
    ofstream file(FILENAME);
    for (const auto& p : players) {
        file << "NAMA  : " << p.nama << "\n";
        file << "GAMES : " << p.totalGames << "\n";
        file << "WINS  : " << p.totalWins << "\n";
        file << "DRAWS : " << p.totalDraws << "\n";
        file << "LOSS  : " << p.totalLosses << "\n";
        file << "SCORE : " << p.score << "\n";
        file << "---\n";
    }
}


int findPlayer(const string& name) {
    for (int i = 0; i < (int)players.size(); i++)
        if (players[i].nama == name)
            return i;
    return -1;
}

void showStats(const Player& p) {
    cout << "\nStatistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.totalGames << endl;
    cout << "- Wins: " << p.totalWins << endl;
    cout << "- Draws: " << p.totalDraws << endl;
    cout << "- Losses: " << p.totalLosses << endl;
    cout << "- Total Score: " << p.score << endl << endl;
}

bool checkWin(char mark) {
    for (int i = 0; i < 3; i++)
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark))
            return true;

    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark))
        return true;

    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

int selectExistingPlayer(const string& prompt, int lockedIndex = -1) {
    if (players.empty()) {
        cout << "Belum ada player.\n";
        pause();
        return -1;
    }

    while (true) {  // ?? LOOP PENTING
        system("cls");
        cout << "\n" << prompt << "\n";

        cout << "|Rank | Nama           |  Score  |  Games  |  W  |  D  |  L  |\n";
        cout << "|-----|----------------|---------|---------|-----|-----|-----|\n";

        for (int i = 0; i < (int)players.size(); i++) {
            Player &p = players[i];

            if (i == lockedIndex) {
                setColor(8);
                cout << "[X]";
            } else {
                setColor(7);
                cout << "[ ]";
            }

            cout << left
                 << setw(3) << i + 1
                 << "| " << setw(30) << p.nama
                 << "|   " << setw(6) << p.score
                 << "|   " << setw(6) << p.totalGames
                 << "|  " << setw(3) << p.totalWins
                 << "|  " << setw(3) << p.totalDraws
                 << "|  " << setw(3) << p.totalLosses << "|";

            if (i == lockedIndex) {
                cout << "    ( SUDAH DIPILIH )";
                setColor(7);
            }
            cout << "\n";
        }
        
        

        cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
        int pick;
        cin >> pick;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid!\n";
            pause();
            continue;
        }

        if (pick == 0)
            return -1;

        if (pick < 1 || pick > (int)players.size()) {
            cout << "Pilihan tidak valid!\n";
            pause();
            continue;
        }

        int idx = pick - 1;

        if (idx == lockedIndex) {
            cout << "? Player ini sudah dipilih! Pilih player lain.\n";
            pause();
            continue; 
        }

        return idx; 
    }
}



void playVsPlayer(int idx1, int idx2) {
    system("cls");
    cout << "======================================\n";
    cout << "            TIC TAC TOE GAME          \n";
    cout << "======================================\n";
    resetBoard();
    printGuide();
    printBoard();

    bool turnX = true;
    while (true) {
        printBoard();
        int pos;
        string currentPlayer = turnX ? players[idx1].nama : players[idx2].nama;
        cout << "Giliran " << currentPlayer << " (";
		if (turnX) {
    	setColor(12);
    	cout << "X";
		} else {
   		setColor(9);
    	cout << "O";
		}
		setColor(7);
		cout << ") Masukkan posisi (1-9): ";

        cin >> pos;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid!\n";
            continue;
        }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;

        if (pos < 1 || pos > 9 || board[r][c] == 'X' || board[r][c] == 'O') {
            cout << "Posisi tidak valid atau sudah terisi!\n";
            continue;
        }

        board[r][c] = turnX ? 'X' : 'O';

        if (checkWin('X')) {
            cout << "?? ANDA MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalWins++; players[idx1].score += 3;
            savePlayers(); showStats(players[idx1]); pause(); return;
            savePlayers(); showStats(players[idx2]); pause(); return;
        }
        if (checkWin('O')) {
            cout << "?? ANDA MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idx2].totalGames++; players[idx2].totalWins++; players[idx2].score += 3;
            savePlayers(); showStats(players[idx1]); pause(); return;
            savePlayers(); showStats(players[idx2]); pause(); return;
        }
        if (isDraw()) {
            cout << "SERI!\n"; 
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : SERI" << endl;
            cout << "Score Yang Di Dapatkan : +1 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalDraws++; players[idx1].score++; savePlayers(); showStats(players[idx1]); pause(); return;
            players[idx2].totalGames++; players[idx2].totalDraws++; players[idx2].score++; savePlayers(); showStats(players[idx2]); pause(); return;
        }

        turnX = !turnX;
    }
}



void computerMoveEasy() {
    int r, c;

    cout << "Komputer Sedang Memilih Kotak ";
    cout << "(";
    setColor(9);
    cout << "O";
    setColor(7);
    cout << ") ";
    cout.flush();

    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    cout << endl;

    this_thread::sleep_for(chrono::seconds(1));

    do {
        r = rand() % 3;
        c = rand() % 3;
    } while (board[r][c] == 'X' || board[r][c] == 'O');

    board[r][c] = 'O';

    cout << "Komputer memilih posisi: " 
         << (r * 3 + c + 1) << endl;
}



bool findWinningMove(char p, int &r, int &c) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = p;
                if (checkWin(p)) {
                    board[i][j] = ' ';
                    r = i; c = j;
                    return true;
                }
                board[i][j] = ' ';
            }
        }
    }
    return false;
}


void computerMoveMedium() {
    int r =-1, c = -1;

    cout << "Komputer Sedang Memilih Kotak ";
    cout << "(";
    setColor(9);
    cout << "O";
    setColor(7);
    cout << ") ";
    cout.flush();

    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    cout << endl;

    this_thread::sleep_for(chrono::seconds(1));
    

    if (findWinningMove('O', r, c)) {
        board[r][c] = 'O';
    }

    else if (findWinningMove('X', r, c)) {
        board[r][c] = 'O';
    }

    else if (board[1][1] == ' ') {
        r = 1; c = 1;
        board[r][c] = 'O';
    }
    else {
        do {
            r = rand() % 3;
            c = rand() % 3;
        } while (board[r][c] != ' ');
        board[r][c] = 'O';
    }



    cout << "Komputer memilih posisi: "
         << (r * 3 + c + 1) << endl;
}


    int evaluate() {
    if (checkWin('O')) return +10;
    if (checkWin('X')) return -10;
    return 0;
}

	bool movesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return true;
    return false;
}

int minimax(bool isMax) {
    int score = evaluate();

    if (score == 10 || score == -10)
        return score;

    if (!movesLeft())
        return 0;

    if (isMax) { 
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(false));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    } else { 
        int best = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    best = min(best, minimax(true));
                    board[i][j] = ' ';
                }
            }
        }
        return best;
    }
}

pair<int,int> findBestMove() {
    int bestVal = -1000;
    pair<int,int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveVal = minimax(false);
                board[i][j] = ' ';

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}

void computerMoveHard() {
    int r, c;

    cout << "Komputer Sedang Memilih Kotak ";
    cout << "(";
    setColor(9);
    cout << "O";
    setColor(7);
    cout << ") ";
    cout.flush();

    for (int i = 0; i < 3; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << ".";
        cout.flush();
    }
    cout << endl;

    this_thread::sleep_for(chrono::seconds(1));
    
    auto move = findBestMove();
    r = move.first;
    c = move.second;

    board[r][c] = 'O';

    cout << "Komputer memilih posisi: " 
         << (r * 3 + c + 1) << endl;
}




void playVsComputerEasy(int idx1) {
    system("cls");
    cout << "======================================\n";
    cout << "            TIC TAC TOE GAME          \n";
    cout << "======================================\n";
    resetBoard();
    printGuide();
    printBoard();
    

    while (true) {
        int pos;
        cout << "Giliran Anda ";
        cout << "(";
        setColor(12);
		cout << "X";  
		setColor(7);
		cout << ")";
		cout << " : "; cin >> pos;
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (pos < 1 || pos > 9 || board[r][c] == 'X' || board[r][c] == 'O') { cout << "Posisi tidak valid!\n"; continue; }

        board[r][c] = 'X'; printBoard();
        if (checkWin('X')) {
            cout << "?? ANDA MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalWins++; players[idx1].score += 3;
            savePlayers(); showStats(players[idx1]); pause(); return;
        }
        if (isDraw()) {
            cout << "SERI!\n"; 
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : SERI" << endl;
            cout << "Score Yang Di Dapatkan : +1 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalDraws++; players[idx1].score++; savePlayers(); showStats(players[idx1]); pause(); return;
        }

        computerMoveEasy(); printBoard();
        if (checkWin('O')) {
            cout << "?? KOMPUTER MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : KALAH" << endl;
            cout << "Score Yang Di Dapatkan : +0 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalLosses++; savePlayers(); pause(); return;
        }
        
    }
    cout << "Game selesai!\n";
    pause();
    return;
    
}

void playVsComputerMedium(int idx1) {
    system("cls");
    cout << "======================================\n";
    cout << "            TIC TAC TOE GAME          \n";
    cout << "======================================\n";
    resetBoard();
    printGuide();
    printBoard();
    

    while (true) {
        int pos;
        cout << "Giliran Anda ";
        cout << "(";
        setColor(12);
		cout << "X";  
		setColor(7);
		cout << ")";
		cout << " : "; cin >> pos;
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (pos < 1 || pos > 9 || board[r][c] == 'X' || board[r][c] == 'O') { cout << "Posisi tidak valid!\n"; continue; }

        board[r][c] = 'X'; printBoard();
        if (checkWin('X')) {
            cout << "?? ANDA MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalWins++; players[idx1].score += 3;
            savePlayers(); showStats(players[idx1]); pause(); return;
        }
        if (isDraw()) {
            cout << "SERI!\n"; 
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : SERI" << endl;
            cout << "Score Yang Di Dapatkan : +1 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalDraws++; players[idx1].score++; savePlayers(); showStats(players[idx1]); pause(); return;
        }

        computerMoveMedium(); printBoard();
        if (checkWin('O')) {
            cout << "?? KOMPUTER MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : KALAH" << endl;
            cout << "Score Yang Di Dapatkan : +0 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalLosses++; savePlayers(); pause(); return;
        }
    }
    cout << "Game selesai!\n";
    pause();
    return;
}

void playVsComputerHard(int idx1) {
    system("cls");
    cout << "======================================\n";
    cout << "            TIC TAC TOE GAME          \n";
    cout << "======================================\n";
    resetBoard();
    printGuide();
    printBoard();
    

    while (true) {
        int pos;
        cout << "Giliran Anda ";
        cout << "(";
        setColor(12);
		cout << "X";  
		setColor(7);
		cout << ")";
		cout << " : "; cin >> pos;
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (pos < 1 || pos > 9 || board[r][c] == 'X' || board[r][c] == 'O') { cout << "Posisi tidak valid!\n"; continue; }

        board[r][c] = 'X'; printBoard();
        if (checkWin('X')) {
            cout << "?? ANDA MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalWins++; players[idx1].score += 3;
            savePlayers(); showStats(players[idx1]); pause(); return;
        }
        if (isDraw()) {
            cout << "SERI!\n"; 
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : SERI" << endl;
            cout << "Score Yang Di Dapatkan : +1 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalDraws++; players[idx1].score++; savePlayers(); pause(); return;
        }

        computerMoveHard(); printBoard();
        if (checkWin('O')) {
            cout << "?? KOMPUTER MENANG! ??\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : KALAH" << endl;
            cout << "Score Yang Di Dapatkan : +0 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalLosses++; savePlayers(); showStats(players[idx1]); pause(); return;
        }
    }
    cout << "Game selesai!\n";
    pause();
    return;
}


void leaderboard() {
    cout << "\n================================";
    cout << "\n        LEADERBOARD";
    cout << "\n  Top 10 Players by Score";
    cout << "\n================================\n\n";

    sort(players.begin(), players.end(), [](Player &a, Player &b){
        return a.score > b.score;
    });

    cout << "Rank | Nama           |  Score  |  Games  |  W  |  D  |  L  |\n";
    cout << "-----|----------------|---------|---------|-----|-----|-----|\n";

    int limit = min(10, (int)players.size());
    for (int i = 0; i < limit; i++) {
        Player &p = players[i];
        cout << "  " << i+1
             << "  | " << p.nama
             << string(30 - p.nama.length(), ' ')
             << "|    " << p.score
             << "    |    " << p.totalGames
             << "    |  " << p.totalWins
             << "  |  " << p.totalDraws
             << "  |  " << p.totalLosses << "  |"
             << "\n";
    }
    cout << "\n================================\n";
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
}

void menuDifficulty(int currentPlayerIndex) {
    int choice3;

    while (true) {
        system("cls");
        cout << "========================\n";
        cout << "    Pilih Difficulty    \n";
        cout << "========================\n";
        cout << "1. Easy\n";
        cout << "2. Medium\n";
        cout << "3. Hard\n";
        cout << "4. Back To Menu\n";
        cout << "Pilihan Anda : ";
        cin >> choice3;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid!\n";
            pause();
            continue;
        }

        if (choice3 == 1) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            playVsComputerEasy(currentPlayerIndex);
    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            break;
        }
        else if (choice3 == 2) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            playVsComputerMedium(currentPlayerIndex);
            for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            break;
        }
        else if (choice3 == 3) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            playVsComputerHard(currentPlayerIndex);
            for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            break;
        }
        else if (choice3 == 4) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            break;
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }
        pause();
        
    }
}

void menu() {
    int choice;
    while (true) {
        system("cls");
        cout << "======================================\n";
        cout << "             TIC TAC TOE              \n";
        cout << "======================================\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player Yang Sudah Ada\n";
        cout << "3. Leaderboard\n";
        cout << "4. Keluar\n";
        cout << "Pilihan Anda: "; cin >> choice;

        switch(choice) {
            case 1: {
            	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
    cout << "\n==============================\n";
    cout << "\n    REGISTRASI PLAYER BARU    \n";
    cout << "\n==============================\n";
    Player p; 
    cout << "Masukkan nama Anda: "; cin >> p.nama;
    players.push_back(p);
    currentPlayerIndex = players.size() - 1;

    cout << "\nPlayer baru berhasil dibuat! \n";
    cout << "Selamat datang, " << p.nama << "!\n";
    showStats(players[currentPlayerIndex]); pause();

    int choice2;
    while (true) {
        system("cls");
        cout << "======================\n";
        cout << "      PILIH MODE      \n";
        cout << "======================\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda : "; cin >> choice2;

        if (choice2 == 1) {
            int idx2 = selectExistingPlayer(
			"=================\n"
			"    Player 2\n"
			"================="
			);

    setColor(7);
            if (idx2 == -1 || idx2 == currentPlayerIndex) { 
                cout << "Player tidak valid!\n"; pause(); continue; 
            }
            playVsPlayer(currentPlayerIndex, idx2); 
            break;
        } else if (choice2 == 2) {
        	menuDifficulty(currentPlayerIndex);
            break;
        } else if (choice2 == 3) break;
        else { cout << "Pilihan Tidak Valid!\n"; pause(); }
    }

    break;
}

case 2: {
	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
    int idx1 = selectExistingPlayer(
			"=================\n"
			"    Player 1\n"
			"=================");


    setColor(7);
    if (idx1 == -1) break;

    int choice2;
    while (true) {
        system("cls");
        cout << "======================\n";
        cout << "      PILIH MODE      \n";
        cout << "======================\n";
        cout << "1. Player1 Vs Player2\n";
        cout << "2. Player1 Vs Computer\n";
        cout << "3. Back To Menu\n";
        cout << "Pilihan Anda : ";cin >> choice2;
        if (choice2 == 1) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            int idx2 = selectExistingPlayer("=== Pilih Player 2 ===", idx1);
            if (idx2 == -1 || idx2 == idx1) { cout << "Player tidak valid!\n"; pause(); continue; }
            playVsPlayer(idx1, idx2);
            break;
        } else if (choice2 == 2) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
        	menuDifficulty(currentPlayerIndex);
        } else if (choice2 == 3) {
        	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
            break;
        } else {
            cout << "Pilihan Tidak Valid!\n";
            pause();
            return;
        }
    }
    break;
}
            case 3: {
            	string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
			 leaderboard(); break;}
            case 4: {
				string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);
    system("cls");
    
			cout << "Terima kasih telah bermain!\n"; return;}
            default: cout << "Pilihan tidak valid!\n"; pause(); break;
        }
    }
}



int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string title[] = {
        "¦¦¦¦¦¦¦¦+ ¦¦+  ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦+   ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+  ¦¦¦¦¦¦+  ¦¦¦¦¦¦¦+",
        "+--¦¦+--+ ¦¦¦ ¦¦+----+    +--¦¦+--+ ¦¦+--¦¦+ ¦¦+----+    +--¦¦+--+ ¦¦+---¦¦+ ¦¦+----+",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦  ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+     ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦¦¦¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦¦¦¦¦+  ",
        "   ¦¦¦    ¦¦¦ ¦¦¦            ¦¦¦    ¦¦+--¦¦¦ ¦¦¦            ¦¦¦    ¦¦¦   ¦¦¦ ¦¦+--+  ",
        "   ¦¦¦    ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    ¦¦¦  ¦¦¦ +¦¦¦¦¦¦+       ¦¦¦    +¦¦¦¦¦¦++ ¦¦¦¦¦¦¦+",
        "   +-+    +-+  +-----+       +-+    +-+  +-+  +-----+       +-+     +-----+  +------+"
    };

    for (int loop = 0; loop < 3; loop++) {
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        printTitleCenter(title, 7);
        Sleep(300);
    }

    cout << "\n\n                       Loading ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

    for (int i = 0; i <= 65; i++) {
        cout << char(219);
        Sleep(30);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    Sleep(500);

    srand(time(0));
    players = loadPlayers();
    menu();

    return 0;
}
