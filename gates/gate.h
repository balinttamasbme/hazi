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
    
    //az algoritmusok helyes működéséhez elengedhetetlen
    int getId() const {return id;}
    std::string getParameters() const{return parameters;}

    virtual void printToFile(std::ofstream&);

};
//fájlba printeléshez
std::ofstream& operator<<(std::ofstream&, Gate*);