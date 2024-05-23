#include "gateStack.h"

void GateStack::push_back(Gate* toPush){
    stack.push_back(toPush);
}

GateStack::~GateStack(){
    for (Gate* toFree : stack) {
        delete[] toFree;
    }
    stack.clear();
}

Gate* GateStack::operator[](const unsigned a){
    return stack[a];
};