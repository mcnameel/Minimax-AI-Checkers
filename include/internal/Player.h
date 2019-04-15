#include <utility>

//
// Created by Luke on 1/28/2019.
//

#ifndef MINIMAX_AI_CHECKERS_PLAYER_H
#define MINIMAX_AI_CHECKERS_PLAYER_H

#include "Move.h"
#include "Board.h"
/**
 * This class represents one of the two players. A class which implements this
 * class needs to define the getMove() function so the
 */
class Player {

public:
    /* constructor */
    explicit Player(Color playerColor, std::string name) {
        this->playerColor = playerColor;
        this->name = std::move(name);
    }

    /* pure virtual methods */
    /**
     * Gets a move from a either a human player or an AI
     * @return pointer to a move the player wishes to make
     */
    virtual Move *getMove(Board *boardState) = 0;
    virtual ~Player() = default;

    /* accessor */
    Color getColor() {
        return playerColor;
    }

    // accessor
    const std::string &getName() const {
        return name;
    }
private:
    /* field vars */
    Color playerColor;
    std::string name;
};

#endif //MINIMAX_AI_CHECKERS_PLAYER_H

