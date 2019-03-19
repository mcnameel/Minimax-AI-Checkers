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
    int minimax(Node* node, int depth, bool maximizingPlayer);
    int minimaxAB(Node* node, int depth, bool maximizingPlayer, int alpha, int beta);
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
    static int random(int low, int high);
    int evaluateBoardState(Node* node);

    int maxNode(Node *n1, Node *n2);
    int minNode(Node *n1, Node *n2);
    int max(int val1, int val2);
    int min(int val1, int val2);
    };


#endif //MINIMAX_AI_CHECKERS_AI_H
