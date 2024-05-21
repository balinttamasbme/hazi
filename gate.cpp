#include "gate.h"

int Gate::base = 0;

void Gate::printInputs() const {
    std::cout << "ID:" << id << std::endl;
    for (const Gate* a : inputs) {
        a->printInputs();
    }
}

void Gate::printType() const{
    std::cout << "Gate" << std::endl;
}

void Gate::printToFile(std::ofstream& of) {
    of << "\t" << id << "[shape=box, width=0.01, label=\"&\"]" << std::endl;
    for (Gate* a : inputs) {
        a->printToFile(of);
        of << std::endl << "\t" <<a->getId() << "--" << id << std::endl;
    }
}