#pragma once

#include "gate.h"
#include <iostream>

class Or : public Gate {
public:
    Or() = default;
    Or( std::vector<Gate*> i): Gate(i){}

    void printInputs() const override;
    void printType() const override;
    void printToFile(std::ofstream&) override;
};