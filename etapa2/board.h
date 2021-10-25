// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#ifndef BOARD_H
#define BOARD_H

using namespace std;

#include <vector>

// used for values
#define W_KING 900
#define W_QUEEN 90
#define W_ROOK 50
#define W_BISHOP 31
#define W_KNIGHT 30
#define W_PAWN 10

#define B_KING -900
#define B_QUEEN -90
#define B_ROOK -50
#define B_BISHOP -31
#define B_KNIGHT -30
#define B_PAWN -10

#define EMPTY 0

#define WHITE 77
#define BLACK 78

// used for positions
#define W_PAWN1 1
#define W_PAWN2 2
#define W_PAWN3 3
#define W_PAWN4 4
#define W_PAWN5 5
#define W_PAWN6 6
#define W_PAWN7 7
#define W_PAWN8 8

#define W_KNIGHT1 9
#define W_KNIGHT2 10
#define W_BISHOP1 11
#define W_BISHOP2 12
#define W_ROOK1 13
#define W_ROOK2 14
#define W_QUEEN1 15
#define W_KING1 16

#define B_PAWN1 21
#define B_PAWN2 22
#define B_PAWN3 23
#define B_PAWN4 24
#define B_PAWN5 25
#define B_PAWN6 26
#define B_PAWN7 27
#define B_PAWN8 28

#define B_KNIGHT1 29
#define B_KNIGHT2 30
#define B_BISHOP1 31
#define B_BISHOP2 32
#define B_ROOK1 33
#define B_ROOK2 34
#define B_QUEEN1 35
#define B_KING1 36

// remember if king was moved or if the rook was moved
// needed for castling
inline int moved_king_w;
inline int moved_rook1_w;
inline int moved_rook2_w;
inline int moved_king_b;
inline int moved_rook1_b;
inline int moved_rook2_b;

inline int prev_moved_king_w;
inline int prev_moved_rook1_w;
inline int prev_moved_rook2_w;
inline int prev_moved_king_b;
inline int prev_moved_rook1_b;
inline int prev_moved_rook2_b;

// the last move of the opponent
inline int w_prev_pos;
inline int w_crt_pos;
inline int b_prev_pos;
inline int b_crt_pos;

// three-dimensional array that is used for retaining
// the pieces that can attack a cell
// attack[0][1][1] = 1 => white pieces can attack the cell (1, 1)
inline int attack[2][8][8];

// vectors for every update
inline int board_prev[8][8];
inline vector<int> pos_prev(40, 0);
inline vector<int> val_prev(40, 0);

// vectors for values and positions
inline int board[8][8];
inline vector<int> pos(40, 0);
inline vector<int> val(40, 0);

class Board {

public:

    void initialise_board();
    void get_attack();
    int is_check(int color);
    int get_piece(int i, int j);
    void attack_update_white();
    void attack_update_black();
    void get_attack(int color);

};

extern Board xboard;

#endif
