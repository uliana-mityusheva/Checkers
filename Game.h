#pragma once

#include "Board.h"
#include "Transformer.h"
#include "Printer.h"

class Game {
public:
    Coordinates before;
    Coordinates after;

    std::string status;

    std::string PlayerMove();
    std::pair<Coordinates, Coordinates> MakeMove();
    void Controller();

    std::string CheckerPlayerMove();
    bool IsIncorrectMove();
    bool IsCellBusy();
    bool IsOnDiag();
    bool CanEat(std::pair<Coordinates, Coordinates> &pair);
    void Eat(std::pair<Coordinates, Coordinates> &pair, Coordinates before,
             Coordinates after, Coordinates opponents);
    std::pair<Coordinates, Coordinates> ChooseMove(std::pair<Coordinates, Coordinates> &pair);
private:
    bool eaten = false;
    Board board_;
    Transformer transformer_;
    Printer printer_;
    StringConst str_const_;
};
