#pragma once

#include "gate.h"
#include <iostream>

class Nor : public Gate {
public:
    Nor(){parameters = "[shape=box width=0.4 height=0.7 label=\"≥1\'\"]";}
    void printToFile(std::ofstream&) override;
};