// Naufal Azka Putra Amaludin
// NIM : 2500018043

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

const string PLAYERS_FILE = "players.txt";

const int POINT_WIN  = 3;
const int POINT_DRAW = 1;
const int POINT_LOSS = 0;

struct Player {
    string nama;
    int totalGames = 0;
    int totalWins = 0;
    int totalDraws = 0;
    int totalLosses = 0;
    int score = 0;
};

static inline string trim(const string &s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

bool parsePlayerLine(const string &line, Player &p) {
    // format: nama|totalGames|totalWins|totalDraws|totalLosses|score
    // nama can have spaces
    vector<string> tokens;
    stringstream ss(line);
    string token;
    while (getline(ss, token, '|')) {
        tokens.push_back(token);
    }
    if (tokens.size() != 6) return false;
    
    // all are strings
    try {
        p.totalGames = stoi(tokens[1]);
        p.totalWins = stoi(tokens[2]);
        p.totalDraws = stoi(tokens[3]);
        p.totalLosses = stoi(tokens[4]);
        p.score = stoi(tokens[5]);
    } catch (...) {
        return false;
    }
    
    // name is tokens[0]
    p.nama = tokens[0];
    
    return !p.nama.empty();
}

void loadPlayers(vector<Player> &players) {
    players.clear();
    ifstream fin(PLAYERS_FILE);
    if (!fin.is_open()) return; // belum ada file, aman

    string line;
    while (getline(fin, line)) {
        line = trim(line);
        if (line.empty()) continue;
        Player p{};
        if (parsePlayerLine(line, p)) {
            players.push_back(p);
        }
    }
    fin.close();
}

void savePlayers(const vector<Player> &players) {
    ofstream fout(PLAYERS_FILE);
    for (const auto &p : players) {
        fout << p.nama << "|"
             << p.totalGames << "|"
             << p.totalWins << "|"
             << p.totalDraws << "|"
             << p.totalLosses << "|"
             << p.score << "\n";
    }
    fout.close();
}

void clearScreen() {
    system("cls");
}

void enter() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.get();
}

void displayTicTacToeTitle() {
        cout << "================================" << endl;
        cout << "        TIC TAC TOE GAME        " << endl;
        cout << "================================" << endl;
}

void errorMessage() {
    cout << "===========================================" << endl;
    cout << "|   ⚠️⚠️⚠️       ERRORRRR!       ⚠️⚠️⚠️   |" << endl;
    cout << "| Pilihan tidak valid! Silakan coba lagi. |" << endl;
    cout << "===========================================" << endl;     
    enter();
}

void tambahPlayer(vector<Player>& players, const string& fileName = PLAYERS_FILE) {
    clearScreen();
    Player newPlayer;
    cout << "=== REGISTRASI PLAYER BARU ===" << endl;
    cout << "Masukkan nama anda: ";
    getline(cin, newPlayer.nama);
    players.push_back(newPlayer);
    cout << "\nPlayer baru berhasil dibuat!" << endl;
    cout << "Selamat datang, " << newPlayer.nama << endl;

    cout << "\nStatistik Anda:" << endl;
    cout << "- Total Games: " << newPlayer.totalGames << endl;
    cout << "- Wins: " << newPlayer.totalWins << endl;
    cout << "- Draws: " << newPlayer.totalDraws << endl;
    cout << "- Losses: " << newPlayer.totalLosses << endl;
    cout << "- Score: " << newPlayer.score << endl;
    ofstream dataPlayer(fileName, ios::app);
    if (dataPlayer.is_open()) {
        dataPlayer << newPlayer.nama << "|"
                   << newPlayer.totalGames << "|"
                   << newPlayer.totalWins << "|"
                   << newPlayer.totalDraws << "|"
                   << newPlayer.totalLosses << "|"
                   << newPlayer.score << endl;
        dataPlayer.close();
        cout << "Data player berhasil ditambahkan ke file " << fileName << endl;
    } else {
        cout << "Gagal membuka file " << fileName << endl;
    }
    enter();
}

int pilihPlayer(vector<Player>& players) {
    clearScreen();
    if (players.empty()) {
        cout << "Tidak Ada Data Player!\n" << endl;
        enter();
        return -1;
    }

    int namaPanjang = 0;
    
    for (const auto& player : players) {
        if ((int)player.nama.length() > namaPanjang) {
            namaPanjang = player.nama.length();
        }
    }

    cout << "====================== DAFTAR PLAYER =======================" << endl;
    cout << "No  | " << left << setw(namaPanjang + 10) << "Nama" << "| Score | Games |  W  |  D  |  L  " << endl;
    cout << "----|-";
    for (int i = 0; i < namaPanjang + 10; i++) cout << "-";
    cout << "|-------|-------|-----|-----|-----" << endl;
    for (size_t i = 0; i < players.size(); i++) {
        cout << left 
            << setw(4)  << i + 1 << "| "
            << setw(namaPanjang + 10) << players[i].nama << "| "
            << setw(6)  << players[i].score << "| "
            << setw(6)  << players[i].totalGames << "| "
            << setw(4)  << players[i].totalWins << "| "
            << setw(4)  << players[i].totalDraws << "| "
            << setw(4)  << players[i].totalLosses 
            << endl;
    }

    int playerTerpilih;
    string masukan;

    while (true) {
        cout << "\nPilih player "
            << (players.size() == 1 ? "(1)" : "(1-" + to_string(players.size()) + ")")
            << " atau 0 untuk kembali: ";
        getline(cin, masukan);

        try {
            playerTerpilih = stoi(masukan);

            if (playerTerpilih == 0) return -1;
            if (playerTerpilih >= 1 && playerTerpilih <= (int)players.size()) break;

            cout << "\nInput Tidak Valid!";
        }
        catch (invalid_argument& e) {
            cout << "\nInput Tidak Valid!";
        }
        catch (out_of_range& e) {
            cout << "\ninput Tidak Valid!";
        }
        cin.clear();
    }

    playerTerpilih -= 1;

    cout << "\nPlayer Dipilih: " << players[playerTerpilih].nama << endl;
    cout << "\nSelamat Datang Kembali, " << players[playerTerpilih].nama << "!" << endl;
    cout << "\nStatistik Anda:" << endl;
    cout << "- Total Games: " << players[playerTerpilih].totalGames << endl;
    cout << "- Wins: " << players[playerTerpilih].totalWins << endl;
    cout << "- Draws: " << players[playerTerpilih].totalDraws << endl;
    cout << "- Losses: " << players[playerTerpilih].totalLosses << endl;
    cout << "- Total Score: " << players[playerTerpilih].score << endl;

    cout << endl;
    enter();

    return playerTerpilih;
}

void lihatLeaderboard(vector<Player> playersCopy) {
    clearScreen();
    if (playersCopy.empty()) {
        cout << "\nLeaderboard kosong Belum ada player tersimpan.\n";
        enter();
        return;
    }

    for (size_t i = 0; i < playersCopy.size() - 1; ++i) {
        for (size_t j = 0; j < playersCopy.size() - i - 1; ++j) {
            if (playersCopy[j].score < playersCopy[j + 1].score) {
                swap(playersCopy[j], playersCopy[j + 1]);
            }
        }
    }

    size_t batasLoop = (playersCopy.size() < 10 ? playersCopy.size() : 10);

    size_t namaPanjang = 0;
    for (size_t i = 0; i < batasLoop; ++i) {
        if (playersCopy[i].nama.length() > namaPanjang) {
            namaPanjang = playersCopy[i].nama.length();
        }
    }

    cout << "===============================================================" << endl;
    cout << "                         LEADERBOARD      " << endl;
    cout << "                   Top 10 Players by Score" << endl;
    cout << "===============================================================" << endl;

    cout << "\n Rank|" << left << setw(namaPanjang + 10) << " Nama" << " | Score | Games |  W  |  D  |  L  |" << endl;
    cout << "-----|-";
    for (size_t i = 0; i < namaPanjang + 10; i++) cout << "-";
    cout << "|-------|-------|-----|-----|-----|" << endl;
    for (size_t i = 0; i < batasLoop; ++i) {
        cout << right << setw(3) << (i + 1) << "  ";
        cout << "| " << left << setw(namaPanjang + 10) << playersCopy[i].nama;
        cout << "| " << left << setw(6) << playersCopy[i].score;
        cout << "| " << left << setw(6) << playersCopy[i].totalGames;
        cout << "| " << left << setw(4) << playersCopy[i].totalWins;
        cout << "| " << left << setw(4) << playersCopy[i].totalDraws;
        cout << "| " << left << setw(4) << playersCopy[i].totalLosses;
        cout << "| " << left << setw(4);
        cout << endl;
    }
    cout << "\n===============================================================" << endl;

    cout << endl;
    enter();
}

/* =========================
   Update Statistik + Score
   ========================= */
void applyResult(Player &p, int win, int draw, int loss) {
    p.totalGames += (win + draw + loss);
    p.totalWins  += win;
    p.totalDraws += draw;
    p.totalLosses+= loss;
    p.score      += (win * POINT_WIN) + (draw * POINT_DRAW) + (loss * POINT_LOSS);
}

void displayPlayerStats(const Player &p) {
    cout << "\nStatistik " << p.nama << ":\n";
    cout << "- Total Games:  " << p.totalGames << "\n";
    cout << "- Wins: " << p.totalWins << "\n";
    cout << "- Draws: " << p.totalDraws << "\n";
    cout << "- Losses: " << p.totalLosses << "\n";
    cout << "- Total Score: " << p.score << "\n";
}

enum GameResult { PLAYER1_WIN, PLAYER2_WIN, DRAW };

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

void panduanPosisi() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

bool checkWin(char board[3][3], char player) {
    // Cek baris
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    
    // Cek kolom
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    }
    
    // Cek diagonal
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    
    return false;
}

// Fungsi untuk mengecek apakah board penuh (draw)
bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Fungsi untuk mengecek apakah posisi valid
bool isValidMove(char board[3][3], int position) {
    if (position < 1 || position > 9)
        return false;
    
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    
    return board[row][col] == ' ';
}

// Fungsi untuk menempatkan tanda pada board
void makeMove(char board[3][3], int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    board[row][col] = player;
}

// Fungsi untuk komputer memilih move (AI sederhana)
int computerMove(char board[3][3]) {
    // Cek apakah komputer bisa menang
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            // Copy board
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];
            
            makeMove(tempBoard, i, 'O');
            if (checkWin(tempBoard, 'O'))
                return i;
        }
    }
    
    // Cek apakah player bisa menang dan block
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            // Copy board
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];
            
            makeMove(tempBoard, i, 'X');
            if (checkWin(tempBoard, 'X'))
                return i;
        }
    }
    
    // Coba ambil tengah
    if (isValidMove(board, 5))
        return 5;
    
    // Coba ambil sudut
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        if (isValidMove(board, corners[i]))
            return corners[i];
    }
    
    // Ambil posisi kosong pertama
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i))
            return i;
    }
    
    return -1;
}

GameResult playVsPlayer(char board[3][3], string player1, string player2) {
    clearScreen();
    char currentPlayer = 'X';
    int position;
    string currentPlayerName;
    displayTicTacToeTitle();
    cout << endl;
    cout << player1 << " vs " << player2 << endl;
    panduanPosisi();
    
    while (true) {
        currentPlayerName = (currentPlayer == 'X') ? player1 : player2;

        displayBoard(board);
        cout << "Giliran " << currentPlayerName << " (" << currentPlayer << ")\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> position;
        
        if (!isValidMove(board, position)) {
            cout << "Posisi tidak valid! Coba lagi.\n";
            continue;
        }
        

        makeMove(board, position, currentPlayer);
        
        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "🎉 " << currentPlayerName << " (" << currentPlayer << ") MENANG! 🎉\n";
            return (currentPlayer == 'X') ? PLAYER1_WIN : PLAYER2_WIN;
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            return DRAW;
        }
        
        // Ganti pemain
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; 
    }

}

GameResult playVsComputer(char board[3][3]) {
    clearScreen();
    int position;
    displayTicTacToeTitle();
    panduanPosisi();

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
            cout << "🎉 ANDA MENANG! 🎉\n";
            return PLAYER1_WIN;
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            return DRAW;
        }
        
        // Giliran Komputer (O)
        cout << "Komputer sedang berpikir";
            flush(cout);
            for (int i = 0; i < 3; i++) {
                this_thread::sleep_for(chrono::seconds(1));
                cout << (i == 2 ? ".\n" : ".");
                flush(cout);
            }
        
        int compMove = computerMove(board);
        makeMove(board, compMove, 'O');
        cout << "Komputer memilih posisi: " << compMove << "\n";
        
        if (checkWin(board, 'O')) {
            displayBoard(board);
            cout << "💻 KOMPUTER MENANG! 💻\n";
            return PLAYER2_WIN;
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            return DRAW;
        }
    }
}

void pilihMode(vector<Player>& players, int playerTerpilih) {
    clearScreen();
    srand(time(0));
    
    char playAgain;
    string player1Name = players[playerTerpilih].nama;
    
    do {
        // Inisialisasi board 2D array
        char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
        
        displayTicTacToeTitle();
        
        int choice;
        cout << "Pilih mode permainan:\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n";
        cout << "3. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> choice;
        cin.ignore();
        
        if (choice == 1) {
            // VS Player - pilih player kedua
            clearScreen();
            int playerDua = pilihPlayer(players);
            
            if (playerDua == -1) {
                continue;
            }
            
            if (playerDua == playerTerpilih) {
                cout << "\n⚠️  Tidak boleh memilih player yang sama untuk lawan!\n";
                enter();
                continue;
            }
            
            string player2Name = players[playerDua].nama;
            GameResult res = playVsPlayer(board, player1Name, player2Name);
            
            // Update statistik kedua player
            if (res == PLAYER1_WIN) {
                applyResult(players[playerTerpilih], 1, 0, 0);
                applyResult(players[playerDua], 0, 0, 1);
            } else if (res == PLAYER2_WIN) {
                applyResult(players[playerTerpilih], 0, 0, 1);
                applyResult(players[playerDua], 1, 0, 0);
            } else {
                applyResult(players[playerTerpilih], 0, 1, 0);
                applyResult(players[playerDua], 0, 1, 0);
            }
            
            savePlayers(players);
            int point = (res == PLAYER1_WIN ? POINT_WIN : (res == PLAYER2_WIN ? POINT_WIN : POINT_DRAW));
            cout << endl;
            cout << "==================================" << endl;
            cout << "       HASIL PERTANDINGAN         " << endl;
            cout << "==================================" << endl;
            cout << "Hasil: " << (res == PLAYER1_WIN ? " MENANG!" : (res == PLAYER2_WIN ? " MENANG!" : "SERI!")) << endl;
            cout << "Score yang didapat: +" << point << " poin" << endl;
            displayPlayerStats(res == PLAYER1_WIN ? players[playerTerpilih] : players[playerDua]);
            cout << "\nData telah disimpan ke file players.txt" << endl;
        } else if (choice == 2) {
            // VS Komputer
            GameResult res = playVsComputer(board);
            
            // Update statistik player
            if (res == PLAYER1_WIN) {
                applyResult(players[playerTerpilih], 1, 0, 0);
            } else if (res == DRAW) {
                applyResult(players[playerTerpilih], 0, 1, 0);
            } else {
                applyResult(players[playerTerpilih], 0, 0, 1);
            }
            
            savePlayers(players);
            int point = (res == PLAYER1_WIN ? POINT_WIN : (res == DRAW ? POINT_DRAW : POINT_LOSS));
            cout << endl;
            cout << "==================================" << endl;
            cout << "       HASIL PERTANDINGAN         " << endl;
            cout << "==================================" << endl;
            cout << "Hasil: " << (res == PLAYER1_WIN ? " MENANG!" : (res == DRAW ? " SERI!" : " KALAH!")) << endl;
            cout << "Score yang didapat: +" << point << " poin" << endl;
            displayPlayerStats(players[playerTerpilih]);
            cout << "\nData telah disimpan ke file players.txt" << endl;
        } else if (choice == 3) {
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
            continue;
        }
        
        cout << "\nMain lagi? (y/n): ";
        cin.ignore();
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');
}        

void menuAwal() {
    vector<Player> players;
    loadPlayers(players);
    int pilihan;
    bool fileTerbaca = false;

    do {
        clearScreen();
        displayTicTacToeTitle();

        if (!fileTerbaca) {
            ifstream data(PLAYERS_FILE);

            if (!data.is_open()) {
                cout << "\nFile tidak ditemukan, membuat file baru..." << endl;
                ofstream dataBaru(PLAYERS_FILE);
                dataBaru.close();
            } else {
                cout << "\nFile ditemukan, data sudah dibaca..." << endl;
                data.close();
            }
            fileTerbaca = true;
        }

        cout << "\n===== MENU UTAMA =====" << endl;
        cout << "1. Tambah Player Baru" << endl;
        cout << "2. Pilih Player" << endl;
        cout << "3. Lihat Leaderboard" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 4) {
            cout << endl;
            cout << "Terima kasih telah bermain!" << endl;
            break;
        }

        switch (pilihan) {
            case 1:
                tambahPlayer(players);
                break;
            case 2: {
                int playerTerpilih = pilihPlayer(players);
                if (playerTerpilih != -1) {
                    pilihMode(players, playerTerpilih);
                }
                break;
            }
            case 3:
                lihatLeaderboard(players);
                break;
            default:
                errorMessage();
                break;
        }
    } while (pilihan != 4);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    menuAwal();
    return 0;
}