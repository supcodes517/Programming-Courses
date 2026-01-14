// Muhammad Arif Rahman
// 2500018001
// Kelas A

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

struct Player {
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

void clearScreen() {
    system("cls");
}

void pressEnter() {
    cout << "Tekan Enter untuk melanjutkan. . .";
    cin.get();
}

void loadData(Player dataPlayer[], int &jumlah) {
    ifstream file("players.txt");
    jumlah = 0;

    if (!file.is_open()) return;

    while (file >> dataPlayer[jumlah].nama
                >> dataPlayer[jumlah].totalGames
                >> dataPlayer[jumlah].totalWins
                >> dataPlayer[jumlah].totalDraws
                >> dataPlayer[jumlah].totalLosses
                >> dataPlayer[jumlah].score) {
        jumlah++;
    }

    file.close();
}

void updateData(Player dataPlayer[], int jumlah) {
    ofstream file("players.txt", ios::trunc);

    for (int i = 0; i < jumlah; i++) {
        file
        << dataPlayer[i].nama << " "
        << dataPlayer[i].totalGames << " "
        << dataPlayer[i].totalWins << " "
        << dataPlayer[i].totalDraws << " "
        << dataPlayer[i].totalLosses << " "
        << dataPlayer[i].score << endl;
    }

    file.close();
}

void registrasiPlayer(Player dataPlayer[], int &jumlah) {
    cout << "=== REGISTRASI PLAYER BARU ===" << endl;
    cout << "Masukkan Nama Anda: ";

    string inputNama;
    getline(cin, inputNama);

    while(inputNama.empty()) {
        cin.clear();
        cout << "\nInput Tidak Valid!" << endl;
        cout << "Masukkan Nama Anda: ";
        getline(cin, inputNama);
    }

    for (int i = 0; i < (int)inputNama.length(); i++) {
        if (inputNama[i] == ' ') {
            inputNama[i] = '_';
        }
    }

    dataPlayer[jumlah].nama = inputNama;

    cout << "\nPlayer Baru Berhasil Dibuat!" << endl;
    cout << "Selamat Datang, " << dataPlayer[jumlah].nama << endl;

    dataPlayer[jumlah].totalGames = 0;
    dataPlayer[jumlah].totalWins = 0;
    dataPlayer[jumlah].totalDraws = 0;
    dataPlayer[jumlah].totalLosses = 0;
    dataPlayer[jumlah].score = 0;

    cout << "\nStatistik Anda:" << endl;
    cout << "- Total Games: " << dataPlayer[jumlah].totalGames << endl;
    cout << "- Wins: " << dataPlayer[jumlah].totalWins << endl;
    cout << "- Draws: " << dataPlayer[jumlah].totalDraws << endl;
    cout << "- Losses: " << dataPlayer[jumlah].totalLosses << endl;
    cout << "- Total Score: " << dataPlayer[jumlah].score << endl;

    ofstream dataFile("players.txt", ios::app);

    dataFile
    << dataPlayer[jumlah].nama << " "
    << dataPlayer[jumlah].totalGames << " "
    << dataPlayer[jumlah].totalWins << " "
    << dataPlayer[jumlah].totalDraws << " "
    << dataPlayer[jumlah].totalLosses << " "
    << dataPlayer[jumlah].score << endl;

    dataFile.close();

    jumlah++;

    cout << endl;
}

int pilihPlayer(Player dataPlayer[], int &jumlah) {
    if (jumlah == 0) {
        cout << "Tidak Ada Data Player!\n" << endl;
        pressEnter();
        return -1;
    }

    int namaTerpanjang = 0;
    
    for (int i = 0; i < jumlah; i++) {
        if ((int)dataPlayer[i].nama.length() > namaTerpanjang) {
            namaTerpanjang = dataPlayer[i].nama.length();
        }
    }

    cout << "=== DAFTAR PLAYER ===" << endl;
    cout << "No  | " << left << setw(namaTerpanjang + 10) << "Nama" << "| Score | Games |  W  |  D  |  L  " << endl;
    cout << "----|-";
    for (int i = 0; i < namaTerpanjang + 10; i++) cout << "-";
    cout << "|-------|-------|-----|-----|-----" << endl;
    for (int i = 0; i < jumlah; i++) {
        cout << left 
            << setw(4)  << i + 1 << "| "
            << setw(namaTerpanjang + 10) << dataPlayer[i].nama << "| "
            << setw(6)  << dataPlayer[i].score << "| "
            << setw(6)  << dataPlayer[i].totalGames << "| "
            << setw(4)  << dataPlayer[i].totalWins << "| "
            << setw(4)  << dataPlayer[i].totalDraws << "| "
            << setw(4)  << dataPlayer[i].totalLosses 
            << endl;
    }

    int indexPlayerSelected;
    string inputRaw;

    while (true) {
        cout << "\nPilih player "
            << (jumlah == 1 ? "(1)" : "(1-" + to_string(jumlah) + ")")
            << " atau 0 untuk kembali: ";
        getline(cin, inputRaw);

        try {
            indexPlayerSelected = stoi(inputRaw);

            if (indexPlayerSelected == 0) return -1;
            if (indexPlayerSelected >= 1 && indexPlayerSelected <= jumlah) break;

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

    indexPlayerSelected -= 1;

    cout << "\nPlayer Dipilih: " << dataPlayer[indexPlayerSelected].nama << endl;
    cout << "\nSelamat Datang Kembali, " << dataPlayer[indexPlayerSelected].nama << "!" << endl;
    cout << "\nStatistik Anda:" << endl;
    cout << "- Total Games: " << dataPlayer[indexPlayerSelected].totalGames << endl;
    cout << "- Wins: " << dataPlayer[indexPlayerSelected].totalWins << endl;
    cout << "- Draws: " << dataPlayer[indexPlayerSelected].totalDraws << endl;
    cout << "- Losses: " << dataPlayer[indexPlayerSelected].totalLosses << endl;
    cout << "- Total Score: " << dataPlayer[indexPlayerSelected].score << endl;

    cout << endl;
    pressEnter();

    return indexPlayerSelected;
}

int pilihPlayer2(Player dataPlayer[], int &jumlah, int p1) {
    if (jumlah == 0) {
        cout << "Tidak Ada Data Player!\n" << endl;
        pressEnter();
        return -1;
    }

    int namaTerpanjang = 0;

    for (int i = 0; i < jumlah; i++) {
        if ((int)dataPlayer[i].nama.length() > namaTerpanjang) {
            namaTerpanjang = dataPlayer[i].nama.length();
        }
    }

    cout << "=== DAFTAR PLAYER ===" << endl;
    cout << "No  | " << left << setw(namaTerpanjang + 10) << "Nama" << "| Score | Games |  W  |  D  |  L  " << endl;
    cout << "----|-";
    for (int i = 0; i < namaTerpanjang + 10; i++) cout << "-";
    cout << "|-------|-------|-----|-----|-----" << endl;

    for (int i = 0; i < jumlah; i++) {
        string coret = (i == p1) ? "\033[9m" : "";
        string reset = (i == p1) ? "\033[0m" : "";

        cout << coret
            << left << setw(4)  << i + 1 << "| "
            << left << setw(namaTerpanjang + 10) << dataPlayer[i].nama << "| "
            << left << setw(6)  << dataPlayer[i].score << "| "
            << left << setw(6)  << dataPlayer[i].totalGames << "| "
            << left << setw(4)  << dataPlayer[i].totalWins << "| "
            << left << setw(4)  << dataPlayer[i].totalDraws << "| "
            << left << setw(4)  << dataPlayer[i].totalLosses
            << reset << endl;
    }

    int indexPlayerSelected;
    string inputRaw;

    while (true) {
        cout << "\nPilih player "
            << (jumlah == 1 ? "(1)" : "(1-" + to_string(jumlah) + ")")
            << " atau 0 untuk kembali: ";
        getline(cin, inputRaw);

        try {
            indexPlayerSelected = stoi(inputRaw);

            if (indexPlayerSelected == 0) return -1;
            if (indexPlayerSelected >= 1 && indexPlayerSelected <= jumlah) break;

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

    indexPlayerSelected -= 1;

    cout << endl;
    return indexPlayerSelected;
}

void showLeaderboard(Player dataPlayer[], int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak Ada Data Player!\n" << endl;
        pressEnter();
        return;
    }

    int namaTerpanjang = 0;

    struct TopPlayers {
        string nama;
        int totalGames;
        int totalWins;
        int totalDraws;
        int totalLosses;
        int score;
    };

    TopPlayers p[10];

    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            if (dataPlayer[j].score < dataPlayer[j + 1].score) {
                auto temp = dataPlayer[j];
                dataPlayer[j] = dataPlayer[j + 1];
                dataPlayer[j + 1] = temp;
            }
        }
    }
    
    int batasLoop = (jumlah < 10 ? jumlah : 10);

    for (int i = 0; i < batasLoop; i++) {
        p[i].nama = dataPlayer[i].nama;
        p[i].totalGames = dataPlayer[i].totalGames;
        p[i].totalWins = dataPlayer[i].totalWins;
        p[i].totalDraws = dataPlayer[i].totalDraws;
        p[i].totalLosses = dataPlayer[i].totalLosses;
        p[i].score = dataPlayer[i].score;
    }

    for (int i = 0; i < batasLoop; i++) {
        if ((int)p[i].nama.length() > namaTerpanjang) {
            namaTerpanjang = p[i].nama.length();
        }
    }

    cout << "===============================" << endl;
    cout << "          LEADERBOARD" << endl;
    cout << "    Top 10 Players by Score" << endl;
    cout << "===============================" << endl;

    cout << "\nRank | " << left << setw(namaTerpanjang + 10) << "Nama" << "| Score | Games |  W  |  D  |  L  " << endl;
    cout << "-----|-";
    for (int i = 0; i < namaTerpanjang + 10; i++) cout << "-";
    cout << "|-------|-------|-----|-----|-----" << endl;
    for (int i = 0; i < batasLoop; i++) {
        cout << right << setw(3) << i + 1 << "  ";
        cout << "| " << left << setw(namaTerpanjang + 10) << p[i].nama;
        cout << "| " << left << setw(6) << p[i].score;
        cout << "| " << left << setw(6) << p[i].totalGames;
        cout << "| " << left << setw(4) << p[i].totalWins;
        cout << "| " << left << setw(4) << p[i].totalDraws;
        cout << "| " << left << setw(4) << p[i].totalLosses;
        cout << endl;
    }
    cout << "\n===============================" << endl;

    cout << endl;

    pressEnter();
}

bool isValidMove(vector<vector<string>>& board, int position) {
    if (position < 1 || position > 9)
        return false;

    int row = (position - 1) / 3;
    int col = (position - 1) % 3;

    return board[row][col] == " ";
}

string currentBoard(vector<vector<string>>& board) {
    string result = "";

    for (int i = 0; i < 3; i++) {
        result += " " + board[i][0] + " | " + board[i][1] + " | " + board[i][2] + "\n";
        if (i < 2) result += "---|---|---\n";
    }

    return result;
}

bool cekWin(vector<vector<string>>& board) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != " " && board[i][0] == board [i][1] && board[i][1] == board[i][2])
            return true;
    }

    for (int j = 0; j < 3; j++) {
        if (board[0][j] != " " && board[0][j] == board [1][j] && board[1][j] == board[2][j])
            return true;
    }

    if (board[0][0] != " " && board[0][0] == board[1][1] && board[1][1] ==  board[2][2])
        return true;
    if (board[0][2] != " " && board[0][2] == board[1][1] && board[1][1] ==  board[2][0])
        return true;

    return false;
}

int pilihMode(int jumlah) {
    int modeSelected;

    cout << "=== PILIH MODE PERMAINAN ===" << endl;
    if (jumlah < 2) {
        cout << "\033[9m" << "1. VS Player" << "\033[0m" << endl;
    } else {
        cout << "1. VS Player" << endl;
    }
    cout << "2. VS Komputer" << endl;
    cout << "3. Keluar" << endl;

    string inputRaw;

    while (true) {
        cout << "\nPilihan Anda: ";
        getline(cin, inputRaw);

        try {
            modeSelected = stoi(inputRaw);

            if (modeSelected == 3) return -1;
            if (modeSelected == 1 && jumlah < 2) {
                cout << "\nTidak Dapat VS Player! Harap Masukkan Player Baru!\n" << endl;
                pressEnter();
                return -1;
            }
            if (modeSelected >= 1 && modeSelected < 3) break;

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

    // cin.ignore();

    cout << "\nMode VS " << (modeSelected == 1 ? "Player" : "Komputer") << " Dipilih!\n" << endl;

    return modeSelected;
}

void gameplayPVComp(Player dataPlayer[], int indexPlayer, int jumlah) {
    char isRestart;

    do {
        clearScreen();
        vector<vector<string>> board(3, vector<string>(3, " "));
        int move = 1;

        cout << "⚔️ " << dataPlayer[indexPlayer].nama << " VS Komputer ⚔️\n" << endl;
        cout << left << setw(12) << dataPlayer[indexPlayer].nama << ": \033[31mX\033[0m" << endl;
        cout << left << setw(12) << "Komputer" << ": \033[34mO\033[0m" << endl;
        cout << endl;

        cout << "================================" << endl;
        cout << "        TIC TAC TOE GAME" << endl;
        cout << "================================" << endl;

        cout << "\nPanduan Posisi:" << endl;
        cout << " 1 | 2 | 3 " << endl;
        cout << "---|---|---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---|---|---" << endl;
        cout << " 7 | 8 | 9 " << endl << endl;

        while(!cekWin(board) && move <= 9) {
            string symbol = (move % 2 == 1 ? "\033[31mX\033[0m" : "\033[34mO\033[0m");
            if (move % 2 == 1) {
                int cellSelected;

                cout << endl << currentBoard(board) << endl;
                cout << "Giliran Anda (X)" << endl;
                cout << "Masukkan Posisi (1-9): ";
                cin >> cellSelected;

                while (!isValidMove(board, cellSelected) || cin.fail()) {
                    cout << "\nInput Tidak Valid!" << endl;
                    cout << "Masukkan Posisi (1-9): ";
                    cin >> cellSelected;
                }

                cin.ignore();
                board[(cellSelected - 1) / 3][(cellSelected - 1) % 3] = symbol;

            } else {
                srand(time(0));

                int compSelect = rand() % 10;

                while (!isValidMove(board, compSelect)) {
                    compSelect = rand() % 10;
                }

                cout << endl << currentBoard(board) << endl;

                cout << "Komputer sedang berpikir";
                flush(cout);

                for (int i = 0; i < 3; i++) {
                    this_thread::sleep_for(chrono::seconds(1));
                    cout << (i == 2 ? ".\n" : ".");
                    flush(cout);
                }

                cout << "Komputer memilih posisi: " << compSelect << endl;

                board[(compSelect - 1) / 3][(compSelect - 1) % 3] = symbol;
            }
            move++;
        }

        cout << endl << currentBoard(board) << endl;

        string hasil;
        int win = 0, draw = 0, lose = 0;

        if (cekWin(board)) {
            if ((move - 1) % 2 != 0) {
                cout << "\n🎉 ANDA MENANG! 🎉" << endl;
                hasil = "MENANG";
                win++;
            } else {
                cout << "\n💻 KOMPUTER MENANG! 💻" << endl;
                hasil = "KALAH";
                lose++;
            }
        } else {
            cout << "\nSERI! Tidak ada yang menang." << endl;
            hasil = "SERI";
            draw++;
        }

        int point = (hasil == "MENANG" ? 3 : hasil == "SERI" ? 1 : 0);

        dataPlayer[indexPlayer].totalGames++;
        dataPlayer[indexPlayer].totalWins += win;
        dataPlayer[indexPlayer].totalDraws += draw;
        dataPlayer[indexPlayer].totalLosses += lose;
        dataPlayer[indexPlayer].score += point;

        cout << "\n================================" << endl;
        cout << "       HASIL PERTANDINGAN" << endl;
        cout << "================================" << endl;
        cout << "Hasil: " << hasil << endl;
        cout << "Score yang didapat: +" << point << " poin" << endl;

        cout << "\nStatistik " << dataPlayer[indexPlayer].nama << ":" << endl;
        cout << "- Total Games: " << dataPlayer[indexPlayer].totalGames << endl;
        cout << "- Wins: " << dataPlayer[indexPlayer].totalWins << endl;
        cout << "- Draws: " << dataPlayer[indexPlayer].totalDraws << endl;
        cout << "- Losses: " << dataPlayer[indexPlayer].totalLosses << endl;
        cout << "- Total Score: " << dataPlayer[indexPlayer].score << endl;

        updateData(dataPlayer, jumlah);

        cout << "\nData telah disimpan ke file players.txt" << endl;

        cout << "\nMain Lagi? (y/n): ";
        cin >> isRestart;
    } while(isRestart == 'y' || isRestart == 'Y');
}

void gameplayPVP(Player dataPlayer[], int p1, int p2, int jumlah) {
    char isRestart;

    do {
        clearScreen();
        vector<vector<string>> board(3, vector<string>(3, " "));
        int move = 1;

        int namaTerpanjang = dataPlayer[p1].nama.length();
        if ((int)dataPlayer[p2].nama.length() > namaTerpanjang) {
            namaTerpanjang = dataPlayer[p2].nama.length();
        }

        cout << "⚔️ " << dataPlayer[p1].nama << " VS " << dataPlayer[p2].nama << " ⚔️\n" << endl;
        cout << left << setw(namaTerpanjang + 4) << dataPlayer[p1].nama << ": \033[31mX\033[0m" << endl;
        cout << left << setw(namaTerpanjang + 4) << dataPlayer[p2].nama << ": \033[34mO\033[0m" << endl;
        cout << endl;

        cout << "================================" << endl;
        cout << "        TIC TAC TOE GAME" << endl;
        cout << "================================" << endl;

        cout << "\nPanduan Posisi:" << endl;
        cout << " 1 | 2 | 3 " << endl;
        cout << "---|---|---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---|---|---" << endl;
        cout << " 7 | 8 | 9 " << endl << endl;

        while (!cekWin(board) && move <= 9) {
            string symbol = (move % 2 == 1 ? "\033[31mX\033[0m" : "\033[34mO\033[0m");
            int cell;
            cout << endl << currentBoard(board) << endl;
            cout << "Giliran " << dataPlayer[(move % 2 == 1 ? p1 : p2)].nama << " (" << symbol << ")" << endl;
            cout << "Masukkan Posisi (1-9): ";
            cin >> cell;

            while (!isValidMove(board, cell) || cin.fail()) {
                cout << "Input Tidak Valid!" << endl;
                cout << "Masukkan Posisi (1-9): ";
                cin >> cell;
            }

            cin.ignore();
            board[(cell - 1) / 3][(cell - 1) % 3] = symbol;

            move++;
        }

        cout << endl << currentBoard(board) << endl;
        int winner;

        if (cekWin(board)) {
            if ((move - 1) % 2 != 0) {
                cout << "\n🎉 " << dataPlayer[p1].nama << " (\033[31mX\033[0m) MENANG! 🎉" << endl;
                dataPlayer[p1].totalWins++;
                dataPlayer[p1].score += 3;

                dataPlayer[p2].totalLosses++;

                winner = p1;
            } else {
                cout << "\n🎉 " << dataPlayer[p2].nama << " (\033[34mX\033[0m) MENANG! 🎉" << endl;
                dataPlayer[p2].totalWins++;
                dataPlayer[p2].score += 3;

                dataPlayer[p1].totalLosses++;

                winner = p2;
            }
        } else {
            cout << "\nGAME SERI" << endl;
            dataPlayer[p1].totalDraws++;
            dataPlayer[p1].score++;

            dataPlayer[p2].totalDraws++;
            dataPlayer[p2].score++;
        }

        dataPlayer[p1].totalGames++;
        dataPlayer[p2].totalGames++;

        cout << "\n================================" << endl;
        cout << "       HASIL PERTANDINGAN" << endl;
        cout << "================================" << endl;

        if (!cekWin(board)) {
            cout << "Pertandingan Seri!" << endl;
            cout << "Score Masing-Masing Player +1 poin" << endl;

            cout << "\nStatistik " << dataPlayer[p1].nama << ":" << endl;
            cout << "- Total Games:" << dataPlayer[p1].totalGames << endl;
            cout << "- Wins:" << dataPlayer[p1].totalWins << endl;
            cout << "- Draws:" << dataPlayer[p1].totalDraws << endl;
            cout << "- Losses:" << dataPlayer[p1].totalLosses << endl;
            cout << "- Total Score:" << dataPlayer[p1].score << endl;

            cout << "\nStatistik " << dataPlayer[p2].nama << ":" << endl;
            cout << "- Total Games:" << dataPlayer[p2].totalGames << endl;
            cout << "- Wins:" << dataPlayer[p2].totalWins << endl;
            cout << "- Draws:" << dataPlayer[p2].totalDraws << endl;
            cout << "- Losses:" << dataPlayer[p2].totalLosses << endl;
            cout << "- Total Score:" << dataPlayer[p2].score << endl;
        } else {
            cout << "Hasil untuk " << dataPlayer[winner].nama << ": MENANG" << endl;
            cout << "Score yang didapat: +3 poin" << endl;

            cout << "\nStatistik " << dataPlayer[winner].nama << ":" << endl;
            cout << "- Total Games:" << dataPlayer[winner].totalGames << endl;
            cout << "- Wins:" << dataPlayer[winner].totalWins << endl;
            cout << "- Draws:" << dataPlayer[winner].totalDraws << endl;
            cout << "- Losses:" << dataPlayer[winner].totalLosses << endl;
            cout << "- Total Score:" << dataPlayer[winner].score << endl;
        }

        updateData(dataPlayer, jumlah);

        cout << "\nData telah disimpan ke file players.txt" << endl;

        cout << "\nMain lagi? (y/n): ";
        cin >> isRestart;
    } while (isRestart == 'y' || isRestart == 'Y');
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    int roomPlayer = 100, pilihMenu;
    Player dataPlayer[roomPlayer];
    const string FILENAME = "players.txt";

    namespace fs = filesystem;
    fs::current_path(fs::path(__FILE__).parent_path());

    bool fileIsChecked = false;

    do {
        clearScreen();
        int jumlahPlayer = 0;
        loadData(dataPlayer, jumlahPlayer);

        cout << "================================" << endl;
        cout << "        TIC TAC TOE GAME" << endl;
        cout << "================================" << endl;

        if (!fileIsChecked) {
            ifstream file(FILENAME);

            if (!file.is_open()) {
                cout << "\nFile tidak ditemukan, membuat file baru..." << endl;
                ofstream newFile(FILENAME);
                newFile.close();
            } else {
                cout << "\nFile ditemukan, data sudah dibaca..." << endl;
                file.close();
            }

            fileIsChecked = true;
        }

        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Player Baru" << endl;
        cout << "2. Pilih Player yang sudah ada" << endl;
        cout << "3. Lihat Leaderboard" << endl;
        cout << "4. Keluar" << endl;
        cout << "\nPilihan Anda: ";
        cin >> pilihMenu;

        while (pilihMenu < 1 || pilihMenu > 4 || cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nInput tidak valid!" << endl;
            cout << "Pilihan Anda: ";
            cin >> pilihMenu;
        }

        cout << endl;
        cin.ignore(1000, '\n');

        switch(pilihMenu) {
            case 1:
                if (jumlahPlayer < roomPlayer) {
                    clearScreen();
                    registrasiPlayer(dataPlayer, jumlahPlayer);
                } else {
                    cout << "Kapasitas Player Penuh! Tidak Dapat Menambahkan Player.\n" << endl;
                    pressEnter();
                    break;
                }
                pressEnter();
                break;

            case 2: {
                clearScreen();
                int selectedPlayer1 = pilihPlayer(dataPlayer, jumlahPlayer);
                if (selectedPlayer1 == -1) break;
                
                clearScreen();
                int gameMode = pilihMode(jumlahPlayer);
                if (gameMode == -1) break;
                if (gameMode == 1) {
                    cout << "--- Pilih Lawan (Player 2) ---\n" << endl;
                    int selectedPlayer2 = pilihPlayer2(dataPlayer, jumlahPlayer, selectedPlayer1);

                    if (selectedPlayer2 == -1) {
                        break;
                    }

                    if (selectedPlayer2 == selectedPlayer1) {
                        cout << "Kesalahan: Player tidak bisa melawan diri sendiri!\n" << endl;
                        pressEnter();
                        break;
                    }
                    
                    cout << dataPlayer[selectedPlayer2].nama << " Akan Menjadi Player 2\n" << endl;
                    pressEnter();
                    clearScreen();
                    gameplayPVP(dataPlayer, selectedPlayer1, selectedPlayer2, jumlahPlayer);
                } else {
                    clearScreen();
                    gameplayPVComp(dataPlayer, selectedPlayer1, jumlahPlayer);
                }
                pressEnter();
                break;
            }
            case 3:
                clearScreen();
                showLeaderboard(dataPlayer, jumlahPlayer);
                break;
            case 4:
                cout << "Terimakasih Telah Memainkan Tic-Tac-Toe" << endl;
                break;
        }
    } while(pilihMenu != 4);

    return 0;

}
