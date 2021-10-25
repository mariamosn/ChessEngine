// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#include <iostream>
#include <string.h>
#include "board.h"
#include "moves.h"
#include <vector>

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

    cout << "feature sigint=0 san=0 usermove=1 variants=\"3check\"\n";
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
          
            xboard.initialise_board();
        } else if (strcmp(cmd, "force") == 0) {
            force_mode = 1;
        } else if (strcmp(cmd, "go") == 0) {
            force_mode = 0;
            my_color = next_to_move;

            // make a move
            moves.next_move(my_color);
           
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

            int moved_piece = xboard.get_piece(i_src, j_src);
            if (next_to_move == WHITE) {
                w_prev_pos = i_src * 10 + j_src;
                w_crt_pos = i_dest * 10 + j_dest;
            } else {
                b_prev_pos = i_src * 10 + j_src;
                b_crt_pos = i_dest * 10 + j_dest;
            }
            // make the move
            moves.make_move(moved_piece, i_dest * 10 + j_dest);
            // update the color that needs to make the next move
            if (next_to_move == WHITE) {
                next_to_move = BLACK;
            } else {
                next_to_move = WHITE;
            }

            // when force is 0 get the next move
            if (force_mode == 0) {
                moves.next_move(my_color);
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
