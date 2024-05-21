#pragma once

#include "gate.h"
#include <iostream>

class Value : public Gate {
    std::string data;
public:
    Value() = default;
    Value(std::string a): Gate(), data(a){}

    void setData(char d){data = d;}

    void printInputs() const override;
    void printType() const override;
    void printToFile(std::ofstream&) override;
};