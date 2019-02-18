//
// Parser implements player
// Parser is a class which represents a human player by getting input from the
// terminal.
//
// Created by Luke on 1/28/2019.
//

#ifndef CHECKERS_01_PARSER_H
#define CHECKERS_01_PARSER_H


#include <iostream>
#include "Move.h"
#include "Player.h"

class Parser: public Player {
private:
    /* vars */
    char color;
    // Amount to use to convert the ascii value input into the proper int
    const int ROW_SHIFT = 48;
    const int COLUMN_SHIFT = 97;

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
     * @param color
     */
    Parser(char color);
    Move* getMove() {
        std::string in = "";
        std::cout << "\nEnter the current then destination square separated "
            << "by a \'->\' \n(aka a2->b3): ";

        std::cin >> in;
        while(!validateInput(in)) {
            std::cout << "Please enter only values matching the regex "
            << "[a-h][0-7]->[a-h][0-7]: ";
            std::cin >> in;
        }
        return convertInput(in);
    }

    /**
     * Translates character column into its numerical value
     * @param a
     * @return number value of the column
     */
    static int translateMove(char a);

    /**
     * Translates numerical column value into its character value
     * @param i
     * @return character value of the column
     */
    static char translateBack(int a);
};

#endif //CHECKERS_01_PARSER_H
