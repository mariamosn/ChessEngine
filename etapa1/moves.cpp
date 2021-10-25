// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#include <iostream>
#include <string.h>
#include "board.h"
#include "moves.h"

using namespace std;

char *Moves::print_move(int i_src, int j_src, int i_dest, int j_dest) {
    char *str_move = (char *)malloc(5 * sizeof(char));
    str_move[0] = (char)('a' + j_src);
    str_move[1] = (char)('1' + i_src);
    str_move[2] = (char)('a' + j_dest);
    str_move[3] = (char)('1' + i_dest);
    str_move[4] = '\0';
    return str_move;
}

void Moves::move_pawn(int &i, int &j, int color, int xboard[8][8]) {
    // if our pawn was captured or if our pawn was promoted
    if ((color == WHITE && xboard[i][j] != W_PAWN) ||
        (color == BLACK && xboard[i][j] != B_PAWN)) {
        cout << "!!!!!1" << endl;
        cout << "resign" << endl;
    // if we need to move the white pawn
    } else if (color == WHITE) {
        // if our pawn can capture another piece
        if (j - 1 >= 0 && xboard[i + 1][j - 1] != EMPTY) {
            xboard[i][j] = EMPTY;

            if (i + 1 < 7) {
                xboard[i + 1][j - 1] = W_PAWN;
                cout << "move " << print_move(i, j, i + 1, j - 1) << endl;
            } else {
                xboard[i + 1][j - 1] = W_QUEEN;
                cout << "move " << print_move(i, j, i + 1, j - 1) << "q" << endl;
            }

            i = i + 1;
            j = j - 1;
        } else if (j + 1 <= 7 && xboard[i + 1][j + 1] != EMPTY) {
            xboard[i][j] = EMPTY;

            if (i + 1 < 7) {
                xboard[i + 1][j + 1] = W_PAWN;
                cout << "move " << print_move(i, j, i + 1, j + 1) << endl;
            } else {
                xboard[i + 1][j + 1] = W_QUEEN;
                cout << "move " << print_move(i, j, i + 1, j + 1) << "q" << endl;
            }

            i = i + 1;
            j = j + 1;
        // if the pawn can advance one position
        } else if (xboard[i + 1][j] == EMPTY) {
            xboard[i][j] = EMPTY;

            if (i + 1 < 7) {
                xboard[i + 1][j] = W_PAWN;
                cout << "move " << print_move(i, j, i + 1, j) << endl;
            } else {
                xboard[i + 1][j] = W_QUEEN;
                cout << "move " << print_move(i, j, i + 1, j) << "q" << endl;
            }

            i = i + 1;
        // if the pawn has no possible moves left
        } else {
            cout << "!!!!!2" << endl;
            cout << "resign" << endl;
        }
    // if we need to move the black pawn
    } else {
        // if our pawn can capture another piece
        if (j - 1 >= 0 && xboard[i - 1][j - 1] != EMPTY) {
            xboard[i][j] = EMPTY;

            if (i - 1 > 0) {
                xboard[i - 1][j - 1] = B_PAWN;
                cout << "move " << print_move(i, j, i - 1, j - 1) << endl;
            } else {
                xboard[i - 1][j - 1] = B_QUEEN;
                cout << "move " << print_move(i, j, i - 1, j - 1) << "q" << endl;
            }

            i = i - 1;
            j = j - 1;
        } else if (j + 1 <= 7 && xboard[i - 1][j + 1] != EMPTY) {
            xboard[i][j] = EMPTY;

            if (i - 1 > 0) {
                xboard[i - 1][j + 1] = B_PAWN;
                cout << "move " << print_move(i, j, i - 1, j + 1) << endl;
            } else {
                xboard[i - 1][j + 1] = B_QUEEN;
                cout << "move " << print_move(i, j, i - 1, j + 1) << "q" << endl;
            }

            i = i - 1;
            j = j + 1;
        // if the pawn can advance a position
        } else if (xboard[i - 1][j] == EMPTY) {
            xboard[i][j] = EMPTY;

            if (i - 1 > 0) {
                xboard[i - 1][j] = B_PAWN;
                cout << "move " << print_move(i, j, i - 1, j) << endl;
            } else {
                xboard[i - 1][j] = B_QUEEN;
                cout << "move " << print_move(i, j, i - 1, j) << "q" << endl;
            }

            i = i - 1;
        // if the pawn has no possible moves left
        } else {
            cout << "!!!!!3" << endl;
            cout << "resign" << endl;
        }
    }
}

