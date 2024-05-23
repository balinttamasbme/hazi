#pragma once

#include "gate.h"
#include <iostream>

class Or : public Gate {
public:
    Or(){parameters = "[shape=box width=0.4 height=0.7 label=\"≥1\"]";}
    void printToFile(std::ofstream&) override;
};