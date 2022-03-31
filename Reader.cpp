#include "Reader.h"
#include <iostream>

std::string Reader::Input() {
    std::string str;
    std::cin >> str;

    for (int i = 0; i < str.length(); ++i) {
        str[i] = tolower(str[i]);
    }
    return str;
}
