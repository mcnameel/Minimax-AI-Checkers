//
// Created by Luke on 1/29/2019.
//

#include <iostream>
#include "../../include/internal/GameManager.h"
#include "../../include/internal/Rules.h"

GameManager::GameManager(Board* board, Player* player1, Player* player2) {
    this->board = board;
    this->player1 = player1;
    this->player2 = player2;
}

GameManager::~GameManager() {
    delete board;
    delete player1;
    delete player2;
}

Color GameManager::play() {
    // when the total number of pieces falls below this number after n turns
    // without either player gaining anything then the game will be declared a
    // draw
    int* pieceCountDraw = new int(8);
    // the number of turns without one player gaining anything on the board
    int* turnsWithoutProfit = new int(0);
    Color winner;
    bool gameOver = false;
    while(!gameOver) {
        ++turnCount;
        takeTurn();

        if(isDraw(board, pieceCountDraw, turnsWithoutProfit) || turnCount > 500) {
            gameOver = true;
            winner = NEITHER;
        }
        // check if the game is over
        if (board->isGameOver()) {
            gameOver = true;
            winner = board->getTurn();
        }
    }
    //takeLastTurn();
    //takeTurn();

    std::string winnerStr;
    if(winner == NEITHER) {
        winnerStr = "Game Over: Draw.";
    } else if (winner == WHITE) {
        winnerStr = "Game Over: Red wins.";
    } else {
        winnerStr = "Game Over: White wins.";

    }
    std::cout << winnerStr << std::endl;

    return winner;
}

Move* GameManager::getLegalMove() {
    Move *currentMove = nullptr;

    // while the move is not valid ask for a new move
    bool invalidMove = true;
    while (invalidMove) {
        // first print the board
        board->printBoard();
        std::vector<Move*> *moves = Rules::getAllLegalMoves(board);
        std::cout << "Turn #" << turnCount << " with " << moves->size() << " Possible Moves:" << std::endl;
        for(auto &move : *moves) {
            std::cout << "    " << move->toString() << std::endl;
        }
        if(moves->empty()) {
            board->setGameOver(true);
            //break;
        }
        
        // call getMove to request the next move from the current player
        currentMove = getMove(board);
        
        // check if the move is valid
        invalidMove = !Rules::legalMoveFromColor(currentMove, board);
    }
    return currentMove;
}



Move *GameManager::getMove(Board *bs) {
    Move* currentMove;

    if(player1->getColor() == bs->getTurn())
        currentMove = player1->getMove(bs);

    else if(player2->getColor() == bs->getTurn())
        currentMove = player2->getMove(bs);

    return currentMove;
}

bool GameManager::crownMe(Move *move) {
    bool crowned = false;
    if((move->getDestRow() == 7 && move->getColor() == WHITE) ||
       (move->getDestRow() == 0 && move->getColor() == RED)) {
        move->setKingMove(true);
        crowned = true;
    }
    return crowned;
}

bool GameManager::isDraw(Board *bs, int *pieceCountDraw,
                         int *turnsWithoutProfit) {
    const int maxTurnsWithoutProfit = 40;
    int totalPieces = board->getWhiteCount() + board->getRedCount();
    if (totalPieces <= *pieceCountDraw) {
        if (totalPieces != *pieceCountDraw) {
            *pieceCountDraw = totalPieces;
            *turnsWithoutProfit = 0;
        } else {
            ++(*turnsWithoutProfit);
        }
    }
    return *turnsWithoutProfit == maxTurnsWithoutProfit;
}

void GameManager::takeTurn() {
    Move *curMove = getLegalMove();
    if(curMove != nullptr) {
        auto *destroyMe = new std::vector<Move *>();
        destroyMe->push_back(curMove);
        // when we have a valid move push the move to the board
        board->move(curMove, true);
    }
}

