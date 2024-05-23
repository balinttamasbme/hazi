#pragma once

#include "gate.h"
#include <iostream>

class Or : public Gate {
public:
    void printToFile(std::ofstream&) override;
};