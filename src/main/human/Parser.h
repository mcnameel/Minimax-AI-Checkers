//
// Parser implements player
// Parser is a class which represents a human player by getting input from the
// terminal.
//
// Created by Luke on 1/28/2019.
//

#ifndef MINIMAX_AI_CHECKERS_PARSER_H
#define MINIMAX_AI_CHECKERS_PARSER_H


#include <iostream>
#include "../POCO/Move.h"
#include "../misc/Player.h"
#include "../misc/Color.h"
#include "../Board.h"

class Parser: public Player {
private:
    /* vars */
    // Amount to use to convert the ascii value input into the proper int
    const int ROW_SHIFT = 48;
    const int COLUMN_SHIFT = 97;

    Move *getMove(Board *boardState) override;

    /**
     * Checks if the input matches the regex [a-h][0-7]->[a-h][0-7]
     *  WARNING: this only checks the regex, it will return any illegal moves
     *           as valid.
     * @param in the input string
     * @return true if the input can be translated into a move
     */
    bool validateInput(std::string in);

    /**
     * Converts a string into a move from the regex [a-h][0-7]->[a-h][0-7]
     *  (aka a2->b3)
     * @param in input string
     * @return a pointer to a move object
     */
    Move* convertInput(std::string in);

public:
    /**
     * Initialize a parser to get input from a human player
     * @param color enum type of color, either red or black
     */
    explicit Parser(Color color);
};

#endif //MINIMAX_AI_CHECKERS_PARSER_H
