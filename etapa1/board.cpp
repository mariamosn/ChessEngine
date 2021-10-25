// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#include <iostream>
#include <string.h>
#include "board.h"

void Board::initialise_board() {
    int i, j;
    // empty positions
    for (int i = 2; i <= 5; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = EMPTY;
        }
    }

    // white pawns
    for (int i = 0; i < 8; i++) {
        board[1][i] = W_PAWN;
    }

    // black pawns
    for (int i = 0; i < 8; i++) {
        board[6][i] = B_PAWN;
    }

    // white pieces (except the pawns)
    board[0][0] = board[0][7] = W_ROOK;
    board[0][1] = board[0][6] = W_KNIGHT;
    board[0][2] = board[0][5] = W_BISHOP;
    board[0][3] = W_QUEEN;
    board[0][4] = W_KING;

    // black pieces (except the pawns)
    board[7][0] = board[7][7] = B_ROOK;
    board[7][1] = board[7][6] = B_KNIGHT;
    board[7][2] = board[7][5] = B_BISHOP;
    board[7][3] = B_QUEEN;
    board[7][4] = B_KING;
}
