#include "and.h"
#include <iostream>

void And::printToFile(std::ofstream& of) {
    of << "\t" << id << "[shape=box width=0.4 height=0.7 label=\"&\"]" << std::endl;
    for (Gate* a : inputs) {
        a->printToFile(of);
        of << std::endl << "\t" <<a->getId() << "--" << id <<std::endl;
    }
}