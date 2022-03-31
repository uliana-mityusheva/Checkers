#include "Coordinates.h"


Coordinates::Coordinates() : x(1), y(1) {
}

Coordinates::Coordinates(char first, char second) {
    x = first - 'a' + 1;
    y = second - '1' + 1;
}

std::string Coordinates::Answer() {
    std::string str;
    str.append(1, static_cast<char>('a' + x - 1));
    str.append(1, static_cast<char>('1' + y - 1));
    return str;
}

Coordinates::Coordinates(int x, int y) : x(x), y(y) {}
