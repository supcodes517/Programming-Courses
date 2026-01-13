#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
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
            p = Player(); // RESET object untuk player berikutnya
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

int selectExistingPlayer(const string& prompt) {
    if (players.empty()) {
        cout << "Belum ada player.\n"; 
        pause(); 
        return -1;
    }

    cout << "\n" << prompt << "\n";

    // Tampilkan daftar player
    cout << "No | Nama           | Score | Games | W  | D  | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";
    for (int i = 0; i < (int)players.size(); i++) {
        Player &p = players[i];
        cout << left
             << setw(3) << i + 1
             << "| " << setw(15) << p.nama
             << "| " << setw(6) << p.score
             << "| " << setw(6) << p.totalGames
             << "| " << setw(3) << p.totalWins
             << "| " << setw(3) << p.totalDraws
             << "| " << setw(3) << p.totalLosses
             << "\n";
    }

    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    int pick; cin >> pick;

    if (pick == 0) return -1;
    if (pick < 1 || pick > (int)players.size()) {
        cout << "Pilihan tidak valid!\n"; 
        pause(); 
        return -1;
    }

    int idx = pick - 1;

    // Tampilkan statistik player yang dipilih
    Player &selected = players[idx];
    cout << "\nPlayer dipilih: " << selected.nama << "\n";
    cout << "Selamat datang kembali, " << selected.nama << "!\n\n";
    cout << "Statistik Anda:\n";
    cout << "- Total Games: " << selected.totalGames << "\n";
    cout << "- Wins: " << selected.totalWins << "\n";
    cout << "- Draws: " << selected.totalDraws << "\n";
    cout << "- Losses: " << selected.totalLosses << "\n";
    cout << "- Total Score: " << selected.score << "\n\n";
    pause();

    return idx;
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
        cout << "Giliran " << currentPlayer << " (" << (turnX ? "X" : "O") << ") Masukkan posisi (1-9): ";
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
            cout << "🎉 ANDA MENANG! 🎉\n";
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
            cout << "🎉 ANDA MENANG! 🎉\n";
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



void computerMove() {
    int r, c;
    do { r = rand() % 3; c = rand() % 3; } while (board[r][c] == 'X' || board[r][c] == 'O');
    board[r][c] = 'O';
    cout << "Komputer memilih posisi: " << (r * 3 + c + 1) << endl;
}


void playVsComputer(int idxPlayer) {
    system("cls");
    cout << "======================================\n";
    cout << "            TIC TAC TOE GAME          \n";
    cout << "======================================\n";
    resetBoard();
    printGuide();
    printBoard();

    while (true) {
        int pos;
        cout << "Giliran Anda (X) : "; cin >> pos;
        if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (pos < 1 || pos > 9 || board[r][c] == 'X' || board[r][c] == 'O') { cout << "Posisi tidak valid!\n"; continue; }

        board[r][c] = 'X'; printBoard();
        if (checkWin('X')) {
            cout << "🎉 ANDA MENANG! 🎉\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : MENANG" << endl;
            cout << "Score Yang Di Dapatkan : +3 Poin"<< endl;
            players[idxPlayer].totalGames++; players[idxPlayer].totalWins++; players[idxPlayer].score += 3;
            savePlayers(); showStats(players[idxPlayer]); pause(); return;
        }
        if (isDraw()) {
            cout << "SERI!\n"; 
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : SERI" << endl;
            cout << "Score Yang Di Dapatkan : +1 Poin"<< endl;
            players[idxPlayer].totalGames++; players[idxPlayer].totalDraws++; players[idxPlayer].score++; savePlayers(); showStats(players[idxPlayer]); pause(); return;
        }

        computerMove(); printBoard();
        if (checkWin('O')) {
            cout << "💻 KOMPUTER MENANG! 💻\n";
            cout << "======================================\n";
            cout << "          HASIL PERTANDINGAN          \n";
            cout << "======================================\n";
            cout << "Hasil : KALAH" << endl;
            cout << "Score Yang Di Dapatkan : +0 Poin"<< endl;
            players[idxPlayer].totalGames++; players[idxPlayer].totalLosses++; savePlayers(); showStats(players[idxPlayer]); pause(); return;
        }
    }
}


void leaderboard() {
    cout << "\n================================";
    cout << "\n        LEADERBOARD";
    cout << "\n  Top 10 Players by Score";
    cout << "\n================================\n\n";

    sort(players.begin(), players.end(), [](Player &a, Player &b){
        return a.score > b.score;
    });

    cout << "Rank | Nama           | Score | Games | W  | D  | L\n";
    cout << "-----|----------------|-------|-------|----|----|----\n";

    int limit = min(10, (int)players.size());
    for (int i = 0; i < limit; i++) {
        Player &p = players[i];
        cout << "  " << i+1
             << "  | " << p.nama
             << string(15 - p.nama.length(), ' ')
             << "|  " << p.score
             << "    |  " << p.totalGames
             << "    | " << p.totalWins
             << "  | " << p.totalDraws
             << "  | " << p.totalLosses
             << "\n";
    }
    cout << "\n================================\n";
    cout << "Tekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
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
    cout << "\n=== REGISTRASI PLAYER BARU ===\n";
    Player p; 
    cout << "Masukkan nama Anda: "; cin >> p.nama;
    players.push_back(p);
    currentPlayerIndex = players.size() - 1;

    cout << "\nPlayer baru berhasil dibuat! \n";
    cout << "Selamat datang, " << p.nama << "!\n";
    showStats(players[currentPlayerIndex]); pause();

    // Langsung pilih mode setelah registrasi
    int choice2;
    while (true) {
        system("cls");
        cout << "===== PILIH MODE =====\n";
        cout << "1. Player vs Player\n";
        cout << "2. Player vs Computer\n";
        cout << "3. Kembali ke Menu Utama\n";
        cout << "Pilihan Anda : "; cin >> choice2;

        if (choice2 == 1) {
            int idx2 = selectExistingPlayer("=== Pilih Player 2 ===");
            if (idx2 == -1 || idx2 == currentPlayerIndex) { 
                cout << "Player tidak valid!\n"; pause(); continue; 
            }
            playVsPlayer(currentPlayerIndex, idx2); 
            break;
        } else if (choice2 == 2) {
            playVsComputer(currentPlayerIndex); 
            break;
        } else if (choice2 == 3) break;
        else { cout << "Pilihan Tidak Valid!\n"; pause(); }
    }

    break;
}

case 2: {
    int idx1 = selectExistingPlayer("=== Pilih Player 1 ===");
    if (idx1 == -1) break;

    int choice2;
    while (true) {
        system("cls");
        cout << "===== PILIH MODE =====\n";
        cout << "1. Player1 Vs Player2\n";
        cout << "2. Player1 Vs Computer\n";
        cout << "3. Back To Menu\n";
        cout << "Pilihan Anda : ";cin >> choice2;
        if (choice2 == 1) {
            int idx2 = selectExistingPlayer("=== Pilih Player 2 ===");
            if (idx2 == -1 || idx2 == idx1) { cout << "Player tidak valid!\n"; pause(); continue; }
            playVsPlayer(idx1, idx2);
            break;
        } else if (choice2 == 2) {
            playVsComputer(idx1);
            break;
        } else if (choice2 == 3) {
            break;
        } else {
            cout << "Pilihan Tidak Valid!\n";
        }
    }
    break;
}
            case 3: leaderboard(); break;
            case 4: cout << "Terima kasih telah bermain!\n"; return;
            default: cout << "Pilihan tidak valid!\n"; pause(); break;
        }
    }
}

int main() {
    srand(time(0));
    players = loadPlayers();
    menu();
    return 0;
}