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
    bool gameOver = false;
    while(!gameOver) {
        Move *curMove = getLegalMove();

        auto *destroyMe = new std::vector<Move *>();
        destroyMe->push_back(curMove);
        // when we have a valid move push the move to the board
        board->move(curMove, false);


        /*std::vector<Move*>* jumps = Rules::getJumpsAtPos(curMove->getDestRow(),curMove->getDestCol(), board);
        // check if the piece should be crowned and if so then king the piece
        // get the next move if the player can changed
        bool crowned = crownMe(curMove);
        while (curMove->getCapRow() != -1 && !jumps->empty() && !crowned) {
            Move *newMove = getLegalMove();
         *//*  this will not work now *//*if (Rules::validMultiCapture(newMove, board)) {
                // Check if the piece is crowned this turn and if so the turn
                // must end even if another capture is available
                crowned = crownMe(newMove);

                // When the move is valid we delete the old jumps and get a new
                // one to see if there is another jump available
                delete jumps;
                jumps = Rules::getJumpsAtPos(newMove->getCurRow(), newMove->getCurCol(), board);

                // when we have a valid move push the move to the board
                //board->move(newMove, false);
                destroyMe->push_back(curMove);
                curMove = newMove;
            } else {
                std::cout << "not valid multi capture" << std::endl;
                delete newMove;
            }
        }

        destroyMe->erase(destroyMe->begin(), destroyMe->end());
        delete destroyMe, jumps;
*/
        // Change the turn



        // check if the game is over
        if (board->getRedCount() == 0 || board->getWhiteCount() == 0)
            gameOver = true;
    }
}

Move* GameManager::getLegalMove() {
    Move *currentMove;

    // while the move is not valid ask for a new move
    bool validMove = false;
    while (!validMove) {
        // first print the board
        board->printBoard();

        // call getMove to request the next move from the current player
        currentMove = getMove(board);
        // check if the move is valid
        validMove = Rules::legalMoveFromColor(currentMove, board);

    }
    return currentMove;
}



Move *GameManager::getMove(Board *bs) {
    Move* currentMove;
    switch (bs->getTurn()) {
        case RED:
            currentMove = player1->getMove(bs);
            break;
        case WHITE:
            currentMove = player2->getMove(bs);
            break;
        default:
            std::cout << "Error" << std::endl;
    }
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