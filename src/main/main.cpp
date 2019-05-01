#include <iostream>
#include "../../include/internal/Board.h"
#include "../../include/internal/Parser.h"
#include "../../include/internal/GameManager.h"
#include "../../include/internal/AI_Evaluation_Impl_01.h"
#include "../../include/internal/AI_Evaluation_Impl_02.h"
#include "../../include/internal/AI_Evaluation_Impl_03.h"
#include "../../include/internal/AI_Evaluation_Impl_04.h"
#include "../../include/internal/AI_Evaluation_Impl_06.h"
#include "../../include/internal/AI_Evaluation_Impl_05.h"
#include "../../include/internal/AI_Evaluation_Impl_07.h"

#define _timer_ std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())

/**
 * constructs a player of the given type. the number will indicate which
 * verison of evaluation algorithm to run and 0 indicates a parser player
 * @param depth the depth to look in the tree
 * @param algorithm the algorithm to use to evaluate
 * @param color either r or w for red or white
 * @return pointer to the player created
 */
Player *getPlayer(const int algorithm, const int depth, const Color color, const bool usePruning) {
    switch(algorithm) {
        case 1:
            return new AI_Minimax_01(depth, color, usePruning);
        case 2:
            return new AI_Minimax_02(depth, color, usePruning);
        case 3:
            return new AI_Minimax_03(depth, color, usePruning);
        case 4:
            return new AI_Minimax_04(depth, color, usePruning);
        case 5:
            return new AI_Minimax_05(depth, color, usePruning);
        case 6:
            return new AI_Minimax_06(depth, color, usePruning);
        case 7:
            return new AI_Minimax_07(depth, color, usePruning);
        default:
            return new Parser(color);
    }
}

void printResults(const std::vector<Color> &whoWon,
        const std::string &player1Str, const std::string &player2Str) {
    int timesToRun = whoWon.size();
    int draws = 0;          // number of draws
    int evalAWinsGF = 0;    // wins by evaluation alg A when its red
    int evalBWinsGS = 0;    // wins by evaluation alg B when its white
    int evalAWinsGS = 0;    // wins by evaluation alg A when its white
    int evalBWinsGF = 0;    // wins by evaluation alg B when its red
    for(int i = 0; i < timesToRun; i++) {
        Color winner = whoWon[i];
        std::string winnerStr;
        if (winner == NEITHER) {
            winnerStr = "Draw.";
        } else if (winner == RED) {
            winnerStr = "Red wins.";
        } else if (winner == WHITE) {
            winnerStr = "White wins.";
        }
        std::cout << "Game " << i << ": " << winnerStr << std::endl;

        if(i < (timesToRun / 2)) {
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
    std::cout << player1Str <<  " wins " << std::endl
              << "    As red:   " << evalAWinsGF << std::endl
              << "    As white: " << evalAWinsGS << std::endl
              << player2Str <<  " wins " << std::endl
              << "    As red:   " << evalBWinsGF << std::endl
              << "    As white: " << evalBWinsGS << std::endl;
    std::cout << "Draws:        " << draws << std::endl;
}

/**
 * Plays x games with on algorithm against another. After half of the games
 * have been run the players switch colors
 * @param timesToRun the number of games to run
 * @param depth1 the depth of the first player
 * @param depth2 the depth of the second player
 */
void runXTimes(const int timesToRun, const int alg1, const int depth1,
        const bool prune1, const int alg2, const int depth2,
        const bool prune2) {
    std::string player1Str;
    std::string player2Str;
    std::vector<Color> whoWon(timesToRun);

    for(int i = 0; i < timesToRun; ++i) {
        std::cout << "\n\n\n\nGame: " << i << std::endl;
        auto* board = new Board();

        Player *player1;
        Player *player2;
        if(i < (timesToRun / 2)) {
            player1 = getPlayer(alg1, depth1, RED, prune1);
            player2 = getPlayer(alg2, depth2, WHITE, prune2);
        } else {
            player1 = getPlayer(alg2, depth2, RED, prune2);
            player2 = getPlayer(alg1, depth1, WHITE, prune1);
        }
        if(i == 0) {
            std::string p1 = (prune1) ? "with pruning" : "without pruning";
            std::string p2 = (prune2) ? "with pruning" : "without pruning";
            player1Str = player1->getName() + ", depth " +
                    std::to_string(depth1) + ", " + p1;
            player2Str = player2->getName() + ", depth " +
                    std::to_string(depth2) + ", " + p2;
        }
        GameManager game(board, player1, player2, false);
        whoWon[i] = game.play();
    }

    printResults(whoWon, player1Str, player2Str);
}

void run() {
    auto *board = new Board();
    auto *player1 = new AI_Minimax_04(7, RED, false);
    //Player *player1 = new Parser(RED);
    //auto *player2 = new AI_Minimax_03(7, WHITE);
    Player *player2 = new Parser(WHITE);
    auto *game = new GameManager(board, player1, player2, true);
    // start the game
    game->play();

    delete game;
}

int main(int argc, char **argv) {
    if(argc != 8) {
        std::cout << "Invalid arguments 8 required: number of games, player 1 "
                     "depth, player 1 algorithm, use alpha-beta pruning, player"
                     " 2 depth, player 2 algorithm, use alpha-beta pruning"
                     << std::endl;
        std::cout << "example:" << std::endl <<
                     "     ./Minimax_AI_Checkers 50 3 7 0 4 4 1" << std::endl;
        std::cout << "For 50 games:\n"
                     "  Player 1: Evaluation 7, depth 3, without alpha-beta "
                     "pruning"
                     "\n     vs. "
                     "\n  Player 2: Evaluation 4, depth 4, with alpha-beta "
                     "pruning\n Use 0 for the algorithm to play using STD I/O"
                     " in terminal" << std::endl;
        exit(0);
    }
    auto startTime = _timer_;
    runXTimes(std::stoi(argv[1]), std::stoi(argv[2]), std::stoi(argv[3]),
            std::stoi(argv[4]), std::stoi(argv[5]),  std::stoi(argv[6]),
            std::stoi(argv[7]));
    auto endTime = _timer_;
    std::cout << "Game finished in " << ((endTime - startTime).count() / ( 1000.0)) << "s" << std::endl;

    return 0;
}
