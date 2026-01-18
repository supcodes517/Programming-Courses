#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

const string FILENAME = "players.txt";

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

void printHeader() {
    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

void pressEnter() {
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(1000, '\n'); 
    cin.get();
    cout << "\n";
}

vector<Player> loadPlayers() {
    vector<Player> players;
    ifstream file(FILENAME.c_str());

    if (!file.is_open()) {
        cout << "File player tidak ditemukan.  Membuat file baru...\n\n";
        ofstream newFile(FILENAME.c_str());
        newFile.close();
        return players;
    }

    Player p;
    while (file >> p.nama >> p.totalGames >> p.totalWins
                >> p.totalDraws >> p.totalLosses >> p.score) {
        players.push_back(p);
    }
    file.close();
    return players;
}

void savePlayers(vector<Player> players) {
    ofstream file(FILENAME.c_str());
    for (int i = 0; i < players.size(); i++) {
        file << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }
    file.close();
    cout << "\nData telah disimpan ke file players.txt\n";
}

void displayGuide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void displayBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---|---|---\n";
    }
    cout << endl;
}

bool checkWin(char board[3][3], char p) {
    for (int i = 0; i < 3; i++)
        if (board[i][0] == p && board[i][1] == p && board[i][2] == p)
            return true;

    for (int j = 0; j < 3; j++)
        if (board[0][j] == p && board[1][j] == p && board[2][j] == p)
            return true;

    if (board[0][0] == p && board[1][1] == p && board[2][2] == p)
        return true;

    if (board[0][2] == p && board[1][1] == p && board[2][0] == p)
        return true;

    return false;
}

bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

int playVsComputer(char board[3][3]) {
    displayGuide();
    displayBoard(board);

    while (true) {
        int pos;
        cout << "Giliran Anda (X)\n";
        cout << "Masukkan posisi (1-9): ";
        if (!(cin >> pos)) {
   		cin.clear();               
   		cin.ignore(1000, '\n');     
    	cout << "Input tidak valid! Masukkan angka 1-9.\n";
    	continue;
		}

		if (pos < 1 || pos > 9) {
		    cout << "Posisi harus antara 1 sampai 9!\n";
		    continue;
		}


        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (board[r][c] != ' ') continue;

        board[r][c] = 'X';
        displayBoard(board);

        if (checkWin(board, 'X')) {
            cout << "?? ANDA MENANG! ??\n";
            return 1;
        }

        if (isBoardFull(board)) {
            cout << "SERI! Tidak ada yang menang.\n";
            return 0;
        }

        cout << "\nKomputer sedang berpikir...\n";

        int comp;
        do {
            comp = rand() % 9 + 1;
            r = (comp - 1) / 3;
            c = (comp - 1) % 3;
        } while (board[r][c] != ' ');

        cout << "Komputer memilih posisi: " << comp << "\n\n";
        board[r][c] = 'O';
        displayBoard(board);

        if (checkWin(board, 'O')) {
            cout << "?? KOMPUTER MENANG! ??\n";
            return -1;
        }
    }
}

void playVsPlayer(char board[3][3]) {
    displayGuide();
    displayBoard(board);

    char turn = 'X';

    while (true) {
    int pos;
    cout << "Giliran Player " << turn << endl;
    cout << "Masukkan posisi (1-9): ";

    if (!(cin >> pos)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Input tidak valid! Masukkan angka 1-9.\n";
        continue;
    }

    if (pos < 1 || pos > 9) {
        cout << "Posisi harus antara 1 sampai 9!\n";
        continue;
    }

    int r = (pos - 1) / 3;
    int c = (pos - 1) % 3;

    if (board[r][c] != ' ') {
        cout << "Posisi sudah terisi!\n";
        continue;
    }

    board[r][c] = turn;
    displayBoard(board);

    if (checkWin(board, turn)) {
        cout << "?? Player " << turn << " MENANG! ??\n";
        break;
    }

    if (isBoardFull(board)) {
        cout << "SERI! Tidak ada yang menang.\n";
        break;
    }

    turn = (turn == 'X') ? 'O' : 'X';
	}
}

void printResultVSPlayer(string nama) {
    cout << "\n================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";
    cout << "Hasil untuk " << nama << ": MENANG\n";
    cout << "Score yang didapat: +3 poin\n\n";
}

void printResultVSComputer(string hasil, int poin) {
    cout << "\n================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";
    cout << "Hasil: " << hasil << endl;
    cout << "Score yang didapat: +" << poin << " poin\n\n";
}

void printStats(Player p) {
    cout << "Statistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.totalGames << endl;
    cout << "- Wins: " << p.totalWins << endl;
    cout << "- Draws: " << p.totalDraws << endl;
    cout << "- Losses: " << p.totalLosses << endl;
    cout << "- Total Score: " << p.score << endl << endl;
}

void showLeaderboard(vector<Player> players) {
    printHeader();
    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";

    for (int i = 0; i < players.size(); i++) {
        for (int j = i + 1; j < players.size(); j++) {
            if (players[j].score > players[i].score) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    cout << "Rank | Nama           | Score | Games | W  | D  | L  |\n";
    cout << "-----|----------------|-------|-------|----|----|----|\n";

    for (int i = 0; i < players.size() && i < 10; i++) {
        cout << setw(4) << i + 1 << " | "
             << setw(14) << players[i].nama << " | "
             << setw(5) << players[i].score << " | "
             << setw(5) << players[i].totalGames << " | "
             << setw(2) << players[i].totalWins << " | "
             << setw(2) << players[i].totalDraws << " | "
             << setw(2) << players[i].totalLosses << " |\n";
    }

    cout << "\n================================\n\n";
    pressEnter();
}

int main() {
    srand(time(0));
    vector<Player> players = loadPlayers();
    int currentPlayer = -1;

    while (true) {
        printHeader();
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan Anda: ";

        int menu;
        cin >> menu;

        if (menu == 1) {
            Player p;
            cout << "\n=== REGISTRASI PLAYER BARU ===\n";
            cout << "Masukkan nama Anda: ";
            cin >> p.nama;

            p.totalGames = 0;
            p.totalWins = 0;
            p.totalDraws = 0;
            p.totalLosses = 0;
            p.score = 0;

            players.push_back(p);
            currentPlayer = players.size() - 1;

            cout << "\nPlayer baru berhasil dibuat!\n";
            cout << "Selamat datang, " << p.nama << "!\n\n";
            printStats(p);
            pressEnter();
        }
        else if (menu == 2) {
            if (players.size() == 0) continue;

            cout << "\n=== DAFTAR PLAYER ===\n";
            cout << "No | Nama           | Score | Games | W  | D  | L\n";
            cout << "---|----------------|-------|-------|----|----|---\n";

            for (int i = 0; i < players.size(); i++) {
                cout << setw(2) << i + 1 << " | "
                     << setw(14) << players[i].nama << " | "
                     << setw(5) << players[i].score << " | "
                     << setw(5) << players[i].totalGames << " | "
                     << setw(2) << players[i].totalWins << " | "
                     << setw(2) << players[i].totalDraws << " | "
                     << setw(2) << players[i].totalLosses << endl;
            }

            int pilih;
            cout << "\nPilih player (1-" << players.size()
                 << ") atau 0 untuk kembali: ";
            cin >> pilih;

            if (pilih < 1 || pilih > players.size()) continue;
            currentPlayer = pilih - 1;

            cout << "\nPlayer dipilih:  " << players[currentPlayer].nama << "\n\n";
            cout << "Selamat datang kembali, "
                 << players[currentPlayer].nama << "!\n\n";
            printStats(players[currentPlayer]);
            pressEnter();
        }
        else if (menu == 3) {
            showLeaderboard(players);
            continue;
        }
        else if (menu == 4) {
            savePlayers(players);
            cout << "\nTerima kasih telah bermain!\n";
            break;
        }
        else {
            continue;
        }

        cout << "=== PILIH MODE PERMAINAN ===\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n\n";
        cout << "Pilihan Anda: ";

        int mode;
        cin >> mode;
        while (mode != 1 && mode != 2) {
            cout << "Pilihan tidak valid. Masukkan 1 atau 2: ";
            cin >> mode;
        }

        char lagi;
        do {
            if (mode == 1) {
                cout << "\nMode VS Player dipilih!\n";
                cout << "Player 1: X\n";
                cout << "Player 2: O\n\n";
                pressEnter();

                printHeader();
                char board[3][3] = {
                    {' ',' ',' '},
                    {' ',' ',' '},
                    {' ',' ',' '}
                };

                playVsPlayer(board);

                players[currentPlayer].totalGames++;
                players[currentPlayer].totalWins++;
                players[currentPlayer].score += 3;

                printResultVSPlayer(players[currentPlayer].nama);
                printStats(players[currentPlayer]);
                savePlayers(players);
            }
            else {
                printHeader();
                char board[3][3] = {
                    {' ',' ',' '},
                    {' ',' ',' '},
                    {' ',' ',' '}
                };

                int hasil = playVsComputer(board);

                players[currentPlayer].totalGames++;

                if (hasil == 1) {
                    players[currentPlayer].totalWins++;
                    players[currentPlayer].score += 3;
                    printResultVSComputer(" MENANG", 3);
                }
                else if (hasil == 0) {
                    players[currentPlayer].totalDraws++;
                    players[currentPlayer].score += 1;
                    printResultVSComputer(" SERI", 1);
                }
                else {
                    players[currentPlayer].totalLosses++;
                    printResultVSComputer(" KALAH", 0);
                }

                printStats(players[currentPlayer]);
                savePlayers(players);
            }

            cout << "\nMain lagi? (y/n): ";
            cin >> lagi;

        } while (lagi == 'y' || lagi == 'Y');
    }

    return 0;
}

