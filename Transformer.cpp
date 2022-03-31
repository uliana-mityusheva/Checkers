#include "Transformer.h"

std::pair<Coordinates, Coordinates> Transformer::Request() {
    std::string str = reader_.Input();

    if (str == str_.exit) {
        Coordinates null(0,0);
        std::pair<Coordinates, Coordinates> null_pair;
        null_pair = {null, null};
        return null_pair;
    }

    for(int i = 0; i < str.length(); ++i) {
        if (str[i] == ' ') str.erase(i,1);
    }

    Coordinates from(str[0], str[1]);
    Coordinates to(str[3], str[4]);
    std::pair<Coordinates, Coordinates> pair(from, to);
    return pair;
}

std::string Transformer::Move(Coordinates from, Coordinates to) {
    return from.Answer() + '-' + to.Answer() + '\n';
}

std::string Transformer::Kill(Coordinates opponents) {
    return str_.eat + ' ' + opponents.Answer() + '\n';
}