// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#ifndef BOARD_H
#define BOARD_H

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

class Board {
public:
    int board[8][8];

    void initialise_board();
};
extern Board xboard;

#endif
