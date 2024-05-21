#include "or.h"
#include <iostream>

void Or::printType() const{
    std::cout << "Or" << std::endl;
}

void Or::printInputs() const {
    std::cout << "ID:" << id << std::endl;
    for (const Gate* a : inputs) {
        a->printInputs();
    }
}

void Or::printToFile(std::ofstream& of) {
    of << "\t" << id << "[shape=box, width=0.01, label=\">=1\"]" << std::endl;
    for (Gate* a : inputs) {
        a->printToFile(of);
        of << std::endl << "\t" <<a->getId() << "--" << id << std::endl;
    }
}