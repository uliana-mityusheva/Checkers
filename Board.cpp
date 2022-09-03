#include "Board.h"

Board::Board() : num_black(12), num_white(12) {
    board_.resize(9);
    for (int i = 0; i < board_.size(); ++i) {
        board_[i].resize(9);
    }

    for (int i = kMin; i <= kMax; ++i) {
        for (int j = kMin; j <= kMax; ++j) {
            if (i <= 3 && (i + j) % 2 == 0) {
                board_[j][i] = WHITE;
            } else if (i >= 6 && (i + j) % 2 == 0) {
                board_[j][i] = BLACK;
            } else {
                board_[j][i] = EMPTY;
            }
        }
    }
}

void Board::Change(Coordinates before, Coordinates after) {
    board_[after.x][after.y] = board_[before.x][before.y];
    board_[before.x][before.y] = EMPTY;
}

cell Board::Cell(Coordinates move) {
    return board_[move.x][move.y];
}

void Board::CheckKing(Coordinates move) {
    if (board_[move.x][move.y] == WHITE && move.x == kMax) {
        board_[move.x][move.y] = WHITE_KING;
    }
    if (board_[move.x][move.y] == BLACK && move.x == kMin) {
        board_[move.x][move.y] = BLACK_KING;
    }
}

void Board::Kill(Coordinates opponent) {
    board_[opponent.x][opponent.y] = EMPTY;
}