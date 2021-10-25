// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#ifndef MOVES_H
#define MOVES_H

using namespace std;
#include <vector>

class Moves {
public:
    char *print_move(int i_src, int j_src, int i_dest, int j_dest);
    void print_helper(int src, int dest, vector<int> val_prev);
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
    int get_opponent(int color);
    bool game_over(int player);
    int evaluate(int player);
    pair <int, int> alphabeta_negamax(int player, int depth, int alpha,
                                        int beta);
    void undo_move(int board_prev[8][8], vector<int> pos_prev,
                    vector<int> val_prev, int prev_moved_king_w,
                    int prev_moved_rook1_w, int prev_moved_rook2_w,
                    int prev_moved_king_b, int prev_moved_rook1_b,
                    int prev_moved_rook2_b, int copy_w_prev_pos,
                    int copy_w_crt_pos, int copy_b_prev_pos,
                    int copy_b_crt_pos);
};
#endif
