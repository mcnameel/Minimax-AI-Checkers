#include <iostream>
#include "Board.h"
#include "human/Parser.h"
#include "GameManager.h"
#include "AI/AI_Minimax_01.h"
#include "AI/AI_Minimax_02.h"
#include "AI/AI_Minimax_03.h"

int main() {
    const int timesToRun = 50;
    Color whoWon[timesToRun] = {};
    for(int i = 0; i < timesToRun; i++) {
        std::cout << "\n\n\n\nGame: " << i << std::endl;
        Board* board = new Board();

        Player *player1;
        Player *player2;
        if(i < timesToRun / 2) {
            player1 = new AI_Minimax_02(4, RED);
            //Player *player1 = new Parser(RED);
            player2 = new AI_Minimax_03(4, WHITE);
            //Player *player2 = new Parser(WHITE);
        } else {
            player1 = new AI_Minimax_03(4, RED);
            //Player *player1 = new Parser(RED);
            player2 = new AI_Minimax_02(4, WHITE);
            //Player *player2 = new Parser(WHITE);
        }
        auto *game = new GameManager(board, player1, player2);
        whoWon[i] = game->play();

        delete board;
        delete player1;
        delete player2;
        delete game;
    }
    for(int i = 0; i < timesToRun; i++) {
        Color winner = whoWon[i];
        std::string s = "Game #" + std::to_string(i) + ": ";
        s = s + (winner == NEITHER ? "Draw." : winner == WHITE ? "Red." : "White.");
        std::cout << s << std::endl;

    }
    return 0;
}