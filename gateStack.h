#pragma once

#include <vector>
#include "gates/gate.h"

class GateStack{
    std::vector<Gate*> stack;
public:
    GateStack(){};
    void push_back(Gate*);
    Gate* back(){return stack.back();}

    unsigned size(){return stack.size();}

    ~GateStack();

    Gate* operator[](const unsigned);
};

