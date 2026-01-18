#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

struct Player
{
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

vector<Player> players;
Player *currentPlayer = NULL;
const string FILE_NAME = "players.txt";

void pause()
{
    cout << "\nTekan ENTER buat lanjut...";
    cin.ignore(1000, '\n');
    cin.get();
}

void header()
{
    cout << "\n====================================\n";
    cout << "        TIC TAC TOE GAME\n";
    cout << "====================================\n\n";
}

void loadPlayers()
{
    ifstream file(FILE_NAME.c_str());
    if (!file)
        return;

    Player p;
    while (file >> p.nama >> p.totalGames >> p.totalWins >> p.totalDraws >> p.totalLosses >> p.score)
    {
        players.push_back(p);
    }
    file.close();
}

void savePlayers()
{
    ofstream file(FILE_NAME.c_str());
    for (size_t i = 0; i < players.size(); i++)
    {
        file << players[i].nama << " "
             << players[i].totalGames << " "
             << players[i].totalWins << " "
             << players[i].totalDraws << " "
             << players[i].totalLosses << " "
             << players[i].score << endl;
    }
    file.close();
}

void showStats(Player &p)
{
    cout << "\nStatistik " << p.nama << ":\n";
    cout << "-Total Game : " << p.totalGames << endl;
    cout << "-Win        : " << p.totalWins << endl;
    cout << "-Draw       : " << p.totalDraws << endl;
    cout << "-Lose       : " << p.totalLosses << endl;
    cout << "Score Total : " << p.score << endl;
}

void newPlayer()
{
    cout << "\n=== PLAYER BARU ===\n";
    cout << "Masukin nama kamu: ";

    Player p;
    cin >> p.nama;
    p.totalGames = p.totalWins = p.totalDraws = p.totalLosses = p.score = 0;

    players.push_back(p);
    currentPlayer = &players.back();

    cout << "\nHOREEE! Player berhasil dibuat \n";
    cout << "Selamat datang, " << p.nama << "!\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

void choosePlayer()
{
    header();
    if (players.empty())
    {
        cout << "Belum ada player nih, bikin dulu ya.\n";
        pause();
        return;
    }

    cout << "=== DAFTAR PLAYER ===\n";
    cout << left << setw(4) << "No"
         << "| " << setw(15) << "Nama"
         << "| " << setw(6) << "Skor"
         << "| " << setw(6) << "Main"
         << "| " << setw(3) << "W"
         << "| " << setw(3) << "D"
         << "| " << setw(3) << "L" << endl;
    cout << string(55, '-') << endl;

    for (size_t i = 0; i < players.size(); i++)
    {
        cout << left << setw(4) << i + 1
             << "| " << setw(15) << players[i].nama
             << "| " << setw(6) << players[i].score
             << "| " << setw(6) << players[i].totalGames
             << "| " << setw(3) << players[i].totalWins
             << "| " << setw(3) << players[i].totalDraws
             << "| " << setw(3) << players[i].totalLosses << endl;
    }

    cout << "\nPilih nomor player (0 buat balik): ";
    int c;
    cin >> c;
    if (c < 1 || c > (int)players.size())
    {
        currentPlayer = NULL;
        return;
    }

    currentPlayer = &players[c - 1];
    cout << "\nWelcome back, " << currentPlayer->nama << "!\n";
    cin.ignore();
    pause();
}

void leaderboard()
{
    header();
    if (players.empty())
    {
        cout << "Leaderboard masih kosong\n";
        pause();
        return;
    }

    vector<Player> temp = players;
    for (size_t i = 0; i < temp.size(); i++)
    {
        for (size_t j = i + 1; j < temp.size(); j++)
        {
            if (temp[j].score > temp[i].score)
                swap(temp[i], temp[j]);
        }
    }

    cout << "============================================\n";
    cout << "              LEADERBOARD\n";
    cout << "============================================\n";
    cout << left << setw(6) << "Rank"
         << "| " << setw(15) << "Nama"
         << "| " << setw(6) << "Skor"
         << "| " << setw(6) << "Main"
         << "| W | D | L\n";
    cout << string(55, '-') << endl;

    for (size_t i = 0; i < temp.size() && i < 10; i++)
    {
        cout << left << setw(6) << i + 1
             << "| " << setw(15) << temp[i].nama
             << "| " << setw(6) << temp[i].score
             << "| " << setw(6) << temp[i].totalGames
             << "| " << setw(2) << temp[i].totalWins
             << " | " << setw(2) << temp[i].totalDraws
             << " | " << setw(2) << temp[i].totalLosses << endl;
    }
    pause();
}

bool checkWin(const vector<char> &b, char m)
{
    int w[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
        if (b[w[i][0]] == m && b[w[i][1]] == m && b[w[i][2]] == m)
            return true;
    return false;
}

bool isboardFull(const vector<char> &b)
{
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
            return false;
    return true;
}

void displayGuide()
{
    cout << "Petunjuk posisi:\n";
    cout << " 1 | 2 | 3\n---|---|---\n";
    cout << " 4 | 5 | 6\n---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void displayBoard(const vector<char> &b)
{
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

void cetakHasil(string hasil, string poin)
{
    cout << "====================================\n";
    cout << "         HASIL AKHIR PERMAINAN      \n";
    cout << "====================================\n";
    cout << "Hasil game : " << hasil << endl;
    cout << "Bonus skor : " << poin << endl;
    showStats(*currentPlayer);
    cout << "\nData otomatis disimpan \n";
}

void playerVsComputer()
{
    vector<char> board(9, ' ');
    header();
    displayGuide();
    displayBoard(board);

    string res = "", pts = "";

    while (true)
    {
        int pos;
        cout << "Giliran kamu (X)\nPilih posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ')
            continue;

        board[pos - 1] = 'X';
        displayBoard(board);

        if (checkWin(board, 'X'))
        {
            cout << "Mantap! Kamu menang \n";
            currentPlayer->totalWins++;
            currentPlayer->score += 3;
            res = "MENANG";
            pts = "+3 poin";
            break;
        }

        if (isboardFull(board))
        {
            cout << "Seri Dong Kita \n";
            currentPlayer->totalDraws++;
            currentPlayer->score += 1;
            res = "SERI";
            pts = "+1 poin";
            break;
        }

        cout << "Komputer mikir dulu...\n";
        int c;
        do
        {
            c = rand() % 9;
        } while (board[c] != ' ');
        board[c] = 'O';
        cout << "Komputer pilih posisi: " << c + 1 << endl;
        displayBoard(board);

        if (checkWin(board, 'O'))
        {
            cout << " Yah Komputer menang \n";
            currentPlayer->totalLosses++;
            res = "KALAH";
            pts = "+0 poin";
            break;
        }
    }
    currentPlayer->totalGames++;
    savePlayers();
    cetakHasil(res, pts);
}

void playerVsPlayer()
{
    vector<char> board(9, ' ');
    char current = 'X';
    header();
    displayGuide();
    displayBoard(board);

    string res = "", pts = "";

    while (true)
    {
        int pos;
        cout << "Giliran Player " << current << "\nPilih posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ')
            continue;

        board[pos - 1] = current;
        displayBoard(board);

        if (checkWin(board, current))
        {
            cout << "Player " << current << " menang!\n";
            if (current == 'X')
            {
                currentPlayer->totalWins++;
                currentPlayer->score += 3;
                res = "MENANG";
                pts = "+3 poin";
            }
            else
            {
                currentPlayer->totalLosses++;
                res = "KALAH";
                pts = "+0 poin";
            }
            break;
        }

        if (isboardFull(board))
        {
            cout << "Permainan berakhir seri \n";
            currentPlayer->totalDraws++;
            currentPlayer->score += 1;
            res = "SERI";
            pts = "+1 poin";
            break;
        }
        current = (current == 'X') ? 'O' : 'X';
    }
    currentPlayer->totalGames++;
    savePlayers();
    cetakHasil(res, pts);
}

void pilihModeGame()
{
    char ulang;
    do
    {
        system("cls");
        header();
        int mode;
        cout << "Hai, " << currentPlayer->nama << " ??\n";
        cout << "Pilih mode main:\n";
        cout << "1. Vs Player\n";
        cout << "2. Vs Computer\n";
        cout << "Pilihan: ";
        cin >> mode;

        if (mode == 1)
            playerVsPlayer();
        else if (mode == 2)
            playerVsComputer();

        cout << "\nMain lagi nggak? (y/n): ";
        cin >> ulang;
    } while (ulang == 'y' || ulang == 'Y');
}

int main()
{
    srand(time(0));
    loadPlayers();

    while (true)
    {
        system("cls");
        header();
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Buat player baru\n";
        cout << "2. Pilih player\n";
        cout << "3. Lihat leaderboard\n";
        cout << "4. Keluar\n\n";
        cout << "Pilihan kamu: ";

        int m;
        if (!(cin >> m))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();

        if (m == 1)
        {
            newPlayer();
            if (currentPlayer)
                pilihModeGame();
        }
        else if (m == 2)
        {
            choosePlayer();
            if (currentPlayer)
                pilihModeGame();
        }
        else if (m == 3)
        {
            leaderboard();
        }
        else if (m == 4)
        {
            cout << "\nYEAYY! Makasih udah main \n";
            break;
        }
    }
    return 0;
}