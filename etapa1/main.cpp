// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#include <iostream>
#include <string.h>
#include "board.h"
#include "moves.h"

using namespace std;

Moves moves;
Board xboard;

int main() {
    int next_to_move = WHITE, my_color = BLACK, force_mode = 0;
    string str;

    // current moving pawns' positions
    int ib, jb, iw, jw;

    cout.setf(ios::unitbuf);
    cin.rdbuf()->in_avail();

    // "xboard"
    getline(cin, str);

    cin.rdbuf()->in_avail();

    // "protover N"
    getline(cin, str);

    cout << "feature sigint=0 san=0 usermove=1\n";
    cout.flush();

    cout << "feature done=1\n";
    cout.flush();

    int ok = 1;
    while (ok) {
        cout.setf(ios::unitbuf);
        cin.rdbuf()->in_avail();

        string str2;
        getline(cin, str2);
        char cmd[80];
        strcpy(cmd, str2.c_str());

        if (strcmp(cmd, "new") == 0) {
            next_to_move = WHITE;
            my_color = BLACK;
            force_mode = 0;
            iw = 1;
            jw = 4;
            ib = 6;
            jb = 4;
            xboard.initialise_board();
        } else if (strcmp(cmd, "force") == 0) {
            force_mode = 1;
        } else if (strcmp(cmd, "go") == 0) {
            force_mode = 0;
            my_color = next_to_move;

            // make a move
            if (my_color == WHITE) {
                moves.move_pawn(iw, jw, WHITE, xboard.board);
            } else {
                moves.move_pawn(ib, jb, BLACK, xboard.board);
            }

            // update the color that needs to make the next move
            if (next_to_move == WHITE) {
                next_to_move = BLACK;
            } else {
                next_to_move = WHITE;
            }
        } else if (strcmp(cmd, "quit") == 0) {
            ok = 0;
        } else if (strstr(cmd, "usermove") && cmd[0] == 'u') {
            // update the board
            int j_src = cmd[9] - 'a';
            int i_src = cmd[10] - '1';
            int j_dest = cmd[11] - 'a';
            int i_dest = cmd[12] - '1';
            xboard.board[i_dest][j_dest] = xboard.board[i_src][j_src];
            xboard.board[i_src][j_src] = EMPTY;

            if (i_src == ib && j_src == jb) {
                ib = i_dest;
                jb = j_dest;
            } else if (i_src == iw && j_src == jw) {
                iw = i_dest;
                jw = j_dest;
            }

            // update the color that needs to make the next move
            if (next_to_move == WHITE) {
                next_to_move = BLACK;
            } else {
                next_to_move = WHITE;
            }

            if (force_mode == 0) {
                if (my_color == WHITE) {
                    moves.move_pawn(iw, jw, WHITE, xboard.board);
                } else {
                    moves.move_pawn(ib, jb, BLACK, xboard.board);
                }

                if (next_to_move == WHITE) {
                    next_to_move = BLACK;
                } else {
                    next_to_move = WHITE;
                }
            }
        } else continue;
    }

    return 0;
}
