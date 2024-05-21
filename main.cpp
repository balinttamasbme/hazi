#include <iostream>
#include <fstream>
#include <vector>

#include "gate.h"
#include "or.h"
#include "and.h"
#include "value.h"

std::vector<std::string> stringStack;
std::vector<Gate *> idStack;

void parseBraces(std::string const& input){
    int i = 0;
    
    while (input[i] != '\0' && i < input.length()) {
        
        std::string gate;
        int closeBracId = -1;
        int openBracId = -1;

        while (input[i] != ')' ) {      
            if (input[i] == '(' ) {
                openBracId = i;
            }
            closeBracId = ++i;
        }

        if (openBracId == -1) {
            break;
        }
        
        for (int a = 0; a + openBracId < closeBracId + 1; a++) {
            gate += input[a + openBracId];
        }
        
        stringStack.push_back(gate);

        i++;
    }
}

Gate* createGate(std::string const& input){
    for (char a : input) {
        if (a == '+') {
            Gate *ret = new Or();
            idStack.push_back(ret);
            return ret;
        } else if (a == '*') {
            Gate *ret = new And();
            idStack.push_back(ret);
            return ret;
        }
    }
}

std::vector<Gate*> createInput(std::string const&  input){
   std::vector<Gate*> toReturn;
   std::string toValue;
   for (int i = 0; i < input.length(); i++) {
        if(input[i] >= 'A' && input[i] <= 'Z') {
            toValue = input[i];
            if (input[i-1] == '!' ) {
                toValue += '\'';
                std::cout << toValue << " ";
            }
            std::cout << toValue;
            Gate *ret = new Value(toValue);
            idStack.push_back(ret);
            toReturn.push_back(ret);
        }
    }
    return toReturn;
}

void printGraph(std::string const& fname, Gate *front){
    std::ofstream myfile;
    myfile.open(fname);
    myfile << "graph { " << std::endl << "\trankdir=\"LR\" " << std::endl;
    front->printToFile(myfile);
    myfile << "\tF[shape = plaintext]" << std::endl;
    myfile << "\t" << front->getId() << "--" << "F" << std::endl;
    myfile << "}";
    myfile.close();
}

int main() {
    
    std::string inputOrigin;
    std::string inputWork;

    std::cin >> inputOrigin;
    inputWork = inputOrigin;

    parseBraces(inputWork);

    Gate* asd = createGate(stringStack[0]);
    asd->inputs = createInput(stringStack[0]);

    Gate* asdNew = createGate(stringStack[1]);
    asdNew->inputs = createInput(stringStack[1]);

    Or orGate;
    orGate.inputs.push_back(asd);
    orGate.inputs.push_back(asdNew);
    
    //orGate.printInputs();

    printGraph("proba.txt", &orGate);

    std::cout << std::endl;

    return 0;
}

/* (A*!D)+(D*!C)*C */