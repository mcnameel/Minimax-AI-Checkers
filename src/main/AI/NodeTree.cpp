//
// Created by Luke McNamee on 2019-04-04.
//

//#include "../../../include/internal/NodeTree.h"

#include <iostream>

class NodeTree
{
public:
    void operator()() {
        std::cout << "functor\n";
    }
};