#pragma once

#include "gate.h"
#include <iostream>

class Value : public Gate {
    std::string data;
public:
    //a shift operátorhoz kell
    Value(){parameters = "[shape=plaintext width=0.1 height=0.1 label=\"";};
    
    //ez lesz az az érték, ami a gráfon címkeként majd megjelenik
    Value(std::string a): Gate(){
        data = a;
        parameters = "[shape=plaintext width=0.1 height=0.1 label=\"";
        parameters += data;
        parameters += "\"]";
    }


    void setData(char d){data = d;}

    void printToFile(std::ofstream&) override;

    ~Value();
};