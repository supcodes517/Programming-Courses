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
    
    int getRank() const {
        if (score >= 100) return 1;      
        else if (score >= 50) return 2;  
        else if (score >= 20) return 3;  
        else return 4;                   
    }
};

string getRankLabel(int rank) {
    switch (rank) {
        case 1: return "<<< CHAMPION >>>";
        case 2: return "<<  ELITE   >>";
        case 3: return "<   PRO    >";
        default: return "    ROOKIE   ";
    }
}


char board[3][3];
vector<Player> players;
int currentPlayerIndex = -1;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setRankColor(int rank) {
    if (rank == 1)      setColor(14); 
    else if (rank == 2) setColor(7); 
    else if (rank == 3) setColor(6);  
    else                setColor(15); 
}

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
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

    int paddingTop = (consoleHeight - lines) / 2;
    for (int i = 0; i < paddingTop; i++) cout << endl;

    for (int i = 0; i < lines; i++) {
        int paddingLeft = (consoleWidth - title[i].length()) / 2;
        if (paddingLeft > 0)
            cout << string(paddingLeft, ' ');
        cout << title[i] << endl;
    }
}

void loadingScreen() {
    system("cls");

    string title[] = {
        "                               ███████████████",
        "      █ TIC TAC TOE █",
        "                               ███████████████"
    };

    CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
int consoleWidth  = csbi.dwSize.X;
int consoleHeight = csbi.dwSize.Y;


    int lines = sizeof(title) / sizeof(title[0]);
    int barWidth = 40;
    int totalHeight = lines + 2 + 1; 

    int paddingTop = (consoleHeight - totalHeight) / 2;
    for(int i = 0; i < paddingTop; i++) cout << "\n";

    for(int i = 0; i < lines; i++) {
        int paddingLeft = (consoleWidth - title[i].length()) / 2;
        if(paddingLeft > 0) cout << string(paddingLeft, ' ');
        setColor(14);
        cout << title[i] << endl;
    }

    cout << "\n"; 


    int barPaddingLeft = (consoleWidth - barWidth - 6) / 2;
    for(int i = 0; i <= barWidth; i++) {
        cout << string(barPaddingLeft, ' ') << "[";
        setColor(11);
        for(int j = 0; j < barWidth; j++) {
            if(j < i) cout << "=";
            else cout << " ";
        }
        setColor(7);
        cout << "] " << (i * 100 / barWidth) << "%\r";
        cout.flush();
        Sleep(30);
    }

    cout << "\n\n";
    setColor(7);
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
    cout << "\n==============================\n";
    cout << "Nama : " << left << setw(12) << p.nama 
         << " [" << p.getRank() << "]\n";
    cout << "Rank : " << getRankLabel(p.getRank()) << "\n";
    cout << "==============================\n";
    cout << "Games : " << p.totalGames << endl;
    cout << "Wins  : " << p.totalWins << endl;
    cout << "Draws : " << p.totalDraws << endl;
    cout << "Loss  : " << p.totalLosses << endl;
    cout << "Score : " << p.score << endl;
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

    while (true) {
        system("cls");
        cout << "\n" << prompt << "\n";

        int wNama = 4;   
        int wScore = 5;  
        int wGames = 5;  
        int wW = 1, wD = 1, wL = 1;

        for (auto& p : players) {
            wNama  = max(wNama,  (int)p.nama.length());
            wScore = max(wScore, (int)to_string(p.score).length());
            wGames = max(wGames, (int)to_string(p.totalGames).length());
            wW     = max(wW,     (int)to_string(p.totalWins).length());
            wD     = max(wD,     (int)to_string(p.totalDraws).length());
            wL     = max(wL,     (int)to_string(p.totalLosses).length());
        }

        cout << "+------+-" << string(wNama, '-')
             << "-+-" << string(wScore, '-')
             << "-+-" << string(wGames, '-')
             << "-+-" << string(wW, '-')
             << "-+-" << string(wD, '-')
             << "-+-" << string(wL, '-') << "-+\n";

        cout << "|  NO  | Nama"
             << string(wNama - 4, ' ')
             << " | Score"
             << string(wScore - 5, ' ')
             << " | Games"
             << string(wGames - 5, ' ')
             << " | W"
             << string(wW - 1, ' ')
             << " | D"
             << string(wD - 1, ' ')
             << " | L"
             << string(wL - 1, ' ')
             << " |\n";

        cout << "|------|-" << string(wNama, '-')
             << "-|-" << string(wScore, '-')
             << "-|-" << string(wGames, '-')
             << "-|-" << string(wW, '-')
             << "-|-" << string(wD, '-')
             << "-|-" << string(wL, '-') << "-|\n";

CONSOLE_SCREEN_BUFFER_INFO csbi;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);


        for (int i = 0; i < (int)players.size(); i++) {
            Player &p = players[i];

            if (i == lockedIndex) {
                setColor(8);
                cout << "|[X]";
            } else {
                setColor(7);
                cout << "|[ ]";
            }

cout << left
     << setw(3) << i + 1 << "| "
     << setw(wNama)  << p.nama << " | "
     << setw(wScore) << p.score << " | "
     << setw(wGames) << p.totalGames << " | "
     << setw(wW)     << p.totalWins << " | "
     << setw(wD)     << p.totalDraws << " | "
     << setw(wL)     << p.totalLosses << " |";

if (i == lockedIndex) {
    setColor(8);
    cout << " ( SUDAH DIPILIH )";
    setColor(7);
}

cout << "\n";
        }

        cout << "+------+-" << string(wNama, '-')
             << "-+-" << string(wScore, '-')
             << "-+-" << string(wGames, '-')
             << "-+-" << string(wW, '-')
             << "-+-" << string(wD, '-')
             << "-+-" << string(wL, '-') << "-+\n";

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
            cout << "🎉 " << players[idx1].nama << " MENANG! 🎉\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idx1].totalGames++;
    players[idx1].totalWins++;
    players[idx1].score += 3;

players[idx2].totalGames++;
players[idx2].totalLosses++;

savePlayers();
showStats(players[idx1]);
showStats(players[idx2]);
pause();
return;

        }
        if (checkWin('O')) {
            cout << "🎉 " << players[idx2].nama << " MENANG! 🎉\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapfatkan : +3 Poin"<< endl;
            players[idx2].totalGames++;
players[idx2].totalWins++;
players[idx2].score += 3;

players[idx1].totalGames++;
players[idx1].totalLosses++;

savePlayers();
showStats(players[idx1]);
showStats(players[idx2]);
pause();
return;

        }
        if (isDraw()) {
            cout << "SERI!\n"; 
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : SERI" << endl;
            cout << "Score Yang Di Dapatkan : +1 Poin"<< endl;
            players[idx1].totalGames++; players[idx1].totalDraws++; players[idx1].score++;
            players[idx2].totalGames++; players[idx2].totalDraws++; players[idx2].score++;
            savePlayers(); showStats(players[idx1]); showStats(players[idx2]); pause(); return;
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
        Sleep(500);
        cout << ".";
        cout.flush();
    }
    cout << endl;

    Sleep(1000);

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
        Sleep(500);
        cout << ".";
        cout.flush();
    }
    cout << endl;

    Sleep(1000);
    

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

int minimax(bool isMax, int depth = 0) {
    int score = evaluate();

    if (score == 10 || score == -10)
        return score - depth;  
    if (!movesLeft())
        return 0;
    
    if (depth > 9) 
        return 0;

    if (isMax) { 
        int best = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    best = max(best, minimax(false, depth+1));
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
                    best = min(best, minimax(true, depth+1));
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

    cout << "Komputer Sedang Memilih Kotak (";
    setColor(9); cout << "O"; setColor(7);
    cout << ") ";
    cout.flush();

    for (int i = 0; i < 3; i++) {
        Sleep(500);
        cout << ".";
        cout.flush();
    }
    cout << endl;

    auto move = findBestMove();

    if (move.first == -1 || move.second == -1) {
        return; 
    }

    r = move.first;
    c = move.second;

    board[r][c] = 'O';

    cout << "Komputer memilih posisi: "
         << (r * 3 + c + 1) << endl;
}


void showResult(int idx, string hasil, int poin) {
    if (hasil == "MENANG") {
        cout << "🎉" << players[idx].nama << " MENANG! 🎉\n";
    } else if(hasil == "KALAH") {
        cout << "💻 KOMPUTER MENANG! 💻\n";
    } else {
        cout << "SERI !";
    }
    cout << "\n======================================\n";
    cout << "          HASIL PERTANDINGAN          \n";
    cout << "======================================\n";
    if (hasil == "MENANG") setColor(10);      
    else if (hasil == "KALAH") setColor(12);  
    else setColor(14);                         
    cout << "Hasil : " << hasil << endl;
    setColor(7);
    cout << "Score Yang Didapatkan : +" << poin << " Poin\n";
    players[idx].totalGames++;
    if (hasil == "MENANG") players[idx].totalWins++;
    else if (hasil == "KALAH") players[idx].totalLosses++;
    else players[idx].totalDraws++;
    players[idx].score += poin;
    savePlayers();
    showStats(players[idx]);
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    pause();
;
}


void playVsComputer(int idx1, void(*computerMoveFunc)()) {
    system("cls");
    cout << "======================================\n";
    cout << "            TIC TAC TOE GAME          \n";
    cout << "======================================\n";
    resetBoard();
    printGuide();
    printBoard();

    while (true) {
        int pos;
        cout << "Giliran Anda (";
        setColor(12); cout << "X"; setColor(7);
        cout << ") : ";

        cin >> pos;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka 1-9.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (pos < 1 || pos > 9 || board[r][c] == 'X' || board[r][c] == 'O') {
            cout << "Posisi tidak valid!\n";
            continue;
        }

        board[r][c] = 'X';
        printBoard();

        if (checkWin('X')) { showResult(idx1, "MENANG", 3); return; }
        if (isDraw()) { showResult(idx1, "SERI", 1); return; }

        computerMoveFunc();
        printBoard();

        if (checkWin('O')) { showResult(idx1, "KALAH", 0); return; }
    }
}

void playVsComputerEasy(int idx1) {
    playVsComputer(idx1, computerMoveEasy);
}

void playVsComputerMedium(int idx1) {
    playVsComputer(idx1, computerMoveMedium);
}

void playVsComputerHard(int idx1) {
    playVsComputer(idx1, computerMoveHard);
}


void leaderboard() {
    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";

    sort(players.begin(), players.end(), [](Player &a, Player &b){
        return a.score > b.score;
    });

    

    cout << "+------+----------------+---------+-------+-----+-----+-----+\n";
    cout << "| " << left  << setw(5)  << "Rank" 
         << "| " << left  << setw(15) << "Nama"
         << "| " << right << setw(7) << "Score"
         << " | " << right << setw(5) << "Games"
         << " | " << right << setw(3) << "W"
         << " | " << right << setw(3) << "D"
         << " | " << right << setw(3) << "L"
         << " |\n";

    cout << "|------|----------------|---------|-------|-----|-----|-----|\n";

    int limit = min(10, (int)players.size());
    for (int i = 0; i < limit; i++) {
        Player &p = players[i];

        if (i == 0) setColor(14);  
        else if (i == 1) setColor(7);  
        else if (i == 2) setColor(6);  
        else setColor(15); 


        cout << "| " << left  << setw(5)  << (i+1)
             << "| " << left  << setw(15) << p.nama
             << "| " << right << setw(7) << p.score
             << " | " << right << setw(5) << p.totalGames
             << " | " << right << setw(3) << p.totalWins
             << " | " << right << setw(3) << p.totalDraws
             << " | " << right << setw(3) << p.totalLosses
             << " |\n";
    }
    setColor(15); 
    cout << "+------+----------------+---------+-------+-----+-----+-----+\n";

    cout << "\n================================\n";
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            loadingScreen();
    system("cls");
            playVsComputerEasy(currentPlayerIndex);
            loadingScreen();
            break;
        }
        else if (choice3 == 2) {
            loadingScreen();
    system("cls");
            playVsComputerMedium(currentPlayerIndex);
            loadingScreen();
            break;
        }
        else if (choice3 == 3) {
            loadingScreen();
    system("cls");
            playVsComputerHard(currentPlayerIndex);
            loadingScreen();
            break;
        }
        else if (choice3 == 4) {
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
    loadingScreen();
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
            loadingScreen();
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
            loadingScreen();
        	menuDifficulty(currentPlayerIndex);
            break;
        } else if (choice2 == 3) break;
        else { cout << "Pilihan Tidak Valid!\n"; pause(); }
    }
    break;
}
            case 2: {
                loadingScreen();
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
            loadingScreen();
    system("cls");
            int idx2 = selectExistingPlayer("=== Pilih Player 2 ===", idx1);
            if (idx2 == -1 || idx2 == idx1) { cout << "Player tidak valid!\n"; pause(); continue; }
            playVsPlayer(idx1, idx2);
            loadingScreen();
            break;
        } else if (choice2 == 2) {
            loadingScreen();
    system("cls");
            menuDifficulty(idx1);
            loadingScreen();
        } else if (choice2 == 3) {
            loadingScreen();
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
                loadingScreen();
    system("cls");
			 leaderboard();
             loadingScreen();
             break;}
             
            case 4: {
                loadingScreen();
    system("cls");
    
			cout << "Terima kasih telah bermain!\n"; return;}
            default: cout << "Pilihan tidak valid!\n"; pause(); break;
        }
    }
}



int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    

    srand(time(0));
    players = loadPlayers();
    loadingScreen();
    menu();

    return 0;
}