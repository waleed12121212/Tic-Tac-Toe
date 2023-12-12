#pragma once
#include<iostream>
#include<vector>
using namespace std;
enum Player { X, O, E };

struct GameState {
    vector<vector<Player>> board;
    Player currPlayer;
};

Player checkGameState(const GameState& state) {
    for (int r = 0; r < 3; ++r) {
        if (state.board[r][0] != E && state.board[r][0] == state.board[r][1] && state.board[r][1] == state.board[r][2]) {
            return state.board[r][0];
        }
    }

    for (int c = 0; c < 3; ++c) {
        if (state.board[0][c] != E && state.board[0][c] == state.board[1][c] && state.board[1][c] == state.board[2][c]) {
            return state.board[0][c];
        }
    }

    if (state.board[0][0] != E && state.board[0][0] == state.board[1][1] && state.board[1][1] == state.board[2][2]) {
        return state.board[0][0];
    }

    if (state.board[0][2] != E && state.board[0][2] == state.board[1][1] && state.board[1][1] == state.board[2][0]) {
        return state.board[0][2];
    }

    bool isDraw = true;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (state.board[row][col] == E) {
                isDraw = false;
                break;
            }
        }
    }
    if (isDraw) {
        return E;
    }

    return E;
}
int minimax(GameState state, int depth, bool isMaxPlayer) {

    Player winner = checkGameState(state);
    if (winner != E) {

        if (winner == X) {
            return 1;
        }

        else if (winner == O) {
            return -1;
        }

        else {
            return 0;
        }
    }

    if (isMaxPlayer) {
        int bestScore = INT_MIN;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (state.board[r][c] == E) {
                    state.board[r][c] = X;
                    int score = minimax(state, depth + 1, false);
                    state.board[r][c] = E;
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    }
    else {
        int bestScore = INT_MAX;
        for (int r = 0; r < 3; ++r) {
            for (int c = 0; c < 3; ++c) {
                if (state.board[r][c] == E) {
                    state.board[r][c] = O;
                    int score = minimax(state, depth + 1, true);
                    state.board[r][c] = E;
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}