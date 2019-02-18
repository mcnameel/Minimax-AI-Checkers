#include <iostream>
#include "Board.h"
#include "Parser.h"
#include "GameManager.h"

int main() {
    Board * board = new Board();
    Rules* rules = new Rules(board);

    Player *black = new Parser('b');
    Player *red = new Parser('r');

    GameManager* game = new GameManager(board, rules , black, red);

    return 0;
}