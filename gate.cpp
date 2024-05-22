#include "gate.h"

int Gate::base = 0;

void Gate::printInputs() const {
    std::cout << "ID:" << id << std::endl;
    for (const Gate* a : inputs) {
        a->printInputs();
    }
}

void Gate::printToFile(std::ofstream& of) {}