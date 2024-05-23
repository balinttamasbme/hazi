#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class Gate {
protected:
    static int idBase;
    int id;
    std::string parameters;
public:
    std::vector<Gate*> inputs;

    Gate(){id = idBase++;}
    ~Gate() {delete[] &inputs;};
    
    int getId() const {return id;}
    std::string getParameters() const{return parameters;}

    virtual void printToFile(std::ofstream&);

};

std::ofstream& operator<<(std::ofstream&, Gate*);