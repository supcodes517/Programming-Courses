#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/* ================= STRUCT ================= */

struct Player
{
    string nama;
    int totalGames;
    int totalWins;
    int totalDraws;
    int totalLosses;
    int score;
};

/* ================= GLOBAL ================= */

vector<Player> players;
Player *currentPlayer = nullptr;
const string FILE_NAME = "players.txt";

/* ================= UTIL ================= */

void pause()
{
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(1000, '\n');
    cin.get();
}

void header()
{
    cout << "\n================================\n";
    cout << "     TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

/* ================= FILE ================= */

void loadPlayers()
{
    ifstream file(FILE_NAME.c_str());
    if (!file)
    {
        cout << "File player tidak ditemukan. Membuat file baru...\n\n";
        return;
    }

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
    for (int i = 0; i < (int)players.size(); i++)
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

/* ================= PLAYER ================= */

void showStats(Player &p)
{
    cout << "Statistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.totalGames << endl;
    cout << "- Wins: " << p.totalWins << endl;
    cout << "- Draws: " << p.totalDraws << endl;
    cout << "- Losses: " << p.totalLosses << endl;
    cout << "- Total Score: " << p.score << endl;
}

void newPlayer()
{
    cout << "\n";

    cout << "=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";

    Player p;
    cin >> p.nama;
    p.totalGames = p.totalWins = p.totalDraws = p.totalLosses = p.score = 0;

    players.push_back(p);
    currentPlayer = &players[players.size() - 1];

    cout << "\nPlayer baru berhasil dibuat\n";
    cout << "Selamat datang, " << p.nama << "!\n\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

void choosePlayer()
{
    header();
    cout << "=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           | Score | Games | W  | D  | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";

    for (int i = 0; i < (int)players.size(); i++)
    {
        cout << i + 1 << "  | " << players[i].nama;
        for (int s = players[i].nama.length(); s < 15; s++)
            cout << " ";
        cout << "| " << players[i].score
             << "     |" << players[i].totalGames
             << "      |" << players[i].totalWins
             << "   | " << players[i].totalDraws
             << "  | " << players[i].totalLosses << endl;
    }

    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    int c;
    cin >> c;
    if (c < 1 || c > (int)players.size())
        return;

    currentPlayer = &players[c - 1];
    cout << "\nPlayer dipilih:  " << currentPlayer->nama << "\n\n";
    cout << "Selamat datang kembali, " << currentPlayer->nama << "!\n\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

/* ================= LEADERBOARD ================= */

void leaderboard()
{
    header();

    // bubble sort by score
    vector<Player> temp = players;
    for (int i = 0; i < (int)temp.size(); i++)
    {
        for (int j = i + 1; j < (int)temp.size(); j++)
        {
            if (temp[j].score > temp[i].score)
            {
                Player t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    cout << "================================\n";
    cout << "        LEADERBOARD\n";
    cout << "  Top 10 Players by Score\n";
    cout << "================================\n\n";

    cout << "Rank | Nama           | Score | Games | W  | D  | L\n";
    cout << "-----|----------------|-------|-------|----|----|----\n";

    for (int i = 0; i < (int)temp.size() && i < 10; i++)
    {
        cout << " " << i + 1 << "   | " << temp[i].nama;
        for (int s = temp[i].nama.length(); s < 15; s++)
            cout << " ";
        cout << "| " << temp[i].score
             << "     | " << temp[i].totalGames
             << "     | " << temp[i].totalWins
             << "  | " << temp[i].totalDraws
             << "  | " << temp[i].totalLosses << endl;
    }
    pause();
}

/* ================= TIC TAC TOE GAME ================= */

bool checkWin(vector<char> &b, char m)
{
    int w[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
        if (b[w[i][0]] == m && b[w[i][1]] == m && b[w[i][2]] == m)
            return true;
    return false;
}

bool isboardFull(vector<char> &b)
{
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
            return false;
    return true;
}

void displayGuide()
{
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void displayBoard(vector<char> &b)
{
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

/* ================= VS COMPUTER ================= */

void playVsComputer()
{
    vector<char> board(9, ' ');
    header();
    displayGuide();
    displayBoard(board);

    while (true)
    {
        int pos;
        cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ')
            continue;

        board[pos - 1] = 'X';
        displayBoard(board);

        if (checkWin(board, 'X'))
        {
            cout << " ANDA MENANG! \n\n";
            cout << "==============================" << endl;
            cout << "      HASIL PERTANDINGAN      " << endl;
            cout << "==============================" << endl;
            cout << "Hasil:  MENANG" << endl;
            cout << "Score yang didapat: +3 poin\n\n";
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            currentPlayer->totalWins++;
            currentPlayer->score += 3;
            break;
        }

        if (isboardFull(board))
        {
            cout << "SERI! Tidak ada yang menang.\n\n";
            cout << "==============================" << endl;
            cout << "      HASIL PERTANDINGAN      " << endl;
            cout << "==============================" << endl;
            cout << "Hasil: SERI" << endl;
            cout << "Score yang didapat: +1 poin\n\n";
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            currentPlayer->totalDraws++;
            currentPlayer->score += 1;
            break;
        }

        cout << "Komputer sedang berpikir...\n";
        int c;
        for (c = 0; c < 9; c++)
            if (board[c] == ' ')
                break;

        cout << "Komputer memilih posisi: " << c + 1 << endl;
        board[c] = 'O';
        displayBoard(board);

        if (checkWin(board, 'O'))
        {
            cout << " KOMPUTER MENANG! \n\n";
            cout << "==============================" << endl;
            cout << "      HASIL PERTANDINGAN      " << endl;
            cout << "==============================" << endl;
            cout << "Hasil:  KALAH" << endl;
            cout << "Score yang didapat: +0 poin\n\n"
                 << endl;
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";
            currentPlayer->totalLosses++;
            break;
        }
    }

    currentPlayer->totalGames++;
    savePlayers();
}

/* ================= VS PLAYER ================= */

void playVsPlayer()
{
    vector<char> board(9, ' ');
    char current = 'X';

    header();
    displayGuide();
    displayBoard(board);

    while (true)
    {
        int pos;
        cout << "Giliran Player " << current << "\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ')
            continue;

        board[pos - 1] = current;
        displayBoard(board);

        if (checkWin(board, 'X'))
        {
            cout << " Player " << current << " MENANG! \n\n";
            cout << "==============================" << endl;
            cout << "      HASIL PERTANDINGAN      " << endl;
            cout << "==============================" << endl;
            cout << "Hasil untuk " << currentPlayer->nama << ": menang\n";
            cout << "Score yang didapat: +3 poin\n\n";
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";

            if (current == 'X')
                currentPlayer->totalWins++;
            else
                currentPlayer->totalLosses++;
            currentPlayer->score += 3;
            break;
        }

        if (checkWin(board, 'O'))
        {
            cout << " Player " << current << " MENANG! \n\n";
            cout << "==============================" << endl;
            cout << "      HASIL PERTANDINGAN      " << endl;
            cout << "==============================" << endl;
            cout << "Hasil untuk " << currentPlayer->nama << ": KALAH\n";
            cout << "Score yang didapat: +0 poin\n\n"
                 << endl;
            showStats(*currentPlayer);
            cout << "\nData telah disimpan ke file\n\n";

            if (current == 'X')
                currentPlayer->totalWins++;
            else
                currentPlayer->totalLosses++;
            break;
        }

        if (isboardFull(board))
        {
            cout << "SERI! Tidak ada yang menang.\n";
            currentPlayer->totalDraws++;
            currentPlayer->score += 1;
            break;
        }

        current = (current == 'X') ? 'O' : 'X';
    }

    currentPlayer->totalGames++;
    savePlayers();
}

/* ================= PILIH GAME MODE ================= */

void pilihModeGame()
{
    char mainlagi;

    do
    {
        int choise;
        system("cls");

        header();
        cout << "\n=== PILIH MODE PERMAINAN ===\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n";
        cout << "Pilihan Anda: ";
        cin >> choise;

        fflush(stdin);

        if (choise == 1)
        {
            playVsPlayer();
        }
        else if (choise == 2)
        {
            playVsComputer();
        }

        cout << "Main lagi? (y/n): ";
        cin >> mainlagi;
        fflush(stdin);

        if (mainlagi == 'n' || mainlagi == 'N')
        {
            cout << "\nTerima kasih telah bermain, " << currentPlayer->nama << "!" << endl;
            pause();
        }

    } while (mainlagi == 'y' || mainlagi == 'y');
}

/* ================= MAIN ================= */

int main()
{
    srand(time(0));
    loadPlayers();

    while (true)
    {
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
            cout << "\nTerima kasih telah bermain Tic Tac Toe!\n";
            break;
        }
        else
        {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}