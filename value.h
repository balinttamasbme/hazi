#pragma once

#include "gate.h"
#include <iostream>

class Value : public Gate {
    std::string data;
public:
    Value();
    Value(std::string a): Gate(), data(a){}

    void setData(char d){data = d;}

    void printToFile(std::ofstream&) override;
};