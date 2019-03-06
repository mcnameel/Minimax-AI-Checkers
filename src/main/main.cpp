#include <iostream>
#include "Board.h"
#include "human/Parser.h"
#include "GameManager.h"
#include "AI/AI.h"

int main() {
    auto * board = new Board();

    //Player *player1 = new AI(1);
    Player *player1 = new Parser(RED);
    Player *player2 = new AI(3);
    //Player *player2 = new Parser(WHITE);

    auto * game = new GameManager(board , player1, player2);

    return 0;
}