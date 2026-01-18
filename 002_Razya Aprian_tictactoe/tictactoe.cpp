#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <thread>
#include <chrono>
#include <windows.h>

using namespace std;

struct Player {
    string nama;
    int games = 0;
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int score = 0;
};

vector<Player> players;
int currentPlayer = -1;
int currentPlayer2 = -1;

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    clearInput();
    cin.get();
    system("cls");
}

void header() {
    cout << "================================\n";
    cout << "       TIC TAC TOE GAME\n";
    cout << "================================\n";
}

int inputPosisi() {
    int pos;
    while (true) {
        cin >> pos;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka 1-9: ";
            continue;
        }

        if (pos < 1 || pos > 9) {
            cout << "Posisi harus antara 1 sampai 9: ";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return pos;
    }
}

void loadPlayers() {
    ifstream file("playersp.txt");
    if (!file) {
        cout << "File player tidak ditemukan. Membuat file baru...\n\n";
        ofstream f("playersp.txt");
        f.close();
        return;
    }
	cout << "File player ditemukan, data sudah dibaca";
    Player p;
    string line;

    while (getline(file, line)) {
        if (line.find("NAMA") != string::npos)
            p.nama = line.substr(line.find(":") + 2);
        else if (line.find("GAMES") != string::npos)
            p.games = stoi(line.substr(line.find(":") + 2));
        else if (line.find("WINS") != string::npos)
            p.wins = stoi(line.substr(line.find(":") + 2));
        else if (line.find("DRAWS") != string::npos)
            p.draws = stoi(line.substr(line.find(":") + 2));
        else if (line.find("LOSSES") != string::npos)
            p.losses = stoi(line.substr(line.find(":") + 2));
        else if (line.find("SCORE") != string::npos) {
            p.score = stoi(line.substr(line.find(":") + 2));
            players.push_back(p);   
            p = Player();           
        }
    }

    file.close();
}


void savePlayers() {
    ofstream file("playersp.txt");
    for (auto &p : players) {
        file << "NAMA   : " << p.nama << "\n"
             << "GAMES  : " << p.games << "\n"
             << "WINS   : " << p.wins << "\n"
             << "DRAWS  : " << p.draws << "\n"
             << "LOSSES : " << p.losses << "\n"
             << "SCORE  : " << p.score << "\n"
             << "  \n";
    }
}

void menuUtama() {
	system("cls");
	int menu;
	bool fileIsChecked = false;
	header();
	if (!fileIsChecked) {
            ifstream file("playersp.txt");

            if (!file.is_open()) {
                cout << "\nFile tidak ditemukan, membuat file baru..." << endl;
                ofstream newFile("playersp.txt");
                newFile.close();
            } else {
                cout << "\nFile ditemukan, data sudah dibaca...\n" << endl;
                file.close();
            }

            fileIsChecked = true;
        }
    cout << "=== MENU UTAMA ===\n";
    cout << "1. Player Baru\n";
    cout << "2. Pilih Player yang Sudah Ada\n";
    cout << "3. Lihat Leaderboard\n";
    cout << "4. Keluar\n\n";
    cout << "Pilihan Anda: ";
    
    
}

void registerPlayer() {
    Player p;

    cout << "=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";
    cin >> p.nama;

    players.push_back(p);
    currentPlayer = players.size() - 1;
    savePlayers();

    cout << "\nPlayer baru berhasil dibuat!\n";
    cout << "Selamat datang, " << p.nama << "!\n\n";
    
    cout << "Statistik Anda:\n";
    cout << "- Total Games: 0\n";
    cout << "- Wins: 0\n";
    cout << "- Draws: 0\n";
    cout << "- Losses: 0\n";
    cout << "- Total Score: 0\n";

    pause();
    
}

void pilihPlayer() {
    header();
	
    cout << "=== DAFTAR PLAYER ===\n";
    cout << left
         << setw(4) << "No"
         << setw(16) << "Nama"
         << setw(8) << "Score"
         << setw(8) << "Games"
         << setw(4) << "W"
         << setw(4) << "D"
         << setw(4) << "L" << endl;

    cout << "-----------------------------------------\n";

    for (int i = 0; i < players.size(); i++) {
        cout << setw(4) << i + 1
             << setw(16) << players[i].nama
             << setw(8) << players[i].score
             << setw(8) << players[i].games
             << setw(4) << players[i].wins
             << setw(4) << players[i].draws
             << setw(4) << players[i].losses << endl;
    }

    int pilih;
    cout << "\nPilih player (0 untuk kembali): ";
    cin >> pilih;

    if (pilih > 0 && pilih <= players.size()) {
        currentPlayer = pilih - 1;

        cout << "\nPlayer dipilih:  " << players[currentPlayer].nama << "\n";
        cout << "\nSelamat datang kembali, " << players[currentPlayer].nama << "!\n\n";

        cout << "Statistik Anda:\n";
        cout << "- Total Games: " << players[currentPlayer].games << endl;
        cout << "- Wins: " << players[currentPlayer].wins << endl;
        cout << "- Draws: " << players[currentPlayer].draws << endl;
        cout << "- Losses: " << players[currentPlayer].losses << endl;
        cout << "- Total Score: " << players[currentPlayer].score << endl;
  
    } pause();
}

void pilihPlayerKedua() {
    header();
    while(true){
	
    cout << "=== PILIH PLAYER KE-2 ===\n";

    for (int i = 0; i < players.size(); i++) {
        if (i == currentPlayer) continue;
        cout << i + 1 << ". " << players[i].nama << endl;
    }
	
    int pilih;
    cout << "\nPilih player ke-2 (0 untuk batal): ";
    cin >> pilih;
	if (cin.fail()){
		clearInput();
		cout <<"Pilihan Tidak Valid";
		pause();
		continue;
	}
    if (pilih > 0 && pilih <= players.size() && pilih - 1 != currentPlayer) {
        currentPlayer2 = pilih - 1;
        cout << "Player ke-2: " << players[currentPlayer2].nama << endl;
    } else {
        cout << "Pilihan tidak valid!\n";
        currentPlayer2 = -1;
        pause();
        continue;
    } 
    pause();
    return;
	}
}

void leaderboard() {
	
    sort(players.begin(), players.end(),
        [](Player a, Player b) {
            return a.score > b.score;
        });

    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "================================\n\n";

    cout << left
         << setw(6) << "Rank  |"
         << setw(16) << " Nama   "
         << setw(8) << "|  Score  |"
         << setw(8) << "  Games  |"
         << setw(6) << "   W   |"
         << setw(6) << "   D   |"
         << setw(6) << "   L   |" << endl;

    cout << "------|----------------|---------|---------|-------|-------|-------|\n";

    for (int i = 0; i < players.size() && i < 10; i++) {
        cout << setw(6) << i + 1 
             << "|" <<setw(16) << players[i].nama
             << "| " <<setw(8) << players[i].score
             << "| "<<setw(8) << players[i].games
             << "| "<<setw(6) << players[i].wins
             << "| "<<setw(6) << players[i].draws
             << "| "<<setw(6) << players[i].losses << "|"<< endl;
		}
    cout << "\n================================\n";
    pause();
}

void guide() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void board(char b[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << b[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
}

bool win(char b[3][3], char p) {
    for (int i = 0; i < 3; i++)
        if ((b[i][0] == p && b[i][1] == p && b[i][2] == p) ||
            (b[0][i] == p && b[1][i] == p && b[2][i] == p))
            return true;

    return (b[0][0] == p && b[1][1] == p && b[2][2] == p) ||
           (b[0][2] == p && b[1][1] == p && b[2][0] == p);
}

bool full(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (b[i][j] == ' ')
                return false;
        }
    }
    return true;
}

int evaluate(char b[3][3]) {
    if (win(b, 'O')) return 10;
    if (win(b, 'X')) return -10;
    return 0;
}

int minimax(char b[3][3], bool isMax) {
    int score = evaluate(b);
    if (score == 10 || score == -10) return score;
    if (full(b)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            int r = i / 3, c = i % 3;
            if (b[r][c] == ' ') {
                b[r][c] = 'O';
                best = max(best, minimax(b, false));
                b[r][c] = ' ';
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            int r = i / 3, c = i % 3;
            if (b[r][c] == ' ') {
                b[r][c] = 'X';
                best = min(best, minimax(b, true));
                b[r][c] = ' ';
            }
        }
        return best;
    }
}
int bestMove(char b[3][3]) {
    int bestVal = -1000, move = -1;

    for (int i = 0; i < 9; i++) {
        int r = i / 3, c = i % 3;
        if (b[r][c] == ' ') {
            b[r][c] = 'O';
            int moveVal = minimax(b, false);
            b[r][c] = ' ';
            if (moveVal > bestVal) {
                bestVal = moveVal;
                move = i;
            }
        }
    }
    return move;
}

void vsComputer() {
    char b[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

    header();
    guide();

    while (true) {
        board(b);
        cout << "\nGiliran " << players[currentPlayer].nama << " (X)\n";
        cout << "Masukkan posisi (1-9): ";

        int pos = inputPosisi();

        if (pos < 1 || pos > 9) {
            cout << "Posisi Tidak Valid\n";
            continue;
        }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;

        if (b[r][c] != ' ') {
            cout << "Posisi Tidak Valid\n";
            continue;
        }

        b[r][c] = 'X';

        if (win(b, 'X')) {
            board(b);
            cout << "\n ANDA MENANG! \n";
            cout << "================================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << " Hasil: MENANG\n";
            cout << "Score yang didapat: +3 poin\n\n";

            players[currentPlayer].wins++;
            players[currentPlayer].score += 3;
            break;
        }

        if (full(b)) {
            board(b);
            cout << "\nSERI! Tidak ada yang menang.\n";
            cout << "================================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << " Hasil: SERI\n";
            cout << "Score yang didapat: +1 poin\n\n";

            players[currentPlayer].draws++;
            players[currentPlayer].score += 1;
            break;
        }

        cout << "\nKomputer sedang berpikir";
        cout.flush();
        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(400));
            cout << ".";
            cout.flush();
        }
        cout << endl;

        this_thread::sleep_for(chrono::milliseconds(500));

        int m = bestMove(b);
        b[m / 3][m % 3] = 'O';

        cout << "Komputer memilih posisi: " << m + 1 << endl;
		cout << endl;
        if (win(b, 'O')) {
            board(b);
            cout << "\n\nKomputer Menang\n";
            cout << "================================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Hasil:" << players[currentPlayer].nama << " Kalah\n";
            cout << "Score yang didapat: +0 poin\n\n";

            players[currentPlayer].losses++;
            break;
        }
    }

    cout << "Statistik Anda:\n";
    cout << "- Total Games: " << players[currentPlayer].games << endl;
    cout << "- Wins: " << players[currentPlayer].wins << endl;
    cout << "- Draws: " << players[currentPlayer].draws << endl;
    cout << "- Losses: " << players[currentPlayer].losses << endl;
    cout << "- Total Score: " << players[currentPlayer].score << endl;

    players[currentPlayer].games++;
    savePlayers();
    cout << "\nData telah disimpan ke file playersp.txt\n";
}

void vsPlayer2(int player2Index) {
    char b[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

    header();
    guide();

    int currentTurn = 0; 

    while (true) {
        board(b);

        int activePlayer = (currentTurn == 0) ? currentPlayer : player2Index;
        char symbol = (currentTurn == 0) ? 'X' : 'O';

        cout << "\nGiliran " << players[activePlayer].nama
             << " (" << symbol << ")\n";
        cout << "Masukkan posisi (1-9): ";

        int pos = inputPosisi();

        if (pos < 1 || pos > 9) {
            cout << "Posisi Tidak Valid\n";
            continue;
        }

        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;

        if (b[r][c] != ' ') {
            cout << "Posisi Tidak Valid\n";
            continue;
        }

        b[r][c] = symbol;

        if (win(b, symbol)) {
            board(b);
            cout << players[activePlayer].nama << " Menang\n\n";
            cout << "================================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << "Pemenang: " << players[activePlayer].nama << endl;
            cout << "Score yang didapat: +3 poin\n";

            players[activePlayer].wins++;
            players[activePlayer].score += 3;

            int loser = (activePlayer == currentPlayer) ? player2Index : currentPlayer;
            players[loser].losses++;
            break;
        }

        if (full(b)) {
            board(b);
            cout << "================================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "================================\n";
            cout << " Hasil: SERI\n";
            cout << "Score masing-masing: +1 poin\n";

            players[currentPlayer].draws++;
            players[player2Index].draws++;
            players[currentPlayer].score++;
            players[player2Index].score++;
            break;
        }

        currentTurn = 1 - currentTurn;
    }

    players[currentPlayer].games++;
    players[player2Index].games++;

    cout << "\nStatistik " << players[currentPlayer].nama << ":\n";
    cout << "- Games: " << players[currentPlayer].games << endl;
    cout << "- Wins: " << players[currentPlayer].wins << endl;
    cout << "- Draws: " << players[currentPlayer].draws << endl;
    cout << "- Losses: " << players[currentPlayer].losses << endl;
    cout << "- Score: " << players[currentPlayer].score << endl;

    cout << "\nStatistik " << players[player2Index].nama << ":\n";
    cout << "- Games: " << players[player2Index].games << endl;
    cout << "- Wins: " << players[player2Index].wins << endl;
    cout << "- Draws: " << players[player2Index].draws << endl;
    cout << "- Losses: " << players[player2Index].losses << endl;
    cout << "- Score: " << players[player2Index].score << endl;

    savePlayers();
    char lagi;
    cout << "\nData telah disimpan ke file playersp.txt\n";
    cout << "\nMain lagi? (y/n): ";
    cin >> lagi;
    pause();
}

int getCenterY(int contentHeight) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return (height - contentHeight) / 2;
}

void printTitleCenterScreen(string title[], int rows) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int startY = getCenterY(rows);

    for (int i = 0; i < startY; i++) cout << endl;

    for (int i = 0; i < rows; i++) {
        int padX = (width - title[i].length()) / 2;
        if (padX > 0) cout << string(padX, ' ');
        cout << title[i] << endl;
    }
}


int main() {
		string title[] = {
    "¦¦¦¦¦¦¦¦+¦¦+ ¦¦¦¦¦¦+    ¦¦¦¦¦¦¦¦+ ¦¦¦¦¦+  ¦¦¦¦¦¦+",
    "+--¦¦+--+¦¦¦¦¦+----+    +--¦¦+--+¦¦+--¦¦+¦¦+----+",
    "   ¦¦¦   ¦¦¦¦¦¦            ¦¦¦   ¦¦¦¦¦¦¦¦¦¦¦     ",
    "   ¦¦¦   ¦¦¦¦¦¦            ¦¦¦   ¦¦+--¦¦¦¦¦¦     ",
    "   ¦¦¦   ¦¦¦+¦¦¦¦¦¦+       ¦¦¦   ¦¦¦  ¦¦¦+¦¦¦¦¦¦+",
    "   +-+   +-+ +-----+       +-+   +-+  +-+ +-----+",
    "           T I C   T A C   T O E"
};

		for (int p = 0; p <= 100; p += 5) {
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printTitleCenterScreen(title, 7);

    cout << "\n\n";
    int padX = 25;
    cout << string(padX, ' ') << "Memuat Pertandingan...\n\n";
    cout << string(padX, ' ') << "[";

    int bars = p / 2;
    for (int i = 0; i < bars; i++) cout << "¦";
    for (int i = bars; i < 50; i++) cout << " ";
    cout << "] " << p << "%";

    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
    loadPlayers();
    int menu;
    
    
    do {
        header();
        menuUtama();
		cin >> menu;

        if (cin.fail()){
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(),'\n');
        	cout<<"Input tidak valid\n\n";
        	pause();
        	continue;
		}
         

        if (menu == 1) {
        	registerPlayer();
		
        }else if (menu == 2) {
        	pilihPlayer();
		}
        else if (menu == 3) {
        	leaderboard();
		}
        else if (menu == 4) {
            cout << "\nTerima kasih telah bermain!\n";
            break;
        }

        if (currentPlayer != -1 && menu != 3) {
            int mode;
            cout << "\n=== PILIH MODE PERMAINAN ===\n";
            cout << "1. VS Player\n";
            cout << "2. VS Komputer\n";
            cout << "3. Kembali Ke Menu Utama\n";
            cout << "Pilihan Anda: ";
            cin >> mode;

            if (mode == 1) {
    			pilihPlayerKedua();
    			
    		if (currentPlayer2 != -1) {
        		vsPlayer2(currentPlayer2);
    			}
			}
			else if (mode == 2) {
    			char lagi;
    			do {
        			vsComputer();
        				cout << "\nMain lagi? (y/n): ";
        				cin >> lagi;
    			} while (lagi == 'y');
			}
			else if (mode == 3) {
		    continue;
			}

        }

    } while (true);

    return 0;
}

