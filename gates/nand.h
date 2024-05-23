#pragma once

#include "gate.h"
#include <iostream>

class Nand : public Gate {
public: 
    //a shift operátorhoz kell
    Nand(){parameters = "[shape=box width=0.4 height=0.7 label=\"&\'\"]";}
    void printToFile(std::ofstream&) override;
};