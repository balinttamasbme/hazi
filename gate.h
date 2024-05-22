#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Gate {
protected:
    static int base;
    int id;
public:
    std::vector<Gate*> inputs;
    Gate(){id = base++;}
    Gate( std::vector<Gate*> i): inputs(i){id = base++;}
    
    int getId() const {return id;}

    virtual void printInputs() const;
    virtual void printToFile(std::ofstream&);
    
    virtual ~Gate() {delete[] &inputs;};
};