#pragma once

#include "gate.h"
#include <iostream>

class And : public Gate {
public: 
    And(){parameters = "[shape=box width=0.4 height=0.7 label=\"&\"]";}
    void printToFile(std::ofstream&) override;
};