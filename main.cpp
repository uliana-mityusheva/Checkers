#include <iostream>
#include "Game.h"
#include "Printer.h"

int main() {
    Printer printer;
    StringConst string;
    printer.Print(string.hello);

    Game game;
    game.status = string.play;
    while (game.status == string.play) {
        game.Controller();
    }

    if (game.status != string.exit) {
        printer.Print(game.status);
    }
    printer.Print(string.bye);
    return 0;
}
