#pragma once

#include "Coordinates.h"
#include "Reader.h"
#include "StringConst.h"
#include <string>

class Transformer {
public:
    std::pair<Coordinates, Coordinates> Request();
    std::string static Move(Coordinates from, Coordinates to);
    std::string Kill(Coordinates opponents);
private:
    Reader reader_;
    StringConst str_;
};
