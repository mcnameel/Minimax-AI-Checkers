//
// Created by Luke on 1/28/2019.
//

#include "Board.h"
#include "Rules.h"
#include <iostream>

Board::Board() {
    // populate the board by iterating through the board, row then column,
    // to populate the board with pieces
    /*for(int i = 0; i < 8; ++i) {
        // iterate through each column to add the piece. For each column
        // multiply j by two then add the modulus of i to get the offset for
        // each odd column.
       for (int j = 0; j < 4; ++j) {
            // the player2 pieces go from rows 1-3
            if(i < 3) {
                // add a player2 piece to the board and to the container set
                Checker* c = new Checker(WHITE, i, 2 * j + (i % 2));
                whitePieces->push_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
            // the player1 pieces go from rows 1-3
            else if(i > 4) {
                // add a player1 piece to the board and to the container set
                Checker* c = new Checker(RED, i, 2 * j + (i % 2));
                redPieces->push_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
        }
    }
    */
     // For testing purposes
    Checker* c1 = new Checker(RED, 4, 2);
    Checker* c2 = new Checker(WHITE, 3, 1);
    Checker* c3 = new Checker(WHITE, 1, 1);
    Checker* c4 = new Checker(WHITE, 1, 3);
   // Checker* c5 = new Checker(WHITE, 3, 3);
    Checker* c6 = new Checker(WHITE, 5, 5);
    c1->makeKing();
    grid[4][2] = c1;
    grid[3][1] = c2;
    grid[1][1] = c3;
    grid[1][3] = c4;
   // grid[3][3] = c5;
    grid[5][5] = c6;

    redPieces->push_back(c1);
    whitePieces->push_back(c2);
    whitePieces->push_back(c3);
    whitePieces->push_back(c4);
   // whitePieces->push_back(c5);
    whitePieces->push_back(c6);

}

void Board::printBoard() {
    for (int r = 7; r >= 0; r--) {
        std::cout << "  |-------------------------------|" << std::endl;
        std::cout << r << " ";
        for (int c = 0; c < 8; c++) {
            std::cout << "|";
            if (grid[r][c] != nullptr)
                std::cout << " " << grid[r][c]->getColorChar() << " ";
            else std::cout << "   ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "   -------------------------------   ";
    std::cout << "player 1: " << getWhitePieces()->size() << std::endl;
    std::cout << "    a   b   c   d   e   f   g   h    ";
    std::cout << "player 2: " << getRedPieces()->size() << std::endl;
    std::string turn = (getTurn() == RED) ? PLAYER_ONE_COLOR : PLAYER_TWO_COLOR;
    std::cout << turn + "'s turn" << std::endl;
}

bool Board::contains(int row, int col) {
    return (grid[row][col] != nullptr);
}

Checker* Board::getAt(int row, int col) {
    return grid[row][col];
}

void Board::move(Move *move, bool dontClear, bool changeTurn) {
    Checker* c = grid[move->getCurRow()][move->getCurCol()];

    Move* temp = move;
    while(temp != nullptr) {

        // remove the piece from the starting space then move it to the next
        grid[temp->getCurRow()][temp->getCurCol()] = nullptr;
        grid[temp->getDestRow()][temp->getDestCol()] = c;

        // set the destination vars
        c->setRow(temp->getDestRow());
        c->setCol(temp->getDestCol());

        // if the move is a king move then set the piece to be a king
        if (temp->getKingMove())
            c->makeKing();

        // Check if piece should be deleted
        if (temp->getCapCol() != -1) {

            Checker *cap = grid[temp->getCapRow()][temp->getCapCol()];
            grid[temp->getCapRow()][temp->getCapCol()] = nullptr;

            if (temp->getColor() == RED) {
                removePiece(cap);
            } else {
                removePiece(cap);
            }
            delete cap;
        }
        temp = temp->getChainMove();
    }
    if(changeTurn) {
        Color curTurn = (getTurn() == RED) ? WHITE : RED;
        setTurn(curTurn);
    }
    Move* tempDel = lastMove;
    movesToDelete->push_back(tempDel);
    if(!dontClear){
        movesToDelete->clear();
    }
    lastMove = move;
}

std::vector<Checker*>* Board::getRedPieces() {
    return redPieces;
}

std::vector<Checker*>* Board::getWhitePieces() {
    return whitePieces;
}

int Board::getRedCount() {
    return redPieces->size();
}

int Board::getWhiteCount() {
    return whitePieces->size();
}

void Board::removePiece(Checker *c) {
    std::vector<Checker*>* deleteFromMe;
    if(c->getColor() == RED)
        deleteFromMe = getRedPieces();
    else
        deleteFromMe = getWhitePieces();

    auto it = deleteFromMe->begin();
    bool found = false;
    while(!found) {
        if(*it == c) {
            deleteFromMe->erase(it);
            found = true;
        }
        ++it;
    }
}

Board::Board(std::vector<Checker *> *startState, Color turn) {
    this->turn = turn;
    this->boardGrid = boardGrid;
    for (auto &piece : *startState) {
        grid[piece->getRow()][piece->getCol()] = piece;
        if(piece->getColor() == RED)
            redPieces->push_back(piece);
        else
            whitePieces->push_back(piece);
    }
}

void Board::setLastMove(Move *lastMove) {
    this->lastMove = lastMove;
}

Move *Board::getLastMove() {
    return lastMove;
}

Board *Board::copy() {
    static int i = 0;
    auto *pieces = new std::vector<Checker *>();
    for(auto &r : *redPieces) {
        Checker* c = r->copy();
        pieces->push_back(c);
        ++i;
    }
    for(auto &w : *whitePieces) {
        pieces->push_back(w->copy());
    }
    return new Board(pieces, getTurn());
}

Color Board::getTurn() {
    return turn;
}

void Board::setTurn(Color color) {
    this->turn = color;
}




