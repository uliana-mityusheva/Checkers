#pragma once

#include <string>

struct Coordinates {
    int x;
    int y;

    Coordinates();
    Coordinates(int x, int y);
    Coordinates(char from, char to);
    std::string Answer();
};
