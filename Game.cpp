#include "Game.h"
#include <random>

void Game::Controller() {
    if (board_.num_white == 0) {
        status = str_const_.lost;
    }
    if (board_.num_black == 0) {
        status = str_const_.win;
    }
    std::string player_result = PlayerMove();

    if (player_result != str_const_.exit) {
        printer_.Print(player_result);
    }

    if (player_result == str_const_.ok) {
        std::pair<Coordinates, Coordinates> pair = MakeMove();
        printer_.Print(transformer_.Move(pair.first, pair.second));
    }
}

std::string Game::PlayerMove() {
    std::pair<Coordinates, Coordinates> pair = transformer_.Request();
    before = pair.first;
    after = pair.second;

    if (before.x == 0 && before.y == 0 && after.x == 0 && after.y == 0) {
        status = str_const_.exit;
        return str_const_.exit;
    }

    std::string result = CheckerPlayerMove();
    if (result == str_const_.ok) {
        board_.Change(before, after);
        board_.CheckKing(after);
    }
    return result;
}

std::pair<Coordinates, Coordinates> Game::MakeMove() {
    std::pair<Coordinates, Coordinates> pair;
    pair.first = Coordinates(0,0);
    pair.second = Coordinates(0,0);

    if (CanEat(pair)) {
        return pair;
    }
    return ChooseMove(pair);
}

void Game::Eat(std::pair<Coordinates, Coordinates> &pair, Coordinates before, Coordinates after,
               Coordinates opponents) {
    pair.first = before;
    pair.second = after;
    board_.Change(before, after);
    board_.Kill(opponents);
    board_.num_white--;
    board_.CheckKing(after);
    printer_.Print(transformer_.Kill(opponents));
}

bool Game::CanEat(std::pair<Coordinates, Coordinates> &pair) {
    int counter = 0;
    int black_checkers = 0;
    for (int i = board_.kMax; i >= board_.kMin && black_checkers < board_.num_black; --i) {
        for (int j = board_.kMax; j >= board_.kMin && black_checkers < board_.num_black; --j) {
            if (board_.Cell(Coordinates(j, i)) == BLACK && i > 2 && j > 2) {
                if ((board_.Cell(Coordinates(j - 1, i - 1)) == WHITE ||
                board_.Cell(Coordinates(j - 1, i - 1)) == WHITE_KING) &&
                board_.Cell(Coordinates(j - 2, i - 2)) == EMPTY) {
                    Eat(pair, Coordinates(j, i), Coordinates(j - 2, i - 2), Coordinates(j - 1, i - 1));
                    ++counter;
                }
            }

            if (board_.Cell(Coordinates(j, i)) == BLACK && i > 2 && j <= 6) {
                if ((board_.Cell(Coordinates(j + 1, i - 1)) == WHITE ||
                     board_.Cell(Coordinates(j + 1, i - 1)) == WHITE_KING) &&
                    board_.Cell(Coordinates(j + 2, i - 2)) == EMPTY) {
                    Eat(pair, Coordinates(j, i), Coordinates(j + 2, i - 2), Coordinates(j + 1, i - 1));
                    ++counter;
                }
            }
        }
    }
    if (counter != 0) {
        return true;
    }
    return false;
}

std::pair<Coordinates, Coordinates> Game::ChooseMove(std::pair<Coordinates, Coordinates> &pair) {
    int black_checkers = 0;
    std::vector<std::pair<Coordinates, Coordinates>> variants;
    for (int i = board_.kMax; i >= board_.kMin && black_checkers < board_.num_black; --i) {
        for (int j = board_.kMax; j >= board_.kMin && black_checkers < board_.num_black; --j) {
            if (board_.Cell(Coordinates(j, i)) == BLACK) {
                black_checkers++;
                if (i > 1 && j > 1 && board_.Cell(Coordinates(j - 1, i - 1)) == EMPTY) {
                    variants.push_back({Coordinates(j, i), Coordinates(j - 1, i - 1)});
                }
                if (i > 1 && j < 8 && board_.Cell(Coordinates(j + 1, i - 1)) == EMPTY) {
                    variants.push_back({Coordinates(j, i), Coordinates(j + 1, i - 1)});
                }
            }
        }
    }
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::pair<Coordinates, Coordinates> move = variants[mersenne() % variants.size()];
    board_.Change(move.first, move.second);
    board_.CheckKing(move.second);
    return move;
}

std::string Game::CheckerPlayerMove() {
    if (!IsIncorrectMove() || !IsOnDiag()) {
        return str_const_.error_incorrect_move;
    }

    if (IsCellBusy()) {
        return str_const_.error_busy;
    }

    if (eaten) {
        board_.num_black--;
        eaten = false;
    }
    return str_const_.ok;
}

bool Game::IsIncorrectMove() {
    return after.x <= board_.kMax && after.x >= board_.kMin &&
    after.y <= board_.kMax && after.y >= board_.kMin;
}

bool Game::IsCellBusy() {
    return board_.Cell(after) != EMPTY;
}

bool Game::IsOnDiag() {
    if (board_.Cell(before) == WHITE && before.y < 8) {
        return before.y + 1 == after.y &&
        ((before.x < 8 && before.x + 1 == after.x) || (before.x > 1 && before.x - 1 == after.x));
    }

    if (board_.Cell(before) == WHITE && before.y < 7) {
        if (before.y + 2 == after.y &&
        ((before.x < 7 && before.x + 2 == after.x) || (before.x > 2 && before.x - 2 == after.x))) {
            eaten = true;
            return eaten;
        }
    }

    if (board_.Cell(before) == WHITE_KING) {
        return before.x + before.y == after.x + after.y ||
        before.x - before.y == after.x - after.y;
    }
}


