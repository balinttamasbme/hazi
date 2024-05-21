#include "kapuk.h"
#include <vector>
#include <iostream>

void Kapu::printInputs() const {
    for (Kapu* a : inputs) {
        a->printInputs();
    }
}

void Value::printInputs() const{
    std::cout << value << std::endl;
    std::cout << "done" << std::endl;
}

void And::printInputs() const{
    for(Kapu *a : inputs){
        a->printInputs();
    }
}