//
// Created by Luke on 2/8/2019.
//

#ifndef MINIMAX_AI_CHECKERS_AI_H
#define MINIMAX_AI_CHECKERS_AI_H


#include "../POCO/Move.h"
#include "Node.h"
#include "MinimaxTree.h"
#include "../misc/Player.h"

class AI : public Player{

public:
    Move *getMove(Board *boardState) override;
    Node* minimax(Node* node, int depth, bool maximizingPlayer);
    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead
     */
    AI(int lookAhead, Color color);

    Node* makeTree(Board* bs);

private:
    static const int MAX =  32767;
    static const int MIN =  -32767;
    int lookAhead;
    int random(int low, int high);
    int evaluateBoardState(Node* node);

    int max(Node *n1, Node *n2);
    int min(Node *n1, Node *n2);
};


#endif //MINIMAX_AI_CHECKERS_AI_H
