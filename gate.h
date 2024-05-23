#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "memtrace.h"

class Gate {
protected:
    /**/
    static int idBase;
    int id;
public:
    std::vector<Gate*> inputs;

    Gate(){id = idBase++;}
    ~Gate() {delete[] &inputs;};
    
    int getId() const {return id;}
    virtual void printToFile(std::ofstream&);
};