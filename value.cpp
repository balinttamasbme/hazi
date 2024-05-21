#include "value.h"
#include <iostream>

void Value::printInputs() const {
    std::cout << "Value: " << data << ", ID:" << id << std::endl;
}

void Value::printType() const{
    std::cout << "Value" << std::endl;
}

void Value::printToFile(std::ofstream& of) {
    of << "\t" << id <<"[shape=plaintext label=\"" << data << "\"]";
}