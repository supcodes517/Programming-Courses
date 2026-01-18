
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Fungsi untuk menampilkan board
void displayBoard(char board[3][3]) {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << " " << board[i][j];
            if (j < 2) cout << " |";
        }
        cout << "\n";
        if (i < 2) cout << " ---|---|---\n";
    }
    cout << "\n";
}

// Fungsi untuk menampilkan panduan posisi
void displayGuide() {
    cout << "\nPanduan Posisi:\n";
    cout << " 1 | 2 | 3\n";
    cout << "---|---|---\n";
    cout << " 4 | 5 | 6\n";
    cout << "---|---|---\n";
    cout << " 7 | 8 | 9\n\n";
}

// Fungsi untuk mengecek kemenangan
bool checkWin(char board[3][3], char player) {
    // Cek baris
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    
    // Cek kolom
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player)
            return true;
    }
    
    // Cek diagonal
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    
    return false;
}

// Fungsi untuk mengecek apakah board penuh (draw)
bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Fungsi untuk mengecek apakah posisi valid
bool isValidMove(char board[3][3], int position) {
    if (position < 1 || position > 9)
        return false;
    
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    
    return board[row][col] == ' ';
}

// Fungsi untuk menempatkan tanda pada board
void makeMove(char board[3][3], int position, char player) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    board[row][col] = player;
}

// Fungsi untuk komputer memilih move (AI sederhana)
int computerMove(char board[3][3]) {
    // Cek apakah komputer bisa menang
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            // Copy board
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];
            
            makeMove(tempBoard, i, 'O');
            if (checkWin(tempBoard, 'O'))
                return i;
        }
    }
    
    // Cek apakah player bisa menang dan block
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i)) {
            char tempBoard[3][3];
            // Copy board
            for (int x = 0; x < 3; x++)
                for (int y = 0; y < 3; y++)
                    tempBoard[x][y] = board[x][y];
            
            makeMove(tempBoard, i, 'X');
            if (checkWin(tempBoard, 'X'))
                return i;
        }
    }
    
    // Coba ambil tengah
    if (isValidMove(board, 5))
        return 5;
    
    // Coba ambil sudut
    int corners[] = {1, 3, 7, 9};
    for (int i = 0; i < 4; i++) {
        if (isValidMove(board, corners[i]))
            return corners[i];
    }
    
    // Ambil posisi kosong pertama
    for (int i = 1; i <= 9; i++) {
        if (isValidMove(board, i))
            return i;
    }
    
    return -1;
}

// Fungsi untuk bermain vs Player
void playVsPlayer(char board[3][3]) {
    char currentPlayer = 'X';
    int position;
    
    while (true) {
        displayBoard(board);
        cout << "Giliran Player " << currentPlayer << "\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> position;
        
        if (!isValidMove(board, position)) {
            cout << "Posisi tidak valid! Coba lagi.\n";
            continue;
        }
        
        makeMove(board, position, currentPlayer);
        
        if (checkWin(board, currentPlayer)) {
            displayBoard(board);
            cout << "🎉 Player " << currentPlayer << " MENANG! 🎉\n";
            break;
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            break;
        }
        
        // Ganti pemain
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

// Fungsi untuk bermain vs Komputer
void playVsComputer(char board[3][3]) {
    int position;
    
    while (true) {
        // Giliran Player (X)
        displayBoard(board);
        cout << "Giliran Anda (X)\n";
        cout << "Masukkan posisi (1-9): ";
        cin >> position;
        
        if (!isValidMove(board, position)) {
            cout << "Posisi tidak valid! Coba lagi.\n";
            continue;
        }
        
        makeMove(board, position, 'X');
        
        if (checkWin(board, 'X')) {
            displayBoard(board);
            cout << "🎉 ANDA MENANG! 🎉\n";
            break;
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            break;
        }
        
        // Giliran Komputer (O)
        cout << "Komputer sedang berpikir...\n";
        int compMove = computerMove(board);
        makeMove(board, compMove, 'O');
        cout << "Komputer memilih posisi: " << compMove << "\n";
        
        if (checkWin(board, 'O')) {
            displayBoard(board);
            cout << "💻 KOMPUTER MENANG! 💻\n";
            break;
        }
        
        if (isBoardFull(board)) {
            displayBoard(board);
            cout << "SERI! Tidak ada yang menang.\n";
            break;
        }
    }
}

int main() {
    srand(time(0));
    
    char playAgain;
    
    do {
        // Inisialisasi board 2D array
        char board[3][3] = {
            {' ', ' ', ' '},
            {' ', ' ', ' '},
            {' ', ' ', ' '}
        };
        
        cout << "\n================================\n";
        cout << "     TIC TAC TOE GAME\n";
        cout << "================================\n";
        
        displayGuide();
        
        int choice;
        cout << "Pilih mode permainan:\n";
        cout << "1. VS Player\n";
        cout << "2. VS Komputer\n";
        cout << "Pilihan Anda: ";
        cin >> choice;
        
        if (choice == 1) {
            playVsPlayer(board);
        } else if (choice == 2) {
            playVsComputer(board);
        } else {
            cout << "Pilihan tidak valid!\n";
            continue;
        }
        
        cout << "\nMain lagi? (y/n): ";
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');
    
    cout << "\nTerima kasih telah bermain!\n";
    
    return 0;
}
