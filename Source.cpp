#include <iostream>
#include <vector>
#include<fstream>
#include "GameState.h"
using namespace std;

void playGame(int currp);
int main() {
    int q = 0, c = 1;
    do {
        playGame(c);
        cout << "============\n";
        cout << "1.Play again\n";
        cout << "2.EXIT      \n";
        cout << "============\n";
        cin >> q;
        c++;
    } while (q == 1);
}

void playGame(int currp) {
    GameState gameState;
    gameState.board = {
        {E, E, E},
        {E, E, E},
        {E, E, E}
    };
    string filename;
    cout << "Enter your file name: \n";
    cin >> filename;

    ifstream inputFile(filename);

    if (!inputFile) {
        cout << "File creation failed\n";
        return;
    }
    vector<string> temp(3);
    for (int i = 0; i < 3; i++) {
        inputFile >> temp[i];
    }
    inputFile.close();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (temp[i][j] == '-') {
                gameState.board[i][j] = E;
            }
            else if (temp[i][j] == 'O') {
                gameState.board[i][j] = O;
            }
            else {
                gameState.board[i][j] = X;
            }
        }
    }
    if (currp % 2 == 0) {
        gameState.currPlayer = O;
    }
    else {
        gameState.currPlayer = X;
    }
    if (gameState.currPlayer == X) {
        int bestScore = INT_MIN;
        int bestRow = -1;
        int bestCol = -1;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (gameState.board[r][c] == E) {
                    gameState.board[r][c] = X;
                    int score = minimax(gameState, 0, false);
                    gameState.board[r][c] = E;
                    if (score > bestScore) {
                        bestScore = score;
                        bestRow = r;
                        bestCol = c;
                    }
                }
            }
        }
        gameState.board[bestRow][bestCol] = X;
        gameState.currPlayer = O;
    }

    while (checkGameState(gameState) == E) {
        cout << "   ___________\n";
        cout << "  | 1 | 2 | 3 |\n";
        cout << "--|---|---|---|\n";
        int z = 1;
        for (const auto& row : gameState.board) {
            cout << "|" << z << "|";
            for (const auto& cell : row) {
                if (cell == X) {
                    cout << " X |";
                }
                else if (cell == O) {
                    cout << " O |";
                }
                else {
                    cout << " _ |";
                }
            }
            cout << endl;
            cout << "|_|___|___|___|\n";
            z++;
        }
        int fullspace = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (gameState.board[i][j] == X || gameState.board[i][j] == O) {
                    fullspace++;
                }
            }
        }

        int row, col;
        if (fullspace != 9) {
            cout << "choise a row: ";
            cin >> row;
            cout << "choise a col: ";
            cin >> col;
            col--;
            row--;
            while (!(row >= 0 && row < 3 && col >= 0 && col < 3 && gameState.board[row][col] == E))
            {
                cout << "Incorrect movement. Try again\n";
                cout << "choise a row: ";
                cin >> row;
                cout << "choise a col: ";
                cin >> col;
                col--;
                row--;
            }
        }
        else {
            cout << "============\n";
            cout << "Equality\n";
            return;
        }

        gameState.board[row][col] = O;
        gameState.currPlayer = X;

        if (checkGameState(gameState) == E) {
            int bestScore = INT_MIN;
            int bestMoveRow = -1;
            int bestMoveCol = -1;
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 3; ++c) {
                    if (gameState.board[r][c] == E) {
                        gameState.board[r][c] = X;
                        int score = minimax(gameState, 0, false);
                        gameState.board[r][c] = E;
                        if (score > bestScore) {
                            bestScore = score;
                            bestMoveRow = r;
                            bestMoveCol = c;
                        }
                    }
                }
            }

            gameState.board[bestMoveRow][bestMoveCol] = X;
            gameState.currPlayer = O;
        }
    }

    for (const auto& row : gameState.board) {
        for (const auto& cell : row) {
            if (cell == X) {
                cout << "X ";
            }
            else if (cell == O) {
                cout << "O ";
            }
            else {
                cout << "_ ";
            }
        }
        cout << endl;
    }

    Player winner = checkGameState(gameState);
    if (winner == X) {
        cout << "============\n";
        cout << "Player X is winer\n";
    }
    else if (winner == O) {
        cout << "============\n";
        cout << "Player O is winer\n";
    }
}
