#include "value.h"
#include <iostream>

void Value::printInputs() const {
    std::cout << "Value: " << data << ", ID:" << id << std::endl;
}

void Value::printToFile(std::ofstream& of) {
    of << "\t" << id <<"[shape=plaintext width=0.1 height=0.1 label=\"" << data << "\"]";
}