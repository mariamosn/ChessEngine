// Avocoders 2021: Ioana Isar, Maria Moșneag, Maria Tîmbur (323CA)

#ifndef MOVES_H
#define MOVES_H

class Moves {
public:
    char *print_move(int i_src, int j_src, int i_dest, int j_dest);
    void move_pawn(int &i, int &j, int color, int xboard[8][8]);
};
#endif
