#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

#define FILE_NAME "players.txt"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct Player {
    string name;
    int games = 0;
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int score = 0;
};

Player currentPlayer;


void clearScreen(){ system(CLEAR); }

void header(){
    cout << "================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

void pressEnter(){
    cout << "Tekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void guide(){
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n---|---|---\n";
    cout << " 4 | 5 | 6\n---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void showBoard(char b[]){
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

bool checkWin(char b[], char s){
    int w[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(auto &x:w) if(b[x[0]]==s && b[x[1]]==s && b[x[2]]==s) return true;
    return false;
}

bool draw(char b[]){
    for(int i=0;i<9;i++) if(b[i]==' ') return false;
    return true;
}

/* ---------- FILE ---------- */
void savePlayers(const vector<Player>& p){
    ofstream f(FILE_NAME);
    for(auto &x:p)
        f<<x.name<<" "<<x.games<<" "<<x.wins<<" "<<x.draws<<" "<<x.losses<<" "<<x.score<<"\n";
}

void savePlayer(Player cur, vector<Player>& p){
    for(auto &x:p){
        if(x.name==cur.name){ x=cur; savePlayers(p); return; }
    }
    p.push_back(cur);
    savePlayers(p);
}

void showLeaderboard(const vector<Player>& p){
    if(p.empty()){
        cout<<"\nBelum ada pemain terdaftar.\n\n";
        return;
    }
    
    vector<Player> sorted_players = p;
    sort(sorted_players.begin(), sorted_players.end(), [](const Player& a, const Player& b){
        return a.score > b.score;
    });
    
    cout<<"\n================================\n";
    cout<<"        LEADERBOARD\n";
    cout<<"================================\n";
    cout<<setw(5)<<"Rank"<<setw(15)<<"Nama"<<setw(10)<<"Games"<<setw(8)<<"Wins"<<setw(8)<<"Score"<<"\n";
    cout<<"================================\n";
    
    for(size_t i=0; i<sorted_players.size(); i++){
        cout<<setw(5)<<i+1
            <<setw(15)<<sorted_players[i].name
            <<setw(10)<<sorted_players[i].games
            <<setw(8)<<sorted_players[i].wins
            <<setw(8)<<sorted_players[i].score<<"\n";
    }
    cout<<"================================\n\n";
}

void vsComputer(Player& cur, vector<Player>& players){
    while(true){
        clearScreen(); header(); guide();
        char b[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
        showBoard(b);

        bool win=false, lose=false, tie=false;

        while(true){
            int pos;
            cout<<"Giliran Anda (X)\nMasukkan posisi (1-9): ";
            cin>>pos;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Input tidak valid. Masukkan angka 1-9.\n";
                continue;
            }
            if(pos<1||pos>9||b[pos-1]!=' '){
                cout<<"Posisi tidak valid atau sudah terisi. Coba lagi.\n";
                continue;
            }
            b[pos-1]='X'; showBoard(b);

            if(checkWin(b,'X')){ win=true; break; }
            if(draw(b)){ tie=true; break; }

            cout<<"Komputer sedang berpikir...\n";
            do{ pos=rand()%9; }while(b[pos]!=' ');
            cout<<"Komputer memilih posisi:  "<<pos+1<<"\n\n";
            b[pos]='O'; showBoard(b);

            if(checkWin(b,'O')){ lose=true; break; }
            if(draw(b)){ tie=true; break; }
        }

        if(win)cout<<"🎉 ANDA MENANG! 🎉\n\n";
        else if(lose)cout<<"💻 KOMPUTER MENANG! 💻\n\n";
        else cout<<"SERI! Tidak ada yang menang. \n\n";
        

        cout<<"================================\n       HASIL PERTANDINGAN\n================================\n";

        cur.games++;
        if(win){
             cur.wins++; cur.score+=3; cout<<"Hasil:  MENANG\nScore yang didapat: +3 poin\n\n"; 
            }else if(lose){ 
                cur.losses++; cout<<"Hasil: KALAH\nScore yang didapat: +0 poin\n\n";
            }else{ 
                cur.draws++; cur.score+=1; cout<<"Hasil: SERI\nScore yang didapat: +1 poin\n\n"; 
            }

        cout<<"Statistik "<<cur.name<<":\n";
        cout<<"- Total Games: "<<cur.games<<"\n- Wins: "<<cur.wins<<"\n- Draws: "<<cur.draws
            <<"\n- Losses: "<<cur.losses<<"\n- Total Score: "<<cur.score<<"\n\n";

        savePlayer(cur,players);
        cout<<"Data telah disimpan ke file players.txt\n\n";

        char u;
        while(true){
            cout<<"Main lagi? (y/n): ";
            cin>>u;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Input tidak valid. Masukkan y atau n.\n";
                continue;
            }
            break;
        }
        if(u!='y'&&u!='Y') break;
    }
}

int main(){
    srand(time(nullptr));
    clearScreen(); header();

    vector<Player> players;
    ifstream in(FILE_NAME);
    if(!in.is_open()){
        cout<<"File player tidak ditemukan.  Membuat file baru... \n\n";
        ofstream(FILE_NAME).close();
    }else{
        Player p;
        while(in>>p.name>>p.games>>p.wins>>p.draws>>p.losses>>p.score)
            players.push_back(p);
    }

    while(true){
        cout<<"=== MENU UTAMA ===\n1. Player Baru\n2. Pilih Player yang Sudah Ada\n3. Lihat Leaderboard\n4. Keluar\n\n";
        cout<<"Pilihan Anda: ";
        int c;
        cin>>c;
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Input tidak valid. Masukkan angka 1-4.\n\n";
            continue;
        }
        cin.ignore();

        if(c==1){
            cout<<"\n=== REGISTRASI PLAYER BARU ===\nMasukkan nama Anda: ";
            getline(cin,currentPlayer.name);
            currentPlayer=Player{currentPlayer.name};
            pressEnter();
            savePlayer(currentPlayer,players);
            vsComputer(currentPlayer,players);
        }
        else if(c==2){
            cout<<"\nPilih player:\n";
            for(size_t i=0;i<players.size();i++)
                cout<<i+1<<". "<<players[i].name<<"\n";
            int p;
            cin>>p;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Input tidak valid. Masukkan angka yang sesuai.\n\n";
                continue;
            }
            if(p>0 && p<=players.size()){
                currentPlayer=players[p-1];
                pressEnter();
                vsComputer(currentPlayer,players);
            }else{
                cout<<"Pilihan tidak valid.\n\n";
            }
        }
        else if(c==2){
            cout<<"\nPilih player:\n";
            for(size_t i=0;i<players.size();i++)
                cout<<i+1<<". "<<players[i].name<<"\n";
            int p; cin>>p;
            if(p>0 && p<=players.size()){
                currentPlayer=players[p-1];
                pressEnter();
                vsComputer(currentPlayer,players);
            }
        }
        else if(c==4) break;
    }

    cout<<"\nTerima kasih telah bermain!\n";
    return 0;
}
