// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#include <iostream>
#include <string.h>
#include "board.h"
#include "moves.h"
#include <vector>

using namespace std;

Board my_board;

char *Moves::print_move(int i_src, int j_src, int i_dest, int j_dest) {
    char *str_move = (char *)malloc(5 * sizeof(char));
    str_move[0] = (char)('a' + j_src);
    str_move[1] = (char)('1' + i_src);
    str_move[2] = (char)('a' + j_dest);
    str_move[3] = (char)('1' + i_dest);
    str_move[4] = '\0';
    return str_move;
}

void Moves::get_moves_wpawn(int pawn, vector<int> &moves) {
    int mv;
    int i = pos[pawn] / 10;
    int j = pos[pawn] % 10;

    // if our pawn can capture another piece
    if (j - 1 >= 0 && board[i + 1][j - 1] < 0
                    && board[i + 1][j - 1] != B_KING) {
        mv = (i + 1) * 10 + (j - 1);
        moves.push_back(mv);
    }

    if (j + 1 <= 7 && board[i + 1][j + 1] < 0
                    && board[i + 1][j + 1] != B_KING) {
        mv = (i + 1) * 10 + (j + 1);
        moves.push_back(mv);
    }

    // if the pawn can advance one position
    if (board[i + 1][j] == EMPTY) {
        mv = (i + 1) * 10 + j;
        moves.push_back(mv);
    }

    // if the pawn can advance 2 positions
    if (board[i + 2][j] == EMPTY && board[i + 1][j] == EMPTY && i == 1){
        mv = (i + 2) * 10 + j;
        moves.push_back(mv);
    }

    // en passant
    if (b_prev_pos != - 1) {
        int i_prev, j_prev, i_crt, j_crt;
        i_prev = b_prev_pos / 10;
        j_prev = b_prev_pos % 10;
        i_crt = b_crt_pos / 10;
        j_crt = b_crt_pos % 10;

        if (j - 1 >= 0 && board[i][j - 1] == B_PAWN) {
            if (i_crt == i && j_crt == j - 1 && i_prev == 6 && i == 4) {
                // if all the conditions are met
                mv = (i + 1) * 10 + (j - 1);
                moves.push_back(mv);
            }
        }

        if (j + 1 < 8 && board[i][j + 1] == B_PAWN) {
            if (i_crt == i && j_crt == j + 1 && i_prev == 6 && i == 4) {
                // if all the conditions are met
                mv = (i + 1) * 10 + (j + 1);
                moves.push_back(mv);
            }
        }
    }
}

void Moves::get_moves_bpawn(int pawn, vector<int> &moves) {
    int mv;
    int i = pos[pawn] / 10;
    int j = pos[pawn] % 10;

    // if our pawn can capture another piece
    if (j - 1 >= 0 && board[i - 1][j - 1] > 0
                    && board[i - 1][j - 1] != W_KING) {
        mv = (i - 1) * 10 + (j - 1);
        moves.push_back(mv);
    }

    if (j + 1 <= 7 && board[i - 1][j + 1] > 0
                    && board[i - 1][j + 1] != W_KING) {
        mv = (i - 1) * 10 + (j + 1);
        moves.push_back(mv);
    }

    // if the pawn can advance a position
    if (board[i - 1][j] == EMPTY) {
        mv = (i - 1) * 10 + j;
        moves.push_back(mv);
    }

    // if the pawn can advance 2 positions
    if (board[i - 2][j] == EMPTY && board[i - 1][j] == EMPTY && i == 6) {
        mv = (i - 2) * 10 + j;
        moves.push_back(mv);
    }

    // en passant
    if (w_prev_pos != - 1) {
        int i_prev, j_prev, i_crt, j_crt;
        i_prev = w_prev_pos / 10;
        j_prev = w_prev_pos % 10;
        i_crt = w_crt_pos / 10;
        j_crt = w_crt_pos % 10;

        if (j - 1 >= 0 && board[i][j - 1] == W_PAWN) {
            if (i_crt == i && j_crt == j - 1 && i_prev == 1 && i == 3) {
                // if all the conditions are met
                mv = (i - 1) * 10 + (j - 1);
                moves.push_back(mv);
            }
        }

        if (j + 1 < 8 && board[i][j + 1] == W_PAWN) {
            if (i_crt == i && j_crt == j + 1 && i_prev == 1 && i == 3) {
                // if all the conditions are met
                mv = (i - 1) * 10 + (j + 1);
                moves.push_back(mv);
            }
        }
    }
}

void Moves::get_moves_pawn(int pawn, vector<int> &moves) {
    if (val[pawn] == W_PAWN) {
        get_moves_wpawn(pawn, moves);
    } else {
        get_moves_bpawn(pawn, moves);
    }
}

bool Moves::check_next(int piece, int i, int j) {
    // check if we attack the king
    if (piece >= W_PAWN1 && piece <= W_KING1) {
        if (board[i][j] <= 0) {
            return (board[i][j] != B_KING);
        }
    } else {
         if (board[i][j] >= 0) {
            return (board[i][j] != W_KING);
        }
    }

    return false;
}

void Moves::get_moves_knight(int knight, vector<int> &moves) {
    int mv;
    int i = pos[knight] / 10;
    int j = pos[knight] % 10;

    // possible knight moves
    if (i - 1 >= 0 && j - 2 >= 0 && check_next(knight, i - 1, j - 2)) {
        mv = (i - 1) * 10 + (j - 2);
        moves.push_back(mv);
    }

    if (i - 2 >= 0 && j - 1 >= 0 && check_next(knight, i - 2, j - 1)) {
        mv = (i - 2) * 10 + (j - 1);
        moves.push_back(mv);
    }

    if (i - 2 >= 0 && j + 1 < 8 && check_next(knight, i - 2, j + 1)) {
        mv = (i - 2) * 10 + (j + 1);
        moves.push_back(mv);
    }

    if (i - 1 >= 0 && j + 2 < 8 && check_next(knight, i - 1, j + 2)) {
        mv = (i - 1) * 10 + (j + 2);
        moves.push_back(mv);
    }

    if (i + 1 < 8 && j + 2 < 8 && check_next(knight, i + 1, j + 2)) {
        mv = (i + 1) * 10 + (j + 2);
        moves.push_back(mv);
    }

    if (i + 2 < 8 && j + 1 < 8 && check_next(knight, i + 2, j + 1)) {
        mv = (i + 2) * 10 + (j + 1);
        moves.push_back(mv);
    }

    if (i + 2 < 8 && j - 1 >= 0 && check_next(knight, i + 2, j - 1)) {
        mv = (i + 2) * 10 + (j - 1);
        moves.push_back(mv);
    }

    if (i + 1 < 8 && j - 2 >= 0 && check_next(knight, i + 1, j - 2)) {
        mv = (i + 1) * 10 + (j - 2);
        moves.push_back(mv);
    }
}

void Moves::get_moves_bishop(int bishop, vector<int> &moves) {
    int mv, start_row, start_column;
    int i = pos[bishop] / 10;
    int j = pos[bishop] % 10;

    // left-down diagonal
    start_row = i - 1;
    start_column = j - 1;
    while (start_row >= 0 && start_column >= 0
            && board[start_row][start_column] == EMPTY) {
        if (check_next(bishop, start_row, start_column)) {
            mv =  start_row * 10 + start_column;
            moves.push_back(mv);
        }
        start_row--;
        start_column--;
    }

    if (start_row >= 0 && start_column >= 0) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
    }

    // right-down diagonal
    start_row = i - 1;
    start_column = j + 1;
    while (start_row >= 0 && start_column <= 7
            && board[start_row][start_column] == EMPTY) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
        start_row--;
        start_column++;
    }

    if (start_row >= 0 && start_column < 8) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
    }

    // left-up diagonal
    start_row = i + 1;
    start_column = j - 1;
    while (start_row < 8 && start_column >= 0
            && board[start_row][start_column] == EMPTY) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
        start_row++;
        start_column--;
    }

    if (start_row < 8 && start_column >= 0) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
    }

    // right-up diagonal
    start_row = i + 1;
    start_column = j + 1;
    while (start_row < 8 && start_column < 8
            && board[start_row][start_column] == EMPTY) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
        start_row++;
        start_column++;
    }

    if (start_row < 8 && start_column < 8) {
        if (check_next(bishop, start_row, start_column)) {
            mv = start_row * 10 + start_column;
            moves.push_back(mv);
        }
    }  
}

void Moves::get_moves_rook(int rook, vector<int> &moves) {
    int mv, start_row, start_column;
    int i = pos[rook] / 10;
    int j = pos[rook] % 10;

    // vertical up
    start_row = i + 1;
    while (start_row < 8 && board[start_row][j] == EMPTY) {
        if (check_next(rook, start_row, j)) {
            mv = start_row * 10 + j;
            moves.push_back(mv);
        }
        start_row++;
    }

    if (start_row < 8 && board[start_row][j] != EMPTY) {
        if (check_next(rook, start_row, j)) {
            mv = start_row * 10 + j;
            moves.push_back(mv);
        }
    }

    // vertical down
    start_row = i - 1;
    while (start_row >= 0 && board[start_row][j] == EMPTY) {
        if (check_next(rook, start_row, j)) {
            mv =  start_row * 10 + j;
            moves.push_back(mv);
        }
        start_row--;
    }

    if (start_row >= 0 && board[start_row][j] != EMPTY) {
        if (check_next(rook, start_row, j)) {
            mv = start_row * 10 + j;
            moves.push_back(mv);
        }
    }

    // horizontal left
    start_column = j - 1;
    while (start_column >= 0 && board[i][start_column] == EMPTY) {
        if (check_next(rook, i, start_column)) {
            mv = i * 10 + start_column;
            moves.push_back(mv);
        }
        start_column--;
    }

    if (start_column >= 0 && board[i][start_column] != EMPTY) {
        if (check_next(rook, i, start_column)) {
            mv = i * 10 + start_column;
            moves.push_back(mv);
        }
    }

    // horizontal right
    start_column = j + 1;
    while (start_column < 8 && board[i][start_column] == EMPTY) {
        if (check_next(rook, i, start_column)) {
            mv = i * 10 + start_column;
            moves.push_back(mv);
        }
        start_column++;
    }

    if (start_column <= 7 && board[i][start_column] != EMPTY) {
        if (check_next(rook, i, start_column)) {
            mv = i * 10 + start_column;
            moves.push_back(mv);
        }
    }
}

void Moves::get_moves_queen(int queen, vector<int> &moves) {
    // rook & bishop merged
    get_moves_rook(queen, moves);
    get_moves_bishop(queen, moves);
}

bool Moves::helper_castling(int king, int j_rook) {
    int color_of_attack;
    int step;

    if (j_rook < pos[king] % 10) {
        step = -1;
    } else {
        step = 1;
    }

    if (king == W_KING1) {
        color_of_attack = 1;
    } else {
        color_of_attack = 0;
    }

    // verify: if not attacked and empty
    if (attack[color_of_attack][pos[king] / 10][pos[king] % 10]) {
        return false;
    }
    for (int j = pos[king] % 10 + step; j != j_rook; j = j + step) {
        if (attack[color_of_attack][pos[king] / 10][j]) {
            return false;
        }
        if (board[pos[king] / 10][j] != EMPTY) {
            return false;
        }
    }
    if (attack[color_of_attack][pos[king] / 10][j_rook]) {
        return false;
    }
    return true;
}

// returns the column of the rook if there is a possible move
// returns -1 otherwise
void Moves::check_castling(int king, vector<int> &moves) {
    int mv;
    if (king == W_KING1) {
        if (moved_king_w == 0) {
            if (moved_rook1_w == 0
                && helper_castling(king, pos[W_ROOK1] % 10)) {
                mv = (pos[king] / 10) * 10 + (pos[W_ROOK1] % 10);
                moves.push_back(mv);
            }
            if (moved_rook2_w == 0
                && helper_castling(king, pos[W_ROOK2] % 10)) {
                mv = (pos[king] / 10) * 10 + (pos[W_ROOK2] % 10);
                moves.push_back(mv);
            }
        }
    } else {
        if (moved_king_b == 0) {
            if (moved_rook1_b == 0
                && helper_castling(king, pos[B_ROOK1] % 10)) {
                mv = (pos[king] / 10) * 10 + (pos[B_ROOK1] % 10);
                moves.push_back(mv);
            }
            if (moved_rook2_b == 0
                && helper_castling(king, pos[B_ROOK2] % 10)) {
                mv = (pos[king] / 10) * 10 + (pos[B_ROOK2] % 10);
                moves.push_back(mv);
            }
        }
    }
}

void Moves::get_moves_king(int king, vector<int> &moves) {
    int mv, start_row, start_column;
    int column_castling;
    int i = pos[king] / 10;
    int j = pos[king] % 10;

    // first of all check if the castling is possible
    check_castling(king, moves);

    // vertical up move
    if (i + 1 < 8 && check_next(king, i + 1, j)) {
        mv = (i + 1) * 10 + j;
        moves.push_back(mv);
    }

    // vertical down move
    if (i - 1 >= 0 && check_next(king, i - 1, j)) {
        mv = (i - 1) * 10 + j;
        moves.push_back(mv);
    }

    // left move
    if (j - 1 >= 0 && check_next(king, i, j - 1)) {
        mv = i * 10 + j - 1;
        moves.push_back(mv);
    }

    // right move
    if (j + 1 < 8 && check_next(king, i, j + 1)) {
        mv = i * 10 + j + 1;
        moves.push_back(mv);
    }

    // left-up diagonal
    if (i + 1 < 8 && j - 1 >= 0 && check_next(king, i + 1, j - 1)) {
        mv = (i + 1) * 10 + j - 1;
        moves.push_back(mv);
    }

    // left-down diagonal
    if (i - 1 >= 0 && j - 1 >= 0 && check_next(king, i - 1, j - 1)) {
        mv = (i - 1) * 10 + j - 1;
        moves.push_back(mv);
    }

    // right-up diagonal
    if (i + 1 < 8 && j + 1 < 8 && check_next(king, i + 1, j + 1)) {
        mv = (i + 1) * 10 + j + 1;
        moves.push_back(mv);
    }

    // right-down diagonal
    if (i - 1 >= 0 && j + 1 < 8 && check_next(king, i - 1,j + 1)) {
        mv = (i - 1) * 10 + j + 1;
        moves.push_back(mv);
    }    
}

void Moves::get_moves(int piece, vector<int> &moves) {
    // clear the vector of moves
    moves.clear();

    // gel all the possible moves of a piece
    // pawn case
    if (val[piece] == W_PAWN || val[piece] == B_PAWN) {
        get_moves_pawn(piece, moves);

    // knight case
    } else if (val[piece] == W_KNIGHT || val[piece] == B_KNIGHT) {
        get_moves_knight(piece, moves);

    // bishop case
    } else if (val[piece] == W_BISHOP || val[piece] == B_BISHOP) {
        get_moves_bishop(piece, moves);

    // rook case
    } else if (val[piece] == W_ROOK || val[piece] == B_ROOK) {
        get_moves_rook(piece, moves);

    // queen case
    } else if (val[piece] == W_QUEEN || val[piece] == B_QUEEN) {
        get_moves_queen(piece, moves);

    // king case
    } else if (val[piece] == W_KING || val[piece] == B_KING) {
        get_moves_king(piece, moves);
    }
}

void Moves::undo_move() {
    // update board
    memcpy(board, board_prev, 64 * sizeof(int));
    pos = pos_prev;
    val = val_prev;

    // update states
    moved_king_w = prev_moved_king_w;
    moved_rook1_w = prev_moved_rook1_w;
    moved_rook2_w = prev_moved_rook2_w;
    moved_king_b = prev_moved_king_b;
    moved_rook1_b = prev_moved_rook1_b;
    moved_rook2_b = prev_moved_rook2_b;
}

int Moves::make_move(int piece, int mv) {
    int i_new = mv / 10, j_new = mv % 10;
    int i_old = pos[piece] / 10;
    int j_old = pos[piece] % 10;
    int castling_rook = -1;

    int original_piece = my_board.get_piece(i_new, j_new);

    // in case of  castling
    if (piece == W_KING1 && original_piece == W_ROOK1) {
        board[0][2] = W_KING;
        pos[W_KING1] = 0 * 10 + 2;
        board[0][4] = EMPTY;

        board[0][3] = W_ROOK;
        pos[W_ROOK1] = 0 * 10 + 3;
        board[0][0] = EMPTY;

        castling_rook = W_ROOK1;
    } else if (piece == W_KING1 && original_piece == W_ROOK2) {
        board[0][6] = W_KING;
        pos[W_KING1] = 0 * 10 + 6;
        board[0][4] = EMPTY;

        board[0][5] = W_ROOK;
        pos[W_ROOK2] = 0 * 10 + 5;
        board[0][7] = EMPTY;

        castling_rook = W_ROOK2;
    } else if (piece == B_KING1 && original_piece == B_ROOK1) {
        board[7][2] = B_KING;
        pos[B_KING1] = 7 * 10 + 2;
        board[7][4] = EMPTY;

        board[7][3] = B_ROOK;
        pos[B_ROOK1] = 7 * 10 + 3;
        board[7][0] = EMPTY;

        castling_rook = B_ROOK1;
    } else if (piece == B_KING1 && original_piece == B_ROOK2) {
        board[7][6] = B_KING;
        pos[B_KING1] = 7 * 10 + 6;
        board[7][4] = EMPTY;

        board[7][5] = B_ROOK;
        pos[B_ROOK2] = 7 * 10 + 5;
        board[7][7] = EMPTY;

        castling_rook = B_ROOK2;
    } else {
        if (original_piece != EMPTY) {
            pos[original_piece] = -1;
            val[original_piece] = EMPTY;
        }

        board[i_new][j_new] = val[piece];
        board[i_old][j_old] = EMPTY;
        pos[piece] = mv;

        // upgrade pawn
        if (val[piece] == W_PAWN && i_new == 7) {
            val[piece] = W_QUEEN;
            board[i_new][j_new] = val[piece];
        }
        if (val[piece] == B_PAWN && i_new == 0) {
            val[piece] = B_QUEEN;
            board[i_new][j_new] = val[piece];
        }
    }

    // undo move we getting a check result
    int color;
    if (piece >= W_PAWN1 && piece <= W_KING1) {
        color = WHITE;
    } else {
        color = BLACK;
    }
    
    if (my_board.is_check(color)) {
        undo_move();
        return -1;
    }

    if (piece == W_KING1) {
        moved_king_w = 1;
    } else if (piece == B_KING1) {
        moved_king_b = 1;
    } 
    
    if (piece == W_ROOK1 || castling_rook == W_ROOK1) {
        moved_rook1_w = 1;
    } else if (piece == W_ROOK2 || castling_rook == W_ROOK2) {
        moved_rook2_w = 1;
    } else if (piece == B_ROOK1 || castling_rook == B_ROOK1) {
        moved_rook1_b = 1;
    } else if (piece == B_ROOK2 || castling_rook == B_ROOK2) {
        moved_rook2_b = 1;
    }

    return i_old * 10 + j_old;
}

void Moves::print_helper(int src, int dest) {
    int i_src, j_src, i_dest, j_dest;
    i_src = src / 10;
    j_src = src % 10;
    i_dest = dest / 10;
    j_dest = dest % 10;
    int piece = my_board.get_piece(i_dest, j_dest);

    // castling check
    if (piece == EMPTY && src == 0 * 10 + 4) {
        if (dest == 0 * 10 + 0) {
            j_dest = 2;
        } else if (dest == 0 * 10 + 7) {
            j_dest = 6;
        }
    } else if (piece == EMPTY && src == 7 * 10 + 4) {
        if (dest == 7 * 10 + 0) {
            j_dest = 2;
        } else if (dest == 7 * 10 + 7) {
            j_dest = 6;
        }
    }

    // print the move
    if (val[piece] == W_QUEEN && val_prev[piece] == W_PAWN ||
        val[piece] == B_QUEEN && val_prev[piece] == B_PAWN) {
        cout <<"move "<< print_move(i_src, j_src, i_dest, j_dest) << "q" << endl;
    } else {
        cout <<"move "<< print_move(i_src, j_src, i_dest, j_dest) << endl;
    }

}

// returns the position of the previous move of a piece
// if there is no piece to move, returns -1
void Moves::next_move(int color) {
    int i, j, ok = 1, flag = 0;
    vector<int> moves;

    // update the board and the states
    memcpy(board_prev, board, 64 * sizeof(int));
    pos_prev = pos;
    val_prev = val;
    prev_moved_king_w = moved_king_w;
    prev_moved_rook1_w = moved_rook1_w;
    prev_moved_rook2_w = moved_rook2_w;
    prev_moved_king_b = moved_king_b;
    prev_moved_rook1_b = moved_rook1_b;
    prev_moved_rook2_b = moved_rook2_b;

    if (color == WHITE) {
        my_board.get_attack(BLACK);

        // when there is a possible castling
        i = W_KING1;
        get_moves(i, moves);
        for (j = 0; j < moves.size() && ok; j++) {
            flag = make_move(i, moves[j]);
            if (flag != -1) {
                w_prev_pos = ok;
                w_crt_pos = moves[j];
                moved_rook1_w = 1;
                print_helper(flag, moves[j]);
                ok = 0;
            } 
        }

        // get the possible move
        for (i = W_PAWN1; i < W_KING1 && ok; i++) {
            if (pos[i] != -1){
                get_moves(i, moves);
                for (j = 0; j < moves.size() && ok; j++) {
                    flag = make_move(i, moves[j]);
                    if (flag != -1) {
                        w_prev_pos = ok;
                        w_crt_pos = moves[j];
                        if (i == W_ROOK1) {
                            moved_rook1_w = 1;
                        } else if (i == W_ROOK2) {
                            moved_rook2_w = 1;
                        }
                        print_helper(flag, moves[j]);
                        ok = 0;
                    } 
                }
            }
        }
    } else {
        my_board.get_attack(WHITE);

        // when there is a possible castling
        i = B_KING1;
        get_moves(i, moves);
        for (j = 0; j < moves.size() && ok; j++) {
            flag = make_move(i, moves[j]);
            if (flag != -1) {
                b_prev_pos = ok;
                b_crt_pos = moves[j];
                moved_king_b = 1;
                print_helper(flag, moves[j]);
                ok = 0;
            }
        }

        for (i = B_PAWN1; i < B_KING1 && ok; i++) {
            if (pos[i] != -1) {
                get_moves(i, moves);
                for (j = 0; j < moves.size() && ok; j++) {
                    flag = make_move(i, moves[j]);
                    if (flag != -1) {
                        b_prev_pos = ok;
                        b_crt_pos = moves[j];
                        if (i == B_ROOK1) {
                            moved_rook1_b = 1;
                        } else if (i == B_ROOK2) {
                            moved_rook2_b = 1;
                        }
                        print_helper(flag, moves[j]);
                        ok = 0;
                    }
                }
            }
        }
    }
    // resign when there is no possible move
    if (ok) {
        cout << "resign" << endl;
    }
}
