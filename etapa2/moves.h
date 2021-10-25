// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#ifndef MOVES_H
#define MOVES_H

using namespace std;
#include <vector>

class Moves {
public:
    char *print_move(int i_src, int j_src, int i_dest, int j_dest);
    void print_helper(int src, int dest);
    void move_pawn(int &i, int &j, int color);
    void get_moves_wpawn(int pawn, vector<int> &moves);
    void get_moves_bpawn(int pawn, vector<int> &moves);
    void get_moves_pawn(int pawn, vector<int> &moves);
    void get_moves_knight(int knight, vector<int> &moves);
    void get_moves_bishop(int bishop, vector<int> &moves);
    void get_moves_rook(int rook, vector<int> &moves);
    void get_moves_queen(int queen, vector<int> &moves);
    void get_moves_king(int king, vector<int> &moves);
    void get_moves(int piece, vector<int> &moves);
    int make_move(int piece, int mv);
    void undo_move();
    void next_move(int color);
    bool check_next(int piece, int i, int j);
    bool helper_castling(int king, int j_rook);
    void check_castling(int king, vector<int> &moves);
};
#endif
