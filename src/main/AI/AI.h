//
// Created by Luke on 2/8/2019.
//

#ifndef CHECKERS_01_AI_H
#define CHECKERS_01_AI_H


#include "../POCO/Move.h"
#include "Node.h"
#include "MinimaxTree.h"
#include "../misc/Player.h"

class AI : public Player{

public:
    Move *getMove(Board *boardState) override;

    /**
     * Create an instance of the AI class implementing player
     * @param lookAhead the number if moves to look ahead
     */
    AI(int lookAhead);
private:
    int lookAhead;
    int random(int low, int high);
    int evaluateBoardState(Node* node);
    Node* minimax(Node* node, int depth, bool maximizingPlayer);
    int max(Node *n1, Node *n2);
    int min(Node *n1, Node *n2);
    Node* makeTree(Board* bs);
};


#endif //CHECKERS_01_AI_H
