#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
//board.h  Display.h  fen.h  Makemove.h  Movegeneration.h  Moverparser.h  Movevalidation.h  Types.h
#include "board.h"
#include "Moverparser.h"
#include "Movevalidation.h"
#include "Movegeneration.h"
#include "fen.h"
#include "Display.h"
#include "Makemove.h"

int main()
{
    board game;

    readFEN(
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        &game
    );

    while (game.game_on)
    {
        drawBoard(&game);
        char input[10];
        std::cout << "Enter move: ";
        std::cin >> input;
        setCurrentMove(&game, input);
        determineMove(&game);
        parseMove(&game.p, &game);
        Move(&game);
    }

    return 0;
}
