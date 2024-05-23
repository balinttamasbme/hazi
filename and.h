#pragma once

#include "gate.h"
#include <iostream>

class And : public Gate {
public: 
    void printToFile(std::ofstream&) override;
};