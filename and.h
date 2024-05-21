#pragma once

#include "gate.h"
#include <iostream>

class And : public Gate {
public: 
    And() = default;
    And( std::vector<Gate*> i): Gate(i){}
    
    void printInputs() const override;
    void printType() const override;
    void printToFile(std::ofstream&) override;
};