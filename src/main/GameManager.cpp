//
// Created by Luke on 1/29/2019.
//

#include <iostream>
#include "GameManager.h"
#include "Rules.h"

GameManager::GameManager(Board* board, Player* player1, Player* player2) {
    this->board = board;
    this->player1 = player1;
    this->player2 = player2;

    play();
}

void GameManager::play() {
    Color winner;
    bool gameOver = false;
    while(!gameOver) {
        Move *curMove = getLegalMove();
        if(curMove != nullptr) {
            auto *destroyMe = new std::vector<Move *>();
            destroyMe->push_back(curMove);
            // when we have a valid move push the move to the board
            board->move(curMove, false, true);
        }


        // check if the game is over
        if (board->isGameOver()) {
            gameOver = true;
            winner = board->getTurn();
        }
    }

    std::string player = (winner == WHITE) ? "Red" : "White";
    std::cout << "Game Over. " + player + " wins!" << std::endl;
}

Move* GameManager::getLegalMove() {
    Move *currentMove = nullptr;

    // while the move is not valid ask for a new move
    bool invalidMove = true;
    while (invalidMove) {
        // first print the board
        board->printBoard();
        std::vector<Move*> *moves = Rules::getAllLegalMoves(board);
        std::cout << "Possible Moves:" << std::endl;
        for(auto &move : *moves) {
            std::cout << "    " << move->toString() << std::endl;
        }
        if(moves->empty()) {
            board->setGameOver(true);
            break;
        }
        
        // call getMove to request the next move from the current player
        currentMove = getMove(board);
        
        // check if the move is valid
        invalidMove = !Rules::legalMoveFromColor(currentMove, board);
    }
    return currentMove;
}



Move *GameManager::getMove(Board *bs) {
    static int i = 0;
    Move* currentMove;

    if(player1->getColor() == bs->getTurn())
        currentMove = player1->getMove(bs);

    else if(player2->getColor() == bs->getTurn())
        currentMove = player2->getMove(bs);

    ++i;
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