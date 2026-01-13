#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// ===== STRUCT PLAYER =====
struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

// ===== FUNGSI FILE MANAGEMENT =====
void savePlayersToFile(const vector<Player>& players) {
    ofstream file("players.txt");
    if (file.is_open()) {
        for (const auto& p : players) {
            file << p.nama << "," 
                 << p.totalGames << "," 
                 << p.totalWins << "," 
                 << p.totalDraws << "," 
                 << p.totalLosses << "," 
                 << p.score << "\n";
        }
        file.close();
    }
}

vector<Player> loadPlayersFromFile(bool& fileExists) {
    vector<Player> players;
    ifstream file("players.txt");
    
    if (!file.is_open()) {
        fileExists = false;
        return players;
    }
    
    fileExists = true;
    string line;
    while (getline(file, line)) {
        Player p;
        size_t pos = 0;
        string token;
        int field = 0;
        
        line += ",";
        while ((pos = line.find(",")) != string::npos) {
            token = line.substr(0, pos);
            
            switch(field) {
                case 0: p.nama = token; break;
                case 1: p.totalGames = stoi(token); break;
                case 2: p.totalWins = stoi(token); break;
                case 3: p.totalDraws = stoi(token); break;
                case 4: p.totalLosses = stoi(token); break;
                case 5: p.score = stoi(token); break;
            }
            
            line.erase(0, pos + 1);
            field++;
        }
        players.push_back(p);
    }
    file.close();
    return players;
}

// ===== FUNGSI SCORING =====
void updatePlayerStats(Player& player, string result) {
    player.totalGames++;
    
    if (result == "WIN") {
        player.totalWins++;
        player.score += 3;
    } else if (result == "DRAW") {
        player.totalDraws++;
        player.score += 1;
    } else if (result == "LOSE") {
        player.totalLosses++;
    }
}

// ===== FUNGSI DISPLAY =====
void displayHeader() {
    cout << "\n================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n";
}

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
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void displayPlayerStats(const Player& player) {
    cout << "\nStatistik " << player.nama << ":\n";
    cout << "- Total Games: " << player.totalGames << "\n";
    cout << "- Wins: " << player.totalWins << "\n";
    cout << "- Draws: " << player.totalDraws << "\n";
    cout << "- Losses: " << player.totalLosses << "\n";
    cout << "- Total Score: " << player.score << "\n";
}

void displayMatchResult(const Player& player, string result) {
    cout << "\n================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";
    
    if (result == "WIN") {
        cout << "Hasil: MENANG\n";
        cout << "Score yang didapat: +3 poin\n";
    } else if (result == "DRAW") {
        cout << "Hasil: SERI\n";
        cout << "Score yang didapat: +1 poin\n";
    } else {
        cout << "Hasil: KALAH\n";
        cout << "Score yang didapat: +0 poin\n";
    }
    
    displayPlayerStats(player);
    cout << "\nData telah disimpan ke file players.txt\n";
}

void displayLeaderboard(vector<Player> players) {
    cout << "\n================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";
    
    sort(players.begin(), players.end(), [](const Player& a, const Player& b) {
        return a.score > b.score;
    });
    
    cout << "Rank | Nama           | Score | Games | W  | D  | L  |\n";
    cout << "-----|----------------|-------|-------|----|----|----|" << endl;
    
    int limit = min(10, (int)players.size());
    for (int i = 0; i < limit; i++) {
        cout << setw(3) << right << (i+1) << "  | ";
        cout << setw(14) << left << players[i].nama << " | ";
        cout << setw(5) << right << players[i].score << " | ";
        cout << setw(5) << players[i].totalGames << " | ";
        cout << setw(2) << players[i].totalWins << " | ";
        cout << setw(2) << players[i].totalDraws << " | ";
        cout << setw(2) << players[i].totalLosses << " |\n";
    }
    cout << "\n================================\n";
}

void displayPlayerList(const vector<Player>& players) {
    cout << "\n=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           | Score | Games | W  | D  | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";
    
    for (size_t i = 0; i < players.size(); i++) {
        cout << setw(2) << (i+1) << " | ";
        cout << setw(14) << left << players[i].nama << " | ";
        cout << setw(5) << right << players[i].score << " | ";
        cout << setw(5) << players[i].totalGames << " | ";
        cout << setw(2) << players[i].totalWins << " | ";
        cout << setw(2) << players[i].totalDraws << " | ";
        cout << setw(2) << players[i].totalLosses << "\n";
    }
}

// ===== FUNGSI GAME LOGIC =====
bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    }
    
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    
    return false;
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

bool isValidMove(char board[3][3], int position) {
    if (position < 1 || position > 9)
        return false;
    
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    
    return board[row][col] == ' ';
}

void makeMove(char board[3][3], int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    board[row][col] = player;
}

int computerMove(char board[3][3]) {
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];
            
            makeMove(tempBoard, i, 'O');
            if (checkWin(tempBoard, 'O'))
                return i;
        }
    }
    
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];
            
            makeMove(tempBoard, i, 'X');
            if (checkWin(tempBoard, 'X'))
                return i;
        }
    }
    
    if (isValidMove(board, 5))
        return 5;
    
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        if (isValidMove(board, corners[i]))
            return corners[i];
    }
    
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i))
            return i;
    }
    
    return -1;
}

// ===== FUNGSI GAMEPLAY =====
string playVsPlayer(char board[3][3]) {
    char currentPlayer = 'X';
    int position;
    
    while (true) {
        displayBoard(board);
        cout << "Giliran Player " << currentPlayer << "\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> position;
        
        if (!isValidMove(board, position)) {
            cout << "Posisi tidak valid! Coba lagi.\n";
            continue;
        }
        
        makeMove(board, position, currentPlayer);
        
        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "*** Player " << currentPlayer << " MENANG! ***\n";
            return (currentPlayer == 'X') ? "WIN" : "LOSE";
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            return "DRAW";
        }
        
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

string playVsComputer(char board[3][3]) {
    int position;
    
    while (true) {
        displayBoard(board);
        cout << "Giliran Anda (X)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> position;
        
        if (!isValidMove(board, position)) {
            cout << "Posisi tidak valid! Coba lagi.\n";
            continue;
        }
        
        makeMove(board, position, 'X');
        
        if (checkWin(board, 'X')) {
            displayBoard(board);
            cout << "*** ANDA MENANG! ***\n";
            return "WIN";
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            return "DRAW";
        }
        
        cout << "Komputer sedang berpikir...\n";
        int compMove = computerMove(board);
        makeMove(board, compMove, 'O');
        cout << "Komputer memilih posisi: " << compMove << "\n";
        
        if (checkWin(board, 'O')) {
            displayBoard(board);
            cout << "*** KOMPUTER MENANG! ***\n";
            return "LOSE";
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            return "DRAW";
        }
    }
}

// ===== MAIN PROGRAM =====
int main() {
    srand(time(0));
    
    bool fileExists = false;
    vector<Player> players = loadPlayersFromFile(fileExists);
    
    displayHeader();
    
    if (!fileExists) {
        cout << "\nFile player tidak ditemukan. Membuat file baru...\n";
    }
    
    while (true) {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n";
        cout << "\nPilihan Anda: ";
        
        int menuChoice;
        cin >> menuChoice;
        
        if (menuChoice == 4) {
            cout << "\nTerima kasih telah bermain!\n";
            break;
        }
        
        if (menuChoice == 3) {
            if (players.empty()) {
                cout << "\n[X] Belum ada data player!\n";
                cout << "\nTekan Enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
            } else {
                displayLeaderboard(players);
                cout << "\nTekan Enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
            }
            continue;
        }
        
        Player* currentPlayer = nullptr;
        
        if (menuChoice == 1) {
            cout << "\n=== REGISTRASI PLAYER BARU ===\n";
            Player newPlayer;
            cout << "Masukkan nama Anda: ";
            cin.ignore();
            getline(cin, newPlayer.nama);
            
            newPlayer.totalGames = 0;
            newPlayer.totalWins = 0;
            newPlayer.totalDraws = 0;
            newPlayer.totalLosses = 0;
            newPlayer.score = 0;
            
            players.push_back(newPlayer);
            savePlayersToFile(players);
            
            cout << "\nPlayer baru berhasil dibuat!\n";
            cout << "Selamat datang, " << newPlayer.nama << "!\n";
            displayPlayerStats(newPlayer);
            
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            
            currentPlayer = &players.back();
            
        } else if (menuChoice == 2) {
            if (players.empty()) {
                cout << "\n[X] Belum ada player terdaftar!\n";
                cout << "\nTekan Enter untuk kembali ke menu...";
                cin.ignore();
                cin.get();
                continue;
            }
            
            displayPlayerList(players);
            
            int playerChoice;
            cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
            cin >> playerChoice;
            
            if (playerChoice == 0) {
                continue;
            }
            
            if (playerChoice >= 1 && playerChoice <= (int)players.size()) {
                currentPlayer = &players[playerChoice - 1];
                cout << "\nPlayer dipilih: " << currentPlayer->nama << "\n";
                cout << "\nSelamat datang kembali, " << currentPlayer->nama << "!\n";
                displayPlayerStats(*currentPlayer);
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
            } else {
                cout << "\n[X] Pilihan tidak valid!\n";
                continue;
            }
        } else {
            cout << "\n[X] Pilihan tidak valid!\n";
            continue;
        }
        
        // Gameplay loop
        char playAgain;
        do {
            char board[3][3] = {
                {' ', ' ', ' '},
                {' ', ' ', ' '},
                {' ', ' ', ' '}
            };
            
            displayHeader();
            displayGuide();
            
            cout << "=== PILIH MODE PERMAINAN ===\n";
            cout << "1. VS Player\n";
            cout << "2. VS Komputer\n";
            cout << "\nPilihan Anda: ";
            
            int gameMode;
            cin >> gameMode;
            
            string result;
            if (gameMode == 1) {
                cout << "\nMode VS Player dipilih!\n";
                cout << "Player 1: X\n";
                cout << "Player 2: O\n";
                cout << "\nTekan Enter untuk memulai...";
                cin.ignore();
                cin.get();
                result = playVsPlayer(board);
            } else if (gameMode == 2) {
                result = playVsComputer(board);
            } else {
                cout << "\n[X] Pilihan tidak valid!\n";
                continue;
            }
            
            updatePlayerStats(*currentPlayer, result);
            displayMatchResult(*currentPlayer, result);
            savePlayersToFile(players);
            
            cout << "\nMain lagi? (y/n): ";
            cin >> playAgain;
            
        } while (playAgain == 'y' || playAgain == 'Y');
    }
    
    return 0;
}