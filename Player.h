//
// This class represents one of the two players. A class which implements this
// class needs to define the getMove() function so the
//
// Created by Luke on 1/28/2019.
//

#ifndef CHECKERS_01_PLAYER_H
#define CHECKERS_01_PLAYER_H

#include "Move.h"

class Player {
public:
    /**
     * Gets a move from a either a human player or an AI
     * @return pointer to a move the player wishes to make
     */
    virtual Move* getMove() = 0;
};

#endif //CHECKERS_01_PLAYER_H
