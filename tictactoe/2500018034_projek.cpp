#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Gamer {
    string nama;
    int game;
    int menang;
    int imbang;
    int kalah;
    int skor;
};

vector<Gamer> players;
Gamer* currentPlayer = nullptr;
const string FILE_NAME = "players.txt";

void pause() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(1000, '\n');
    cin.get();
}

void header() {
    cout << "\n=============================\n";
    cout << "      TIC TAC TOE GAME\n";
    cout << "=============================\n\n";
}

void loadPlayers() {
    ifstream file(FILE_NAME.c_str());
    if (!file) {
        cout << "File player tidak ditemukan. Membuat file baru...\n\n";
        return;
    }

    Gamer p;
    while (file >> p.nama >> p.game >> p.menang >> p.imbang >> p.kalah >> p.skor) {
        players.push_back(p);
    }
    file.close();
}

void savePlayers() {
    ofstream file(FILE_NAME.c_str());
    for (size_t i = 0; i < players.size(); i++) {
        file << players[i].nama << " "
             << players[i].game << " "
             << players[i].menang << " "
             << players[i].imbang << " "
             << players[i].kalah << " "
             << players[i].skor << endl;
    }
    file.close();
}

void showStats(Gamer &p) {
    cout << "Statistik " << p.nama << ":\n";
    cout << "- Game: " << p.game << endl;
    cout << "- Menang: " << p.menang << endl;
    cout << "- Imbang: " << p.imbang << endl;
    cout << "- Kalah: " << p.kalah << endl;
    cout << "- Total Skor: " << p.skor << endl;
}

void newPlayer() {
    cout << "\n";

    cout << "=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";

    Gamer p;
    cin >> p.nama;
    p.game = p.menang = p.imbang = p.kalah = p.skor = 0;

    players.push_back(p);
    currentPlayer = &players[players.size() - 1];

    cout << "\nPlayer baru berhasil dibuat\n";
    cout << "Selamat datang, " << p.nama << "!\n\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

void choosePlayer() {
    header();
    cout << "=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           | Skor | Game | M  | I  | K\n";
    cout << "---|----------------|------|------|----|----|---\n";

    for (size_t i = 0; i < players.size(); i++) {
        cout << i + 1 << "  | " << players[i].nama;
        for (size_t s = players[i].nama.length(); s < 15; s++) cout << " ";
        cout << "| " << players[i].skor
             << "    |" << players[i].game
             << "     |" << players[i].menang
             << "   | " << players[i].imbang
             << "  | " << players[i].kalah << endl;
    }

    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    int c;
    cin >> c;
    if (c < 1 || c > static_cast<int>(players.size())) return;

    currentPlayer = &players[c - 1];
    cout << "\nPlayer dipilih:  " << currentPlayer->nama << "\n\n";
    cout << "Selamat datang kembali, " << currentPlayer->nama <<"!\n\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

void leaderboard() {
    header();
    vector<Gamer> temp = players;
    for (size_t i = 0; i < temp.size(); i++) {
        for (size_t j = i + 1; j < temp.size(); j++) {
            if (temp[j].skor > temp[i].skor) {
                Gamer t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Skor\n";
    cout << "================================\n\n";

    cout << "Rank | Nama           | Skor | Game | M  | I  | K\n";
    cout << "-----|----------------|------|------|----|----|----\n";

    for (size_t i = 0; i < temp.size() && i < 10; i++) {
        cout << " " << i + 1 << "   | " << temp[i].nama;
        for (size_t s = temp[i].nama.length(); s < 15; s++) cout << " ";
        cout << "| " << temp[i].skor
             << "    | " << temp[i].game
             << "    | " << temp[i].menang
             << "  | " << temp[i].imbang
             << "  | " << temp[i].kalah << endl;
    }
    pause();
}

bool checkWin(vector<char> &b, char m) {
    int w[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };
    for (int i = 0; i < 8; i++)
        if (b[w[i][0]] == m && b[w[i][1]] == m && b[w[i][2]] == m)
            return true;
    return false;
}

bool isboardFull(vector<char> &b) {
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ') return false;
    return true;
}

void displayGuide() {
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void displayBoard(vector<char> &b) {
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

void playVsComputer() {
    vector<char> board(9, ' ');
    header();
    displayGuide();
    displayBoard(board);

    while (true) {
        int pos;
        cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ') continue;

        board[pos - 1] = 'X';
        displayBoard(board);

        if (checkWin(board, 'X')) {
            cout << " ANDA MENANG! \n\n";
            cout << "==============================" <<endl;
            cout << "      HASIL PERTANDINGAN      " <<endl;
            cout << "==============================" <<endl;
            cout << "Hasil:  MENANG" << endl;
            cout << "Skor yang didapat: +3 poin\n\n";
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            currentPlayer->menang++;
            currentPlayer->skor += 3;
            break;
        }

        if (isboardFull(board)) {
            cout << "SERI! Tidak ada yang menang.\n\n";
            cout << "==============================" <<endl;
            cout << "      HASIL PERTANDINGAN      " <<endl;
            cout << "==============================" <<endl;
            cout << "Hasil: SERI" <<endl;
            cout << "Skor yang didapat: +1 poin\n\n";
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            currentPlayer->imbang++;
            currentPlayer->skor += 1;
            break;
        }

        cout << "Komputer sedang berpikir...\n";
        int c;
        for (c = 0; c < 9; c++)
            if (board[c] == ' ') break;

        cout << "Komputer memilih posisi: " << c + 1 << endl;
        board[c] = 'O';
        displayBoard(board);

        if (checkWin(board, 'O')) {
            cout << " KOMPUTER MENANG! \n\n";
            cout << "==============================" <<endl;
            cout << "      HASIL PERTANDINGAN      " <<endl;
            cout << "==============================" <<endl;
            cout << "Hasil:  KALAH" <<endl;
            cout << "Skor yang didapat: +0 poin\n\n" <<endl;
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            currentPlayer->kalah++;
            break;
        }
    }

    currentPlayer->game++;
    savePlayers();
}

void playVsPlayer() {
    vector<char> board(9, ' ');
    char current = 'X';
    
    header();
    displayGuide();
    displayBoard(board);

    while (true) {
        int pos;
        cout << "Giliran Player " << current << "\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ') continue;

        board[pos - 1] = current;
        displayBoard(board);

        if (checkWin(board, 'X')) {
            cout << " Player " << current << " MENANG! \n\n";
            cout << "==============================" <<endl;
            cout << "      HASIL PERTANDINGAN      " <<endl;
            cout << "==============================" <<endl;
            cout << "Hasil untuk " << currentPlayer->nama<< ": menang\n";
            cout << "Skor yang didapat: +3 poin\n\n";
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            
            if (current == 'X') currentPlayer->menang++;
            else currentPlayer->kalah++;
            currentPlayer->skor += 3;
            break;
        }
        
        if (checkWin(board, 'O')) {
            cout << " Player " << current << " MENANG! \n\n";
            cout << "==============================" <<endl;
            cout << "      HASIL PERTANDINGAN      " <<endl;
            cout << "==============================" <<endl;
            cout << "Hasil untuk " << currentPlayer->nama<< ": KALAH\n";
            cout << "Skor yang didapat: +0 poin\n\n" <<endl;
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
                        
            if (current == 'X') currentPlayer->menang++;
            else currentPlayer->kalah++;
            break;
        }

        if (isboardFull(board)) {
            cout << "SERI! Tidak ada yang menang.\n";
            currentPlayer->imbang++;
            currentPlayer->skor += 1;
            break;
        }

        current = (current == 'X') ? 'O' : 'X';
    }

    currentPlayer->game++;
    savePlayers();
}

void pilihModeGame() {
    char mainlagi;
    
    
    do {
        int choise;
        system("cls"); 
        
        header();
        cout << "\n=== PILIH MODE PERMAINAN ===\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n";
        cout << "Pilihan Anda: ";
        cin >> choise;
         
        fflush(stdin);
        
        if(choise == 1){
            playVsPlayer();
        }else if (choise == 2){
            playVsComputer();
        }
        
        cout << "Main lagi? (y/n): ";
        cin >> mainlagi;
        fflush(stdin);
        
        if(mainlagi == 'n'|| mainlagi == 'N'){
            cout <<"\nTerima kasih telah bermain, " << currentPlayer->nama << "!" <<endl;
            pause();
        }
        
    }while (mainlagi == 'y' || mainlagi == 'Y');
    
}

int main() {
    srand(time(0));
    loadPlayers();

    while (true) {
        header();
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Player Baru\n";
        cout << "2. Pilih Player yang Sudah Ada\n";
        cout << "3. Lihat Leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan Anda: ";
        
        
       
       

        int m;
        cin >> m;
        cin.ignore();

        if (m == 1) {
            newPlayer();
            if (currentPlayer) pilihModeGame();
        } else if (m == 2) {
            choosePlayer();
            if (currentPlayer) pilihModeGame();
        } else if (m == 3) {
            leaderboard();
        } else if (m == 4) {
            cout << "\nTerima kasih telah bermain Tic Tac Toe!\n";
            break;
        } else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}