#pragma once
#include <iostream>
#include <vector>
#include "Coordinates.h"

enum cell {WHITE, WHITE_KING, BLACK, BLACK_KING, EMPTY};

class Board {
public:
    const int kMin = 1;
    const int kMax = 8;

    int num_white;
    int num_black;

    Board();
    void Change(Coordinates before, Coordinates after);
    cell Cell(Coordinates move);
    void CheckKing(Coordinates move);
    void Kill(Coordinates opponent);
private:
    std::vector<std::vector<cell>> board_;
};
