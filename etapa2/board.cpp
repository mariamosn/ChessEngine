// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#include <iostream>
#include <string.h>
#include "board.h"
#include "moves.h"
#include <vector>

using namespace std;

Moves action;

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
        pos[i + 1] = 1 * 10 + i;
        val[i + 1] = W_PAWN;
    }

    // black pawns
    for (int i = 0; i < 8; i++) {
        board[6][i] = B_PAWN;
        pos[i + 21] = 6 * 10 + i;
        val[i + 21] = B_PAWN;
    }

    // white pieces (except the pawns)
    board[0][0] = board[0][7] = W_ROOK;
    pos[W_ROOK1] = 0 * 10 + 0;
    pos[W_ROOK2] = 0 * 10 + 7;
    val[W_ROOK1] = val[W_ROOK2] = W_ROOK;

    board[0][1] = board[0][6] = W_KNIGHT;
    pos[W_KNIGHT1] = 0 * 10 + 1;
    pos[W_KNIGHT2] = 0 * 10 + 6;
    val[W_KNIGHT1] = val[W_KNIGHT2] = W_KNIGHT;

    board[0][2] = board[0][5] = W_BISHOP;
    pos[W_BISHOP1] = 0 * 10 + 2;
    pos[W_BISHOP2] = 0 * 10 + 5;
    val[W_BISHOP1] = val[W_BISHOP2] = W_BISHOP;

    board[0][3] = W_QUEEN;
    pos[W_QUEEN1] = 0 * 10 + 3;
    val[W_QUEEN1] = W_QUEEN;

    board[0][4] = W_KING;
    pos[W_KING1] = 0 * 10 + 4;
    val[W_KING1] = W_KING;

    // black pieces (except the pawns)
    board[7][0] = board[7][7] = B_ROOK;
    pos[B_ROOK1] = 7 * 10 + 0;
    pos[B_ROOK2] = 7 * 10 + 7;
    val[B_ROOK1] = val[B_ROOK2] = B_ROOK;

    board[7][1] = board[7][6] = B_KNIGHT;
    pos[B_KNIGHT1] = 7 * 10 + 1;
    pos[B_KNIGHT2] = 7 * 10 + 6;
    val[B_KNIGHT1] = val[B_KNIGHT2] = B_KNIGHT;

    board[7][2] = board[7][5] = B_BISHOP;
    pos[B_BISHOP1] = 7 * 10 + 2;
    pos[B_BISHOP2] = 7 * 10 + 5;
    val[B_BISHOP1] = val[B_BISHOP2] = B_BISHOP;

    board[7][3] = B_QUEEN;
    pos[B_QUEEN1] = 7 * 10 + 3;
    val[B_QUEEN1] = B_QUEEN;

    board[7][4] = B_KING;
    pos[B_KING1] = 7 * 10 + 4;
    val[B_KING1] = B_KING;

    moved_king_w = 0;
    moved_rook1_w = 0;
    moved_rook2_w = 0;
    moved_king_b = 0;
    moved_rook1_b = 0;
    moved_rook2_b = 0;

    w_prev_pos = -1;
    w_crt_pos = -1;
    b_prev_pos = -1;
    b_crt_pos = -1;
}

// update the attack three-dimensional array
void Board::attack_update_white(){
    vector<int> moves;
    memset(attack[0], 0, 64 * sizeof(int));
    board[pos[B_KING1] / 10][pos[B_KING1] % 10] = B_PAWN;

    for (int i = W_PAWN1; i <= W_KING1; i++) {
        if(pos[i] != -1){
            action.get_moves(i, moves);
            for(int j = 0; j < moves.size(); j++){
                int x = moves[j] / 10;
                int y = moves[j] % 10;
                // put 1 in the attacked cell
                attack[0][x][y] = 1;
            }
        }
    }

    // undo the changes
    board[pos[B_KING1] / 10][pos[B_KING1] % 10] = B_KING;
}


// update the attack three-dimensional array
void Board::attack_update_black(){
    vector<int> moves;
    memset(attack[1], 0, 64 * sizeof(int));

    board[pos[W_KING1] / 10][pos[W_KING1] % 10] = W_PAWN;

    for (int i = B_PAWN1; i <= B_KING1; i++) {
        if(pos[i] != -1){
            action.get_moves(i, moves);
            for(int j = 0; j< moves.size(); j++){
                int x = moves[j] / 10;
                int y = moves[j] % 10;
                // put 1 in the attacked cell
                attack[1][x][y] = 1;
            }
        }
    }

    // undo the changes
    board[pos[W_KING1] / 10][pos[W_KING1] % 10] = W_KING;
}

// get the attacks of a certain color
void Board::get_attack(int color) {
    if (color == WHITE) {
        attack_update_white();
    } else {
        attack_update_black();
    }
}

// verify if the king is in check
int Board::is_check(int color) {
    int i, j;
    if (color == WHITE) {
        i = pos[W_KING1] / 10;
        j = pos[W_KING1] % 10;
        get_attack(BLACK);

        return attack[1][i][j];
    } else {
        i = pos[B_KING1] / 10;
        j = pos[B_KING1] % 10;
        get_attack(WHITE);

        return attack[0][i][j];
    }
    return 0;
}

// returns the piece from a position
int Board::get_piece(int i, int j) {
    int k, p;
    p = i * 10 + j;

    for (k = W_PAWN1; k <= W_KING1; k++) {
        if (pos[k] == p) {
            return k;
        }
    }
    for (k = B_PAWN1; k <= B_KING1; k++) {
        if (pos[k] == p) {
            return k;
        }
    }

    return EMPTY;
}
