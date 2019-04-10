#include <iostream>
#include "../../include/internal/Board.h"
#include "../../include/internal/Parser.h"
#include "../../include/internal/GameManager.h"
#include "../../include/internal/AI_Minimax_01.h"
#include "../../include/internal/AI_Minimax_02.h"
#include "../../include/internal/AI_Minimax_03.h"
#include "../../include/internal/AI_Minimax_04.h"

#define _timer_ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())

void runXTimes(const int timesToRun) {
    std::vector<Color> whoWon(timesToRun);
    for(int i = 0; i < timesToRun; i++) {
        std::cout << "\n\n\n\nGame: " << i << std::endl;
        Board* board = new Board();

        Player *player1;
        Player *player2;
        if(i < timesToRun / 2) {
            player1 = new AI_Minimax_04(4, RED);
            //Player *player1 = new Parser(RED);
            player2 = new AI_Minimax_03(5, WHITE);
            //Player *player2 = new Parser(WHITE);
        } else {
            player1 = new AI_Minimax_03(4, RED);
            //Player *player1 = new Parser(RED);
            player2 = new AI_Minimax_04(5, WHITE);
            //Player *player2 = new Parser(WHITE);
        }
        auto *game = new GameManager(board, player1, player2, false);
        whoWon[i] = game->play();

        delete game;
    }
    int draws = 0;          // number of draws
    int evalAWinsGF = 0;    // wins by evaluation alg A when its red
    int evalBWinsGS = 0;    // wins by evaluation alg B when its white
    int evalAWinsGS = 0;    // wins by evaluation alg A when its white
    int evalBWinsGF = 0;    // wins by evaluation alg B when its red
    for(int i = 0; i < timesToRun; i++) {
        Color winner = whoWon[i];
        if(i < timesToRun / 2) {
            if (winner == NEITHER) {
                ++draws;
            } else if (winner == RED) {
                ++evalAWinsGF;
            } else if (winner == WHITE) {
                ++evalBWinsGS;
            }
        } else {
            if (winner == NEITHER) {
                ++draws;
            } else if (winner == RED) {
                ++evalBWinsGF;
            } else if (winner == WHITE) {
                ++evalAWinsGS;
            }
        }
    }
    std::cout << "Draws:        " << draws << std::endl;
    std::cout << "Evaluation A wins " << std::endl
              << "    As red:   " << evalAWinsGF << std::endl
              << "    As white: " << evalAWinsGS << std::endl
              << "Evaluation B wins " << std::endl
              << "    As red:   " << evalBWinsGF << std::endl
              << "    As white: " << evalBWinsGS << std::endl;
}

void run() {
    Board* board = new Board();
    auto *player1 = new AI_Minimax_04(4, RED);
    //Player *player1 = new Parser(RED);
    auto *player2 = new AI_Minimax_03(4, WHITE);
    //Player *player2 = new Parser(WHITE);
    auto *game = new GameManager(board, player1, player2, true);
    // start the game
    game->play();

    delete game;
}

int main() {
    auto startTime = _timer_;
    //run();
    runXTimes(100);
    auto endTime = _timer_;
    std::cout << "Game finished in " << ((endTime - startTime).count() / ( 1000.0 * 60)) << "s" << std::endl;

    return 0;
}
