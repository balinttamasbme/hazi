#include "gateStack.h"

void GateStack::push_back(Gate* toPush){
    stack.push_back(toPush);
}

Gate* GateStack::operator[](const unsigned a){
    return stack[a];
};