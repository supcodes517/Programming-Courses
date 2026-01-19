#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Player
{
    string nama;
    int games;
    int wins;
    int draws;
    int losses;
    int score;
};

vector<Player> players;
Player *currentPlayer = NULL;
const string FILE_NAME = "players.txt";

void pause()
{
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void start()
{
    cout << "\nTekan Enter untuk Memulai...";
    cin.get();
}

void header()
{
    cout << "\n================================\n";
    cout << "       TIC TAC TOE GAME\n";
    cout << "================================\n\n";
}

void loadPlayers()
{
    ifstream file(FILE_NAME.c_str());
    if (!file)
    {
        cout << "File player tidak ditemukan. Membuat file baru...\n\n";
        return;
    }

    Player p;
    while (file >> p.nama >> p.games >> p.wins >> p.draws >> p.losses >> p.score)
    {
        players.push_back(p);
    }
    file.close();
}

void savePlayers()
{
    ofstream file(FILE_NAME.c_str());
    for (int i = 0; i < players.size(); i++)
    {
        file << players[i].nama << " "
             << players[i].games << " "
             << players[i].wins << " "
             << players[i].draws << " "
             << players[i].losses << " "
             << players[i].score << endl;
    }
    file.close();
}

void showStats(Player &p)
{
    cout << "Statistik " << p.nama << ":\n";
    cout << "- Total Games: " << p.games << endl;
    cout << "- Wins: " << p.wins << endl;
    cout << "- Draws: " << p.draws << endl;
    cout << "- Losses: " << p.losses << endl;
    cout << "- Total Score: " << p.score << endl;
}

void newPlayer()
{
    header();
    cout << "=== REGISTRASI PLAYER BARU ===\n";
    cout << "Masukkan nama Anda: ";

    Player p;
    cin >> p.nama;
    p.games = p.wins = p.draws = p.losses = p.score = 0;

    players.push_back(p);
    currentPlayer = &players[players.size() - 1];

    cout << "\nPlayer baru berhasil dibuat!\n";
    cout << "Selamat datang, " << p.nama << "!\n\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

void choosePlayer()
{
    header();
    cout << "=== DAFTAR PLAYER ===\n";
    cout << "No | Nama           |  Skor | Games |  W |  D | L\n";
    cout << "---|----------------|-------|-------|----|----|---\n";

    for (int i = 0; i < players.size(); i++)
    {
        cout << i + 1 << "  | " << players[i].nama;
        for (int s = players[i].nama.length(); s < 15; s++)
            cout << " ";
        cout << "| " << players[i].score
             << "     | " << players[i].games
             << "     | " << players[i].wins
             << "  | " << players[i].draws
             << "  | " << players[i].losses << endl;
    }

    cout << "\nPilih player (1-" << players.size() << ") atau 0 untuk kembali: ";
    int c;
    cin >> c;
    if (c < 1 || c > players.size())
        return;

    currentPlayer = &players[c - 1];
    cout << "\nPlayer dipilih:  " << currentPlayer->nama << "\n\n";
    cout << "Selamat Datang Kembali " << currentPlayer->nama << "\n\n";
    showStats(*currentPlayer);
    cin.ignore();
    pause();
}

void leaderboard()
{
    header();

    // bubble sort by score
    vector<Player> temp = players;
    for (int i = 0; i < temp.size(); i++)
    {
        for (int j = i + 1; j < temp.size(); j++)
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

    cout << "no | Nama             | Skor | Games| W  |  D | L\n";
    cout << "---|------------------|------|------|----|----|----\n";

    for (int i = 0; i < temp.size() && i < 10; i++)
    {
        cout << " " << i + 1 << " | " << temp[i].nama;
        for (int s = temp[i].nama.length(); s < 15; s++)
            cout << " ";
        cout << "  | " << temp[i].score
             << "    | " << temp[i].games
             << "    | " << temp[i].wins
             << "  | " << temp[i].draws
             << "  | " << temp[i].losses << endl;
    }
    pause();
}

bool checkWin(vector<char> &b, char m)
{
    int w[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
        if (b[w[i][0]] == m && b[w[i][1]] == m && b[w[i][2]] == m)
            return true;
    return false;
}

bool boardFull(vector<char> &b)
{
    for (int i = 0; i < 9; i++)
        if (b[i] == ' ')
            return false;
    return true;
}

void showGuide()
{
    cout << "Panduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

void showBoard(vector<char> &b)
{
    cout << " " << b[0] << " | " << b[1] << " | " << b[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[3] << " | " << b[4] << " | " << b[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << b[6] << " | " << b[7] << " | " << b[8] << "\n\n";
}

void vskomputer()
{
    vector<char> board(9, ' ');
    header();
    showGuide();
    showBoard(board);

    while (true)
    {
        int pos;
        cout << "Giliran Anda (X)\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ')
            continue;

        board[pos - 1] = 'X';
        showBoard(board);

        if (checkWin(board, 'X'))
        {
            cout << "!!ANDA MENANG!!\n";
            currentPlayer->wins++;
            currentPlayer->score += 3;
            cout << "Skor yang didapat = +3\n";
            cout << endl;
            showStats(*currentPlayer);
            break;
        }

        if (boardFull(board))
        {
            cout << "SERI! Tidak ada yang menang.\n";
            currentPlayer->draws++;
            currentPlayer->score += 1;
            cout << "skor yang didapat = +1";
            cout << endl;
            showStats(*currentPlayer);
            break;
        }

        cout << "Komputer sedang berpikir...\n";
        int c;
        for (c = 0; c < 9; c++)
            if (board[c] == ' ')
                break;

        cout << "Komputer memilih posisi: " << c + 1 << endl;
        board[c] = 'O';
        showBoard(board);

        if (checkWin(board, 'O'))
        {
            cout << "KOMPUTER MENANG! \n";
            currentPlayer->losses++;
            cout << "skor yang didapat = +0";
            cout << endl;
            showStats(*currentPlayer);
            break;
        }
    }

    currentPlayer->games++;
    savePlayers();
}

void vsPlayer()
{
    vector<char> board(9, ' ');
    char current = 'X';
    char currents = 'O';
    header();
    showGuide();
    cout << endl;
    cout << "Mode VS Player Dipilih\n";
    cout << endl;
    cout << "Player 1 = X\n";
    cout << "Player 2 = O\n";
    cout << endl;
    start();
    showBoard(board);

    while (true)
    {
        int pos;
        cout << "Giliran Player " << current << "\nMasukkan posisi (1-9): ";
        cin >> pos;
        if (pos < 1 || pos > 9 || board[pos - 1] != ' ')
            continue;

        board[pos - 1] = current;
        showBoard(board);

        if (checkWin(board, 'X'))
        {
            cout << " Player " << current << " MENANG! \n";
            if (current == 'X')
                currentPlayer->wins++;
            else
                currentPlayer->losses++;
            currentPlayer->score += 3;
            cout << "===============================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "===============================\n";
            cout << "hasil untuk " << currentPlayer->nama << " : Menang" << endl;
            cout << "Skor yang didapat = +3\n";
            showStats(*currentPlayer);
            cin.ignore();
            pause();
            break;
        }
        if (checkWin(board, 'O'))
        {
            cout << " Player " << currents << " MENANG! \n";
            if (current == 'X')
                currentPlayer->wins++;
            else
                currentPlayer->losses++;
            currentPlayer->score += 0;
            cout << "===============================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "===============================\n";
            cout << "hasil untuk " << currentPlayer->nama << " : Kalah" << endl;
            cout << "Skor yang didapat = +0\n";
            showStats(*currentPlayer);
            cin.ignore();
            pause();
            break;
        }

        if (boardFull(board))
        {
            cout << "SERI! Tidak ada yang menang.\n";
            currentPlayer->draws++;
            currentPlayer->score += 1;
            cout << "===============================\n";
            cout << "       HASIL PERTANDINGAN\n";
            cout << "===============================\n";
            cout << "hasil untuk " << currentPlayer->nama << " : SERI!!" << endl;
            cout << "Skor yang didapat = +1\n";
            showStats(*currentPlayer);
            cin.ignore();
            pause();
            break;
        }

        current = (current == 'X') ? 'O' : 'X';
    }

    currentPlayer->games++;
    savePlayers();
}

void pilihModeGame()
{
    char mainLagi;

    do
    {
        int pilih;
        system("cls");

        header();
        cout << "HIII " << currentPlayer->nama << endl;
        cout << "=== PILIH MODE PERMAINAN ===\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n";
        cout << "Pilihan Anda: ";
        cin >> pilih;

        fflush(stdin);

        if (pilih == 1)
        {
            vsPlayer();
        }
        else if (pilih == 2)
        {
            vskomputer();
        }

        cout << "\n===============================\n";
        cout << "Main lagi? (y/n): ";
        cin >> mainLagi;
        fflush(stdin);

        if (mainLagi == 'n' || mainLagi == 'N')
        {
            cout << "\nTerima kasih telah bermain, " << currentPlayer->nama << "!" << endl;
            pause();
        }

    } while (mainLagi == 'y' || mainLagi == 'Y');
}

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
