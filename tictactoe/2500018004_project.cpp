#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

void enter(){
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

int pilihPlayer(Player plyr[], int jumlahData) {
    int indexPlayer;
    int space = 0;

    for(int i=0; i<jumlahData; i++){
        if((int)plyr[i].nama.length()>space){
            space = plyr[i].nama.length();
        }
    }

    int nameWidth = space + 2;
    
    cout << "\n=== DAFTAR PLAYER ===" << endl;
    cout << "| "
         << setw(3) << "No" << " | "
         << left << setw(nameWidth) << "Nama" << " | "
         << left << setw(5) << "Score" << " | "
         << left << setw(5) << "Games" << " | "
         << left << setw(2) << "W" << " | "
         << left << setw(2) << "D" << " | "
         << left << setw(2) << "L" << " | " << endl;
    
    cout << "|-----|-";
    for (int i = 0; i <= nameWidth; i++) {
        cout << "-";
    }
    cout << "|-------|-------|----|----|----|" << endl;

    for(int i=0; i<jumlahData; i++){
        cout << "| "
             << setw(3) << i+1 << " | "
             << left << setw(nameWidth) << plyr[i].nama << " | "
             << left << setw(5) << plyr[i].score << " | "
             << left << setw(5) << plyr[i].totalGames << " | "
             << left << setw(2) << plyr[i].totalWins << " | "
             << left << setw(2) << plyr[i].totalDraws << " | "
             << left << setw(2) << plyr[i].totalLosses << " | " << endl;
    }

    cout << "\nPilih player (1-"<< jumlahData <<") atau 0 untuk kembali: "; cin >> indexPlayer;
    if(indexPlayer==0){
        return -1;
    }
    cin.ignore();
    indexPlayer-=1;
    cout << "\nPlayer dipilih: " << plyr[indexPlayer].nama << endl;
    cout << "\nSelamat datang kembali, " << plyr[indexPlayer].nama << endl;
    cout << "\nStatistik Anda: " << endl;
    cout << "- Total Games: " << plyr[indexPlayer].totalGames << endl;
    cout << "- Wins: " << plyr[indexPlayer].totalWins << endl;
    cout << "- Draws: " << plyr[indexPlayer].totalDraws << endl;
    cout << "- Losses: " << plyr[indexPlayer].totalLosses << endl;
    cout << "- Total Score: " << plyr[indexPlayer].score << endl;
    return indexPlayer;
}

int hitungIndex(Player plyr[]){
    int jumlahplyr = 0;
    ifstream file("players.txt");
    if(!file.is_open()){
        cout << "File tidak ditemukan" << endl;
    } else{
        while(file>>plyr[jumlahplyr].nama
            >>plyr[jumlahplyr].totalGames
            >>plyr[jumlahplyr].totalWins
            >>plyr[jumlahplyr].totalDraws
            >>plyr[jumlahplyr].totalLosses
            >>plyr[jumlahplyr].score
        ) {
            jumlahplyr++;
        }
        file.close();
    }
    return jumlahplyr;
}

void updateFile(Player plyr[], int jumlahData){
    ofstream file("players.txt", ios::trunc);
    for(int i=0; i<jumlahData; i++){
        file << plyr[i].nama << " "
        << plyr[i].totalGames << " "
        << plyr[i].totalWins << " "
        << plyr[i].totalDraws << " "
        << plyr[i].totalLosses << " "
        << plyr[i].score << endl;
    }
    file.close();
}

void simpanPlayer(Player plyr[]){
    int jmlPlayer = hitungIndex(plyr);
    ofstream file("players.txt", ios::app);
    if(!file.is_open()){
        cout << "File tidak ditemukan" << endl;
        return;
    }
    cout << "\n=== REGISTRASI PLAYER BARU ===" << endl;
    cout << "Masukkan nama Anda: "; cin >> plyr[jmlPlayer].nama;
    cout << "\nPlayer baru berhasil dibuat!" << endl;
    cout << "Selamat datang " << plyr[jmlPlayer].nama << "!" << endl;
    cin.ignore();

    plyr[jmlPlayer].totalGames = 0;
    plyr[jmlPlayer].totalWins = 0;
    plyr[jmlPlayer].totalDraws = 0;
    plyr[jmlPlayer].totalLosses = 0;
    plyr[jmlPlayer].score = 0;

    cout << "\nStatistik Anda: " << endl;
    cout << "- Total Games: " << plyr[jmlPlayer].totalGames << endl;
    cout << "- Total Wins: " << plyr[jmlPlayer].totalWins << endl;
    cout << "- Total Draws: " << plyr[jmlPlayer].totalDraws << endl;
    cout << "- Total Losses: " << plyr[jmlPlayer].totalLosses << endl;
    cout << "- Total Score: " << plyr[jmlPlayer].score << endl;

    file << plyr[jmlPlayer].nama << " "
         << plyr[jmlPlayer].totalGames << " "
         << plyr[jmlPlayer].totalWins << " "
         << plyr[jmlPlayer].totalDraws << " "
         << plyr[jmlPlayer].totalLosses << " "
         << plyr[jmlPlayer].score << endl;
    jmlPlayer++;
    file.close();
}

void leaderboard(Player plyr[], int jumlahData){
    struct topTen{
        string nama;
        int totalGames;
        int totalWins;
        int totalDraws;
        int totalLosses;
        int score;
    }; 

    int limit;
    if(jumlahData<10){
        limit = jumlahData;
    } else{
        limit = 10;
    }
    topTen top10[10];

    for(int i=0; i<jumlahData; i++){
        for(int j=0; j<jumlahData-i-1; j++){
            if(plyr[j].score<plyr[j+1].score){
                auto temp = plyr[j];
                plyr[j] = plyr[j+1];
                plyr[j+1] = temp;
            }
        }
    }
    
    for(int i=0; i<limit; i++){
        top10[i].nama = plyr[i].nama;
        top10[i].totalGames = plyr[i].totalGames;
        top10[i].totalWins = plyr[i].totalWins;
        top10[i].totalDraws = plyr[i].totalDraws;
        top10[i].totalLosses = plyr[i].totalLosses;
        top10[i].score = plyr[i].score;
    }

    int space = 0;

    for(int i=0; i<limit; i++){
        if((int)top10[i].nama.length()>space){
            space = top10[i].nama.length();
        }
    }

    int nameWidth = space + 2;

    cout << "============================" << endl;
    cout << "        LEADERBOARD" << endl;
    cout << "  Top 10 Players By Score" << endl;
    cout << "============================\n" << endl;

    cout << "| "
         << setw(4) << "Rank" << " | "
         << left << setw(nameWidth) << "Nama" << " | "
         << left << setw(5) << "Score" << " | "
         << left << setw(5) << "Games" << " | "
         << left << setw(2) << "W" << " | "
         << left << setw(2) << "D" << " | "
         << left << setw(2) << "L" << " | " << endl;
    
    cout << "|------|-";
    for (int i=0; i<=nameWidth; i++) {
        cout << "-";
    }
    cout << "|-------|-------|----|----|----|" << endl;


    for(int i=0; i<limit; i++){
        cout << "| "
             << setw(4) << i+1 << " | "
             << left << setw(nameWidth) << top10[i].nama << " | "
             << left << setw(5) << top10[i].score << " | "
             << left << setw(5) << top10[i].totalGames << " | "
             << left << setw(2) << top10[i].totalWins << " | "
             << left << setw(2) << top10[i].totalDraws << " | "
             << left << setw(2) << top10[i].totalLosses << " | " << endl;
    }
}

int pilihMode(){
    int menu;
    cout << "\n=== PILIH MODE PERMAINAN ===" << endl;
    cout << "1. VS Player" << endl;
    cout << "2. VS Komputer" << endl;
    cout << "\nPilihan Anda: "; cin >> menu;
    cout << "Mode VS " << (menu==1?"Player":"Komputer") << " dipilih!" << endl;
    return menu;
}

string conBoard(vector<vector<string>>&board){
    string hasil = "";
    for(int i=0; i<3; i++){
        hasil+=" "+board[i][0]+" | "+board[i][1]+" | "+board[i][2]+"\n";
        if(i<2){
            hasil+="---|---|---\n";
        }
    }
    return hasil;
}

bool checkWin(vector<vector<string>>&board){
    // Check baris
    for(int i=0; i<3; i++){
        if(board[i][0]!=" "&&board[i][0]==board[i][1]&&board[i][1]==board[i][2]){
            return true;
        }
    }
    // Check Kolom
    for(int i=0; i<3; i++){
        if(board[0][i]!=" "&&board[0][i]==board[1][i]&&board[1][i]==board[2][i]){
            return true;
        }
    }
    if(board[0][0]!=" "&&board[0][0]==board[1][1]&&board[1][1]==board[2][2]){
        return true;
    }
    if(board[0][2]!=" "&&board[0][2]==board[1][1]&&board[1][1]==board[2][0]){
        return true;
    }
    return false;
}

bool checkPos(vector<vector<string>>&board, int posisi){
    if(posisi<1||posisi>9){
        return false;
    }
    int baris = (posisi-1)/3;
    int kolom = (posisi-1)%3;
    return board[baris][kolom]==" ";
}

void VSPlayer(Player plyr[], int indexPlayer, int jumlah){
    char yn;
    do{
        vector<vector<string>> board(3,vector<string>(3," "));
        int langkah = 1;
        cout << "=============================" << endl;
        cout << "      TIC TAC TOE GAME" << endl;
        cout << "=============================" << endl;
        cout << "\n 1 | 2 | 3" << endl;
        cout << "---|---|---" << endl;
        cout << " 4 | 5 | 6" << endl;
        cout << "---|---|---" << endl;
        cout << " 7 | 8 | 9" << endl;
    
        while(!checkWin(board)&&langkah<=9){
            string symbol=(langkah%2==1?"X":"O");
            int posisi;
            cout << endl;
            cout << conBoard(board);
            cout << endl;
            cout << "\nGiliran Anda (" << symbol << ")" << endl;
            cout << "Masukkan posisi (1-9): "; cin >> posisi;
            while(!checkPos(board,posisi)){
                cout << "Posisi tidak valid" << endl;
                cout << "Masukkan posisi (1-9): "; cin >> posisi;
            }
            cin.ignore();
            board[(posisi-1)/3][(posisi-1)%3]=symbol;
            langkah++;
        }
        cout << endl;
        cout << conBoard(board);
        cout << endl;
        if(checkWin(board)){
            if((langkah-1)%2!=0){
                cout << "Player X menang!"<< endl;
                plyr[indexPlayer].totalWins++;
                plyr[indexPlayer].score+=3;
            } else{
                cout << "Player X kalah!" << endl;
                plyr[indexPlayer].totalLosses++;
            }
        } else{
            cout << "SERI! Tidak ada yang menang." << endl;
            plyr[indexPlayer].totalDraws++;
            plyr[indexPlayer].score+=1;
        }
        plyr[indexPlayer].totalGames++;
        cout << "=============================" << endl;
        cout << "     HASIL PERTANDINGAN" << endl;
        cout << "=============================" << endl;
        if(!checkWin(board)){
            cout << "Hasil: SERI" << endl;
            cout << "Score yang didapat: +1" << endl;
            cout << "\nStatistik Anda: " << endl;
            cout << "- Total Games: " << plyr[indexPlayer].totalGames << endl;
            cout << "- Wins: " << plyr[indexPlayer].totalWins << endl;
            cout << "- Draws: " << plyr[indexPlayer].totalDraws << endl;
            cout << "- Losses: " << plyr[indexPlayer].totalLosses << endl;
            cout << "- Total Score: " << plyr[indexPlayer].score << endl;
        } else{
            if((langkah-1)%2!=0){
                cout << "Hasil: MENANG" << endl;
                cout << "Score yang didapat: +3" << endl;
                cout << "\nStatistik Anda: " << endl;
                cout << "- Total Games: " << plyr[indexPlayer].totalGames << endl;
                cout << "- Wins: " << plyr[indexPlayer].totalWins << endl;
                cout << "- Draws: " << plyr[indexPlayer].totalDraws << endl;
                cout << "- Losses: " << plyr[indexPlayer].totalLosses << endl;
                cout << "- Total Score: " << plyr[indexPlayer].score << endl;
            } else{
                cout << "Hasil: KALAH" << endl;
                cout << "Score yang didapat: +0" << endl;
                cout << "\nStatistik Anda: " << endl;
                cout << "- Total Games: " << plyr[indexPlayer].totalGames << endl;
                cout << "- Wins: " << plyr[indexPlayer].totalWins << endl;
                cout << "- Draws: " << plyr[indexPlayer].totalDraws << endl;
                cout << "- Losses: " << plyr[indexPlayer].totalLosses << endl;
                cout << "- Total Score: " << plyr[indexPlayer].score << endl;
            }
        }
        updateFile(plyr,jumlah);
        cout << "\nData telah disimpan ke file players.txt" << endl;
        cout << "\nMain lagi? (y/n): "; cin >> yn;
    } while(yn=='y'||yn=='Y');
}

void VSComputer(Player plyr[], int indexPlayer, int jumlah){
    char yn;
    do{
        vector<vector<string>> board(3,vector<string>(3," "));
        int langkah = 1;
        cout << "=============================" << endl;
        cout << "      TIC TAC TOE GAME" << endl;
        cout << "=============================" << endl;
        cout << "\n 1 | 2 | 3" << endl;
        cout << "---|---|---" << endl;
        cout << " 4 | 5 | 6" << endl;
        cout << "---|---|---" << endl;
        cout << " 7 | 8 | 9" << endl;
        while(!checkWin(board)&&langkah<=9){
            string symbol=(langkah%2==1?"X":"O");
            if(langkah%2==1){
                int posisi;
                cout << endl;
                cout << conBoard(board);
                cout << endl;
                cout << "\nGiliran Anda (X)" << endl;
                cout << "Masukkan posisi (1-9): "; cin >> posisi;
                while(!checkPos(board,posisi)){
                    cout << "Posisi tidak valid" << endl;
                    cout << "Masukkan posisi (1-9): "; cin >> posisi;
                }
                cin.ignore();
                board[(posisi-1)/3][(posisi-1)%3]=symbol;
            } else{
                srand(time(0));
                int posisi = (rand()%9)+1;
                while(!checkPos(board, posisi)){
                    posisi = (rand()%9)+1;
                }
                cout << endl;
                cout << conBoard(board);
                cout << endl;
                cout << "Komputer sedang berpikir..." << endl;
                cout << "Komputer memilih posisi: " << posisi << endl;
                board[(posisi-1)/3][(posisi-1)%3]=symbol;
            }
            langkah++;
        }
        cout << endl;
        cout << conBoard(board);
        cout << endl;
    
        string hasil;
        int point;
        if(checkWin(board)){
            if((langkah-1)%2!=0){
                cout << "Anda Menang!" << endl;
                hasil = "MENANG";
                point = 3;
                plyr[indexPlayer].score+=point;
                plyr[indexPlayer].totalWins++;
            } else{
                cout << "Komputer Menang!" << endl;
                hasil = "KALAH";
                point = 0;
                plyr[indexPlayer].score+=point;
                plyr[indexPlayer].totalLosses++;
            }
        } else{
            cout << "SERI! Tidak ada yang menang." << endl;
            hasil = "SERI";
            point = 1;
            plyr[indexPlayer].score+=point;
            plyr[indexPlayer].totalDraws++;
        }
        plyr[indexPlayer].totalGames++;
        cout << "\n=============================" << endl;
        cout << "     HASIL PERTANDINGAN" << endl;
        cout << "=============================" << endl;
        cout << "Hasil: " << hasil << endl;
        cout << "Score yang didapat: +" << point << " poin" << endl;
    
        cout << "\nStatistik Anda: " << endl;
        cout << "- Total Games: " << plyr[indexPlayer].totalGames << endl;
        cout << "- Wins: " << plyr[indexPlayer].totalWins << endl;
        cout << "- Draws: " << plyr[indexPlayer].totalDraws << endl;
        cout << "- Losses: " << plyr[indexPlayer].totalLosses << endl;
        cout << "- Total Score: " << plyr[indexPlayer].score << endl;
        updateFile(plyr, jumlah);
        cout << "\nData telah disimpan ke file players.txt" << endl;
        cout << "\nMain lagi? (y/n): "; cin >> yn;
    } while(yn=='y'||yn=='Y');
}

int main(){
    int menu;
    Player plyr[50];
    int jumlahData = hitungIndex(plyr);
    bool isFileChecked = false;
    const string filename = "players.txt";

    do{
        system("cls");
        cout << "=============================" << endl;
        cout << "      TIC TAC TOE GAME" << endl;
        cout << "=============================" << endl;
    
        if(!isFileChecked){ 
            ifstream file(filename);
                if(!file.is_open()){
                    cout << "File tidak ditemukan, membuat file baru..." << endl;
                    ofstream newfile(filename);
                    newfile.close();
                } else {
                    cout << "File ditemukan" << endl;
                    file.close();
                }
                isFileChecked = true;
        }
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Player Baru" << endl;
        cout << "2. Pilih Player yang Sudah Ada" << endl;
        cout << "3. Lihat Leaderboard" << endl;
        cout << "4. Keluar" << endl;
        cout << "\nPilihan Anda: "; cin >> menu;
        cin.ignore();
    
        switch(menu){
            case 1:
                simpanPlayer(plyr);
                enter();
            break;
            case 2:{
                int indexPlayer = pilihPlayer(plyr, jumlahData);
                if(indexPlayer==-1){
                    break;
                }
                int mode = pilihMode();
                if(mode==1){
                    VSPlayer(plyr, indexPlayer, jumlahData);
                } else{
                    VSComputer(plyr, indexPlayer, jumlahData);
                }
                enter();
            }
            break;
            case 3:
                leaderboard(plyr, jumlahData);
                enter();
            break;
        }
    } while(menu!=4);
    cout << "\nTerimakasih telah bermain!" << endl;
    return 0;
}