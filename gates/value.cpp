#include "value.h"
#include <iostream>

void Value::printToFile(std::ofstream& of) {
    of << "\t" << id <<"[shape=plaintext width=0.1 height=0.1 label=\"" << data << "\"]";
}