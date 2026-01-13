#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

//struct player
struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

// Global variables
vector<Player> players;
int currentPlayerIndex = -1;

// ---------- file management ----------
void loadPlayers() {
    ifstream fin("players.txt");
    if(!fin) {
        cout << "\nFile player tidak ditemukan. Membuat file baru...\n";
        ofstream fout("players.txt"); fout.close();
        return;
    }
    Player p;
    while(fin >> p.nama >> p.score >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses){
        players.push_back(p);
    }
    fin.close();
}

void savePlayers() {
    ofstream fout("players.txt");
    for(auto &p : players){
        fout << p.nama << " " << p.score << " " << p.totalGames << " "
             << p.totalWins << " " << p.totalDraws << " " << p.totalLosses << "\n";
    }
    fout.close();
}

// ---------- tampilan ----------
void displayGuide() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void displayBoard(char board[3][3]) {
    cout << "\n";
    for(int i=0;i<3;i++){
        cout << " ";
        for(int j=0;j<3;j++){
            cout << " " << board[i][j];
            if(j<2) cout << " |";
        }
        cout << "\n";
        if(i<2) cout << " ---|---|---\n";
    }
    cout << "\n";
}

// ---------- kegunaan ----------
bool isBoardFull(char board[3][3]){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j]==' ') return false;
    return true;
}

bool checkWin(char board[3][3], char player){
    for(int i=0;i<3;i++) if(board[i][0]==player && board[i][1]==player && board[i][2]==player) return true;
    for(int j=0;j<3;j++) if(board[0][j]==player && board[1][j]==player && board[2][j]==player) return true;
    if(board[0][0]==player && board[1][1]==player && board[2][2]==player) return true;
    if(board[0][2]==player && board[1][1]==player && board[2][0]==player) return true;
    return false;
}

bool isValidMove(char board[3][3], int pos){
    if(pos<1 || pos>9) return false;
    int r=(pos-1)/3, c=(pos-1)%3;
    return board[r][c]==' ';
}

void makeMove(char board[3][3], int pos, char player){
    int r=(pos-1)/3, c=(pos-1)%3;
    board[r][c]=player;
}

// ---------- computer ----------
int computerMove(char board[3][3]){
    // Cek menang
    for(int i=1;i<=9;i++){
        if(isValidMove(board,i)){
            char temp[3][3]; for(int x=0;x<3;x++) for(int y=0;y<3;y++) temp[x][y]=board[x][y];
            makeMove(temp,i,'O');
            if(checkWin(temp,'O')) return i;
        }
    }
    // cek player
    for(int i=1;i<=9;i++){
        if(isValidMove(board,i)){
            char temp[3][3]; for(int x=0;x<3;x++) for(int y=0;y<3;y++) temp[x][y]=board[x][y];
            makeMove(temp,i,'X');
            if(checkWin(temp,'X')) return i;
        }
    }
    if(isValidMove(board,5)) return 5;
    int corners[]={1,3,7,9};
    for(int i=0;i<4;i++) if(isValidMove(board,corners[i])) return corners[i];
    for(int i=1;i<=9;i++) if(isValidMove(board,i)) return i;
    return -1;
}

// ---------- gameplay ----------
void playVsComputer() {
    system("clear"); // gunakan "cls" untuk Windows
    if(currentPlayerIndex==-1){ 
        cout << "\nSilakan pilih player terlebih dahulu.\n"; 
        return;
    }
    char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    displayGuide();
    int result;
    int turnCount=0;
    bool shownEllipsis=false;

    while(true){
        displayBoard(board);
        int pos;
        cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
        cin >> pos;
        if(!isValidMove(board,pos)){ cout << "Posisi tidak valid! Coba lagi.\n"; continue;}
        makeMove(board,pos,'X');

        if(checkWin(board,'X')){ result=1; break;}
        if(isBoardFull(board)){ result=0; break;}

        cout << "\nKomputer sedang berpikir...\n";
        int comp=computerMove(board);
        makeMove(board,comp,'O');
        cout << "Komputer memilih posisi: " << comp << "\n\n";

        turnCount++;
        if(turnCount==2 && !shownEllipsis){
            cout << "[...  gameplay berlanjut ...]\n\n";
            shownEllipsis=true;
        }

        if(checkWin(board,'O')){ result=-1; break;}
        if(isBoardFull(board)){ result=0; break;}
    }

    displayBoard(board);
    cout << "================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";

    Player &p = players[currentPlayerIndex];
    if(result==1){
        cout << "Hasil untuk " << p.nama << ": MENANG\nScore yang didapat: +3 poin\n";
        p.totalWins++; p.score+=3;
    } else if(result==0){
        cout << "Hasil untuk " << p.nama << ": SERI\nScore yang didapat: +1 poin\n";
        p.totalDraws++; p.score+=1;
    } else{
        cout << "Hasil untuk " << p.nama << ": KALAH\nScore yang didapat: +0 poin\n";
        p.totalLosses++;
    }
    p.totalGames++;

    cout << "\nStatistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.totalGames << "\n";
    cout << "- Wins: " << p.totalWins << "\n";
    cout << "- Draws: " << p.totalDraws << "\n";
    cout << "- Losses: " << p.totalLosses << "\n";
    cout << "- Total Score: " << p.score << "\n\n";

    savePlayers();
    cout << "Data telah disimpan ke file players.txt\n";
    cout << "mau main lagi? (y/n): ";
    char again; cin >> again;
    system("clear");
}

// versus player
void playVsPlayer() {
    system("clear"); 
    if(currentPlayerIndex==-1){ 
        cout << "\nSilakan pilih player terlebih dahulu.\n"; 
        return;
    }
    char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    displayGuide();
    int turnCount=0;
    bool shownEllipsis=false;
    char currentPlayer='X';
    int result;

    cout << "Mode VS Player dipilih!\nPlayer 1: X\nPlayer 2: O\n\n";
    cout << "Tekan Enter untuk memulai..."; cin.ignore(); cin.get();
    

    while(true){
        displayBoard(board);
        int pos;
        cout << "Giliran Player " << currentPlayer << "\nMasukkan posisi (1-9): ";
        cin >> pos;
        if(!isValidMove(board,pos)){ cout << "Posisi tidak valid! Coba lagi.\n"; continue;}
        makeMove(board,pos,currentPlayer);

        if(checkWin(board,currentPlayer)){ result= (currentPlayer=='X')?1:-1; break;}
        if(isBoardFull(board)){ result=0; break;}

        currentPlayer = (currentPlayer=='X')?'O':'X';

        turnCount++;
        if(turnCount==2 && !shownEllipsis){
            cout << "[...  gameplay berlanjut ...]\n\n";
            shownEllipsis=true;
        }
    }

    displayBoard(board);
    cout << "✨ Player " << currentPlayer << " MENANG! ✨\n";

    cout << "================================\n";
    cout << "       HASIL PERTANDINGAN\n";
    cout << "================================\n";

    Player &p = players[currentPlayerIndex];
    if(result==1){
        cout << "Hasil untuk " << p.nama << ": MENANG\nScore yang didapat: +3 poin\n";
        p.totalWins++; p.score+=3;
    } else if(result==0){
        cout << "Hasil untuk " << p.nama << ": SERI\nScore yang didapat: +1 poin\n";
        p.totalDraws++; p.score+=1;
    } else{
        cout << "Hasil untuk " << p.nama << ": KALAH\nScore yang didapat: +0 poin\n";
        p.totalLosses++;
    }
    p.totalGames++;

    cout << "\nStatistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.totalGames << "\n";
    cout << "- Wins: " << p.totalWins << "\n";
    cout << "- Draws: " << p.totalDraws << "\n";
    cout << "- Losses: " << p.totalLosses << "\n";
    cout << "- Total Score: " << p.score << "\n\n";

    savePlayers();
    cout << "Data telah disimpan ke file players.txt\n";
    cout << "mau main lagi? (y/n): ";
    char again; cin >> again;
    system("clear");
}

// ---------- menu ----------
void showMainMenu() {
    cout << "=== MENU UTAMA ===\n";
    cout << "1. Player Baru\n";
    cout << "2. Pilih Player yang Sudah Ada\n";
    cout << "3. Lihat Leaderboard\n";
    cout << "4. Keluar\n\n";
    cout << "Pilihan Anda: ";
}

void menuPlayerBaru(){
    Player p;
    cout << "\n=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";
    cin >> p.nama;
    p.totalGames=p.totalWins=p.totalDraws=p.totalLosses=p.score=0;
    players.push_back(p);
    currentPlayerIndex = players.size()-1;

    cout << "\nPlayer baru berhasil dibuat! \nSelamat datang, " << p.nama << "!\n";
    cout << "\nStatistik Anda:\n- Total Games: 0\n- Wins: 0\n- Draws: 0\n- Losses: 0\n- Total Score: 0\n";
    savePlayers();
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();
    system("clear");
}

void menuPilihPlayer(){
    if(players.empty()){ 
        cout << "\nBelum ada player. Silakan buat player baru.\n"; 
        return;
    }

    cout << "\n=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           | Score | Games | W  | D  | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";

    for(int i=0;i<players.size();i++){
        printf("%-2d | %-14s | %-5d | %-5d | %-2d | %-2d | %-2d\n",
               i+1,
               players[i].nama.c_str(),
               players[i].score,
               players[i].totalGames,
               players[i].totalWins,
               players[i].totalDraws,
               players[i].totalLosses);
    }

    int pilih;
    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    cin >> pilih;

    if(pilih==0) return;
    if(pilih<1 || pilih>players.size()){ cout << "Pilihan tidak valid.\n"; return; }

    currentPlayerIndex = pilih-1;
    Player &p = players[currentPlayerIndex];
    cout << "\nPlayer dipilih: " << p.nama << "\n\n";
    cout << "Selamat datang kembali, " << p.nama << "! \n\n";
    cout << "Statistik Anda:\n";
    cout << "- Total Games: " << p.totalGames << "\n";
    cout << "- Wins: " << p.totalWins << "\n";
    cout << "- Draws: " << p.totalDraws << "\n";
    cout << "- Losses: " << p.totalLosses << "\n";
    cout << "- Total Score: " << p.score << "\n\n";
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(); cin.get();

    // Pilih mode 
    int mode;
    cout << "\n=== PILIH MODE PERMAINAN ===\n";
    cout << "1. VS Player\n2. VS Komputer\nPilihan Anda: ";
    cin >> mode; cin.ignore();
    if(mode==1) playVsPlayer();
    else if(mode==2) playVsComputer();
    else cout << "Pilihan tidak valid.\n";
}

void menuLeaderboard(vector<Player>& players) {
    // Sort descending berdasarkan score
    sort(players.begin(), players.end(), [](const Player &a, const Player &b){
        return a.score > b.score;
    });

    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";

    cout << "Rank | Nama           | Score | Games | W  | D  | L  | \n";
    cout << "-----|----------------|-------|-------|----|----|----| \n";

    int limit = min(10, (int)players.size());
    for(int i = 0; i < limit; i++){
        printf(" %2d  | %-14s | %5d | %5d | %2d | %2d | %2d |\n",
            i+1,
            players[i].nama.c_str(),
            players[i].score,
            players[i].totalGames,
            players[i].totalWins,
            players[i].totalDraws,
            players[i].totalLosses
        );
    }

    cout << "\n================================\n";
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.ignore();
    cin.get();
    system("clear");
}


// ---------- main ----------
int main() {
    srand(time(0));

    // tampilan header
    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";

    // Cek file player
    ifstream fin("players.txt");
    if(!fin){
        cout << "File player tidak ditemukan. Membuat file baru... \n\n";
        ofstream fout("players.txt"); fout.close();
    } else {
        loadPlayers();
    }

    int pilihan;
    while(true){
        showMainMenu();
        cin >> pilihan;
        cin.ignore(); // Bersihkan line baru
        switch(pilihan){
            case 1: menuPlayerBaru(); break;
            case 2: menuPilihPlayer(); break;
            case 3: menuLeaderboard(players); break;
            case 4: cout << "Keluar dari program.\n"; return 0;
            default: cout << "Pilihan tidak valid!\n"; break;
        }
    }

    return 0;
}
