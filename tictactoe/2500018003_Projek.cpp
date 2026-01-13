#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

struct Player {
    string name;
    int totalGames = 0;
    int totalWins = 0;
    int totalDraws = 0;
    int totalLosses = 0;
    int score = 0;
};

vector<Player> players;
Player currentPlayer;

void pauseScreen(){
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void player() {
    ifstream file("players.txt");
    if (!file) {
        cout << "\nFile player tidak ditemukan.  Membuat file baru...\n\n";
        ofstream newFile("players.txt");
        newFile.close();
        return;
    }

    Player p;
    while (file >> p.name >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses >> p.score)
        players.push_back(p);
    file.close();
}

void simpanPlayer() {
    ofstream file("players.txt");
    for (auto &p : players)
        file << p.name << " " << p.totalGames << " " << p.totalWins << " "
             << p.totalDraws << " " << p.totalLosses << " " << p.score << endl;
    file.close();
    cout << "\nData telah disimpan ke file players.txt\n";
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
             << "  | " << p.name
             << string(15 - p.name.length(), ' ')
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

void showPlayersList() {
    cout << "\n=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           | Score | Games | W  | D  | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";
    for(int i=0;i<players.size();i++){
        Player &p=players[i];
        cout<<i+1<<"  | "<<p.name
            <<string(15-p.name.length(),' ')
            <<"|  "<<p.score
            <<"   |  "<<p.totalGames
            <<"   | "<<p.totalWins
            <<" | "<<p.totalDraws
            <<" | "<<p.totalLosses<<"\n";
    }
   
}

void displayGuide(){
    cout<<"\nPanduan Posisi:\n";
    cout<<" 1 | 2 | 3\n---|---|---\n 4 | 5 | 6\n---|---|---\n 7 | 8 | 9\n\n";
}

void displayBoard(char board[3][3]){
    cout<<"\n";
    for(int i=0;i<3;i++){
        cout<<" ";
        for(int j=0;j<3;j++){
            cout<<" "<<board[i][j];
            if(j<2) cout<<" |";
        }
        cout<<"\n";
        if(i<2) cout<<" ---|---|---\n";
    }
    cout<<"\n";
}

bool checkWin(char b[3][3], char p){
    for(int i=0;i<3;i++)
        if(b[i][0]==p && b[i][1]==p && b[i][2]==p) return true;
    for(int j=0;j<3;j++)
        if(b[0][j]==p && b[1][j]==p && b[2][j]==p) return true;
    if(b[0][0]==p && b[1][1]==p && b[2][2]==p) return true;
    if(b[0][2]==p && b[1][1]==p && b[2][0]==p) return true;
    return false;
}

bool boardFull(char b[3][3]){
    for(int i=0;i<3;i++) for(int j=0;j<3;j++)
        if(b[i][j]==' ') return false;
    return true;
}

bool validMove(char b[3][3], int pos){
    if(pos<1||pos>9) return false;
    return b[(pos-1)/3][(pos-1)%3]==' ';
}

void makeMove(char b[3][3], int pos, char p){
    b[(pos-1)/3][(pos-1)%3]=p;
}

int computerMove(char board[3][3]){
    for(int i=1;i<=9;i++){
        if(validMove(board,i)){
            char t[3][3];
            for(int x=0;x<3;x++) for(int y=0;y<3;y++) t[x][y]=board[x][y];
            makeMove(t,i,'O');
            if(checkWin(t,'O')) return i;
        }
    }
    for(int i=1;i<=9;i++){
        if(validMove(board,i)){
            char t[3][3];
            for(int x=0;x<3;x++) for(int y=0;y<3;y++) t[x][y]=board[x][y];
            makeMove(t,i,'X');
            if(checkWin(t,'X')) return i;
        }
    }
    if(validMove(board,5)) return 5;
    int corners[4]={1,3,7,9};
    for(int c:corners) if(validMove(board,c)) return c;
    for(int i=1;i<=9;i++) if(validMove(board,i)) return i;
    return -1;
}

void lawanKomputer(Player &p){
    while(true){
        system("cls"); 
        cout<<"================================\n";
        cout<<"     TIC TAC TOE GAME\n";
        cout<<"================================\n";
        displayGuide();

        char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
        int pos;

        while(true){
            displayBoard(board);
            cout<<"Giliran Anda (X)\nMasukkan posisi (1-9): ";
            cin>>pos;

            if(!validMove(board,pos)){
                cout<<"Posisi tidak valid! Coba lagi.\n";
                continue;
            }
            makeMove(board,pos,'X');

            if(checkWin(board,'X')){
                displayBoard(board);
                cout<<"🎉 ANDA MENANG! 🎉\n";
                p.totalGames++; p.totalWins++; p.score+=3;
                break;
            }
            if(boardFull(board)){
                displayBoard(board);
                cout<<"SERI! Tidak ada yang menang.\n";
                p.totalGames++; p.totalDraws++; p.score+=1;
                break;
            }

            cout<<"Komputer sedang berpikir...\n";
            int cm = computerMove(board);
            makeMove(board,cm,'O');
            cout<<"Komputer memilih posisi: "<<cm<<"\n";

            if(checkWin(board,'O')){
                displayBoard(board);
                cout<<"💻 KOMPUTER MENANG! 💻\n";
                p.totalGames++; p.totalLosses++;
                break;
            }
            if(boardFull(board)){
                displayBoard(board);
                cout<<"SERI! Tidak ada yang menang.\n";
                p.totalGames++; p.totalDraws++; p.score+=1;
                break;
            }
        }

        cout<<"\n================================";
        cout<<"\n       HASIL PERTANDINGAN";
        cout<<"\n================================";
        cout<<"\nHasil: ";
        if(checkWin(board,'X')) cout<<"MENANG";
        else if(checkWin(board,'O')) cout<<"KALAH";
        else cout<<"SERI";

        cout<<"\nScore yang didapat: "<<(checkWin(board,'X')?"+3":checkWin(board,'O')?"+0":"+1")<<" poin\n";

        cout<<"\nStatistik "<<p.name<<":";
        cout<<"\n- Total Games:  "<<p.totalGames;
        cout<<"\n- Wins: "<<p.totalWins;
        cout<<"\n- Draws: "<<p.totalDraws;
        cout<<"\n- Losses: "<<p.totalLosses;
        cout<<"\n- Total Score: "<<p.score<<"\n";

        simpanPlayer();
		pauseScreen();
        char lagi;
        cout<<"\nMain lagi? (y/n): ";
        cin>>lagi;
        if(lagi!='y'&&lagi!='Y') break;
    }
}

void lawanPlayer(Player &p){
    while(true){
        system("cls");
        cout<<"=== PILIH MODE PERMAINAN ===\n1. VS Player\n2. VS Komputer\nPilihan Anda: ";
        int m;cin>>m;
        if(m!=1) return;

        cout<<"\nMode VS Player dipilih!\nPlayer 1: X\nPlayer 2: O\n";
        cin.ignore();
        cout<<"Tekan Enter untuk memulai...";
        cin.get();

        char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
        bool turnX=true;
        int pos;

        while(true){
            system("cls");
            cout<<"================================\n";
            cout<<"     TIC TAC TOE GAME\n";
            cout<<"================================\n";
            displayGuide();
            displayBoard(board);

            cout<<"Giliran Player "<<(turnX?'X':'O')<<"\nMasukkan posisi (1-9): ";
            cin>>pos;

            if(!validMove(board,pos)){
                cout<<"Posisi tidak valid!\n";
                cin.ignore();cin.get();
                continue;
            }

            makeMove(board,pos,turnX?'X':'O');

            if(checkWin(board,'X')){
                displayBoard(board);
                cout<<"🎉 Player X MENANG! 🎉\n";
                p.totalGames++; p.totalWins++; p.score+=3;
                break;
            }
            if(checkWin(board,'O')){
                displayBoard(board);
                cout<<"🎉 Player O MENANG! 🎉\n";
                p.totalGames++; p.totalLosses++;
                break;
            }
            if(boardFull(board)){
                displayBoard(board);
                cout<<"SERI!\n";
                p.totalGames++; p.totalDraws++; p.score+=1;
                break;
            }
            turnX=!turnX;
        }

        cout<<"\n================================";
        cout<<"\n       HASIL PERTANDINGAN";
        cout<<"\n================================";

        cout<<"\nStatistik "<<p.name<<":";
        cout<<"\n- Total Games: "<<p.totalGames;
        cout<<"\n- Wins: "<<p.totalWins;
        cout<<"\n- Draws: "<<p.totalDraws;
        cout<<"\n- Losses: "<<p.totalLosses;
        cout<<"\n- Total Score: "<<p.score<<"\n";

        simpanPlayer();
		pauseScreen();

        char lagi;
        cout<<"\nMain lagi? (y/n): ";
        cin>>lagi;
        if(lagi!='y'&&lagi!='Y') break;
    }
}

void tambahPlayer(){
    cout<<"\n=== REGISTRASI PLAYER BARU ===\nMasukkan nama Anda: ";
    string n;cin>>n;

    Player p; p.name=n;
    players.push_back(p);
    currentPlayer=p;

    cout<<"\nPlayer baru berhasil dibuat!\nSelamat datang, "<<n<<"!\n\nStatistik Anda:";
    cout<<"\n- Total Games: 0\n- Wins: 0\n- Draws: 0\n- Losses: 0\n- Total Score: 0\n";

    simpanPlayer();
	pauseScreen();

}

bool pilih(){
    if(players.empty()){
        cout<<"Belum ada player!\n";
        cin.ignore();cin.get();
        return false;
    }
    showPlayersList();
    cout<<"\nPilih player (1-"<<players.size()<<") atau 0 untuk kembali: ";
    int c;cin>>c;
    if(c==0) return false;
    c--;

    currentPlayer=players[c];
    cout<<"\nPlayer dipilih: "<<currentPlayer.name<<"\nSelamat datang kembali!\n";
    cout<<"\nStatistik Anda:\n- Total Games: "<<currentPlayer.totalGames;
    cout<<"\n- Wins: "<<currentPlayer.totalWins;
    cout<<"\n- Draws: "<<currentPlayer.totalDraws;
    cout<<"\n- Losses: "<<currentPlayer.totalLosses;
    cout<<"\n- Total Score: "<<currentPlayer.score<<"\n";

    pauseScreen();
    return true;
}

void menu(){
    while(true){
        system("cls");
        cout<<"================================\n";
        cout<<"     TIC TAC TOE GAME\n";
        cout<<"================================\n";
        cout<<"\n=== MENU UTAMA ===";
        cout<<"\n1. Player Baru";
        cout<<"\n2. Pilih Player yang Sudah Ada";
        cout<<"\n3. Lihat Leaderboard";
        cout<<"\n4. Keluar";
        cout<<"\n\nPilihan Anda: ";

        int p;cin>>p;

        if(p==1) tambahPlayer();
        else if(p==2){ if(pilih()){
                while(true){
                    system("cls");
                    cout<<"\n=== PILIH MODE PERMAINAN ===\n1. VS Player\n2. VS Komputer\n3. Kembali\nPilihan Anda: ";
                    int m;cin>>m;
                    if(m==1) lawanPlayer(currentPlayer);
                    else if(m==2) lawanKomputer(currentPlayer);
                    else break;
                }
            }
        }
        else if(p==3) leaderboard();
        else if(p==4){
            cout<<"\nTerima kasih telah bermain!\n";
            pauseScreen();
            simpanPlayer();
            break;
        }
        else{
            cout<<"Input salah!\n";
            pauseScreen();
        }

        for(int i=0;i<players.size();i++){
            if(players[i].name==currentPlayer.name){
                players[i]=currentPlayer;
                break;
            }
        }
        simpanPlayer();
    }
}

int main(){
    srand(time(0));
    player();
    menu();
    return 0;
}
