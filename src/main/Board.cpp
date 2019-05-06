//
// Created by Luke on 1/28/2019.
//

#include "../../include/internal/Board.h"
#include "../../include/internal/Rules.h"
#include <algorithm>    // std::find
#include <iostream>

Board::Board() {
    this->lastMove = nullptr;
    this->endgame = false;
    // populate the board by iterating through the board, row then column,
    // to populate the board with pieces
   for(int i = 0; i < getBOARD_HEIGHT(); ++i) {
        // iterate through each column to add the piece. For each column
        // multiply j by two then add the modulus of i to get the offset for
        // each odd column.
       for (int j = 0; j < getBOARD_WIDTH() / 2; ++j) {
            // the player2 pieces go from rows 1-3
            if(i < 3) {
                // add a player2 piece to the board and to the container set
                auto * c = new Checker(WHITE, i, 2 * j + (i % 2));
                whitePieces->emplace_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
            // the player1 pieces go from rows 1-3
            else if(i > 4) {
                // add a player1 piece to the board and to the container set
                auto * c = new Checker(RED, i, 2 * j + (i % 2));
                redPieces->emplace_back(c);
                grid[i][2 * j + (i % 2)] = c;
            }
        }
    }
}

Board::Board(const Board &board) : turn(board.turn), endgame(board.endgame) {
    for(auto &r : *board.redPieces) {
        // deleted with destructor of board copy
        auto *piece = new Checker(*r);
        grid[piece->getRow()][piece->getCol()] = piece;
        redPieces->emplace_back(piece);
    }
    for(auto &w : *board.whitePieces) {
        // deleted with destructor of board copy
        auto *piece = new Checker(*w);
        grid[piece->getRow()][piece->getCol()] = piece;
        whitePieces->emplace_back(piece);
    }
    Move *lastMoveCopy;
    if(board.lastMove != nullptr) {
        // deleted with destructor of board copy or next call of Board::move
        lastMoveCopy = new Move(*board.lastMove);
    } else {
        lastMoveCopy = nullptr;
    }
    lastMove = lastMoveCopy;
}

Board::Board(std::vector<Checker *> *startState, Color turn, Move *lastMove,
        bool endgame) {
    this->turn = turn;
    this->lastMove = lastMove;
    this->endgame = endgame;
    for (auto &piece : *startState) {
        grid[piece->getRow()][piece->getCol()] = piece;
        if(piece->getColor() == RED)
            redPieces->emplace_back(piece);
        else
            whitePieces->emplace_back(piece);
    }
}

Board::~Board() {
    for(auto & i : grid) {
        for (auto & j : i) {
            delete j;
        }
    }
    delete redPieces;
    delete whitePieces;
    delete lastMove;
}

void Board::removePiece(Checker *c) {
    std::vector<Checker *> *deleteFromMe;
    if (c->getColor() == RED)
        deleteFromMe = getRedPieces();
    else
        deleteFromMe = getWhitePieces();

    auto it = std::find(deleteFromMe->begin(), deleteFromMe->end(), c);
    if(it != deleteFromMe->end()) {
        deleteFromMe->erase(it);
    }
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
    std::cout << "White: " << getWhitePieces()->size() << std::endl;
    std::cout << "    a   b   c   d   e   f   g   h    ";
    std::cout << "Red:   " << getRedPieces()->size() << std::endl;
    std::string turn = (getTurn() == RED)
            ? getPLAYER_ONE_COLOR() : getPLAYER_TWO_COLOR();
    std::cout << turn + "'s turn" << std::endl;
}

bool Board::contains(int row, int col) {
    return (grid[row][col] != nullptr);
}

Checker* Board::getAt(int row, int col) {
    return grid[row][col];
}

void Board::move(Move *move, bool changeTurn) {
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
        if (temp->getKingMove()) {
            c->makeKing();
        }

        // Check if piece should be deleted
        if (temp->getCapCol() != -1) {

            Checker *cap = grid[temp->getCapRow()][temp->getCapCol()];
            grid[temp->getCapRow()][temp->getCapCol()] = nullptr;
            removePiece(cap);
            delete cap;
        }
        temp = temp->getNextChainMove();
    }
    handTurnChange(changeTurn);

    // if lastMove was not a chain move then set it to be deleted
    if(lastMove == nullptr) {
        // deleted at end of next time function is called or this destructor
        lastMove = move->copy();
    } else if(!lastMove->isChainMove()) {
        delete lastMove;
        // deleted at end of next time function is called or this destructor
        lastMove = move->copy();
    }
}

void Board::handTurnChange(bool changeTurn) {
    if(changeTurn) {
        Color curTurn = (getTurn() == RED) ? WHITE : RED;
        setTurn(curTurn);

        std::vector<Move*> *possibleMoves = Rules::getAllLegalMoves(this);
        // check if the game is over
        if(possibleMoves->empty()) {
            setGameOver(true);
        }
        // clean up
        for(auto &possibleMove : *possibleMoves) {
            delete possibleMove;
        }
        delete possibleMoves;
    }
}

std::vector<Checker*>* Board::getRedPieces() {
    return redPieces;
}

std::vector<Checker*>* Board::getWhitePieces() {
    return whitePieces;
}

int Board::getRedCount() {
    return static_cast<int>(redPieces->size());
}

int Board::getWhiteCount() {
    return static_cast<int>(whitePieces->size());
}

Move *Board::getLastMove() {
    return lastMove;
}

Color Board::getTurn() {
    return turn;
}

void Board::setTurn(Color color) {
    this->turn = color;
}

bool Board::isGameOver() const {
    return gameOver;
}

void Board::setGameOver(bool gameOver) {
    this->gameOver = gameOver;
}

bool Board::isEndgame() const {
    return endgame;
}

void Board::setEndgame(bool endgame) {
    Board::endgame = endgame;
}

// static functions
int Board::getBOARD_HEIGHT() {
    return 8;
}

int Board::getBOARD_WIDTH() {
    return 8;
}

std::string Board::getPLAYER_ONE_COLOR() {
    return "Red";
}

std::string Board::getPLAYER_TWO_COLOR() {
    return "White";
}
