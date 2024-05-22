#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "gate.h"
#include "or.h"
#include "and.h"
#include "value.h"

std::vector<std::string> stringStack;
std::vector<Gate *> gateStack;


Gate* createGate(std::string const& input) {
    std::string workString = input;
    int idIn;
    
    std::vector<char> toReplace = {'+', '*', '(', ')'};
    Gate *ret;

    for (char a : workString) {
        if (a == '+') {
            ret = new Or();
            gateStack.push_back(ret);
            break;
        } else if (a == '*') {
            ret = new And();
            gateStack.push_back(ret);
            break;
        }
    }

    for (char a : toReplace) {
        std::replace(workString.begin(), workString.end(), a, ' ');
    }

    std::stringstream ss(workString);

    while (ss >> idIn) {
        ret->inputs.push_back(gateStack[idIn]);
    }

    return ret;
}

int createInput(std::string const&  input) {
    std::string toValue;

    if(input[input.length()-1] >= 'A' && input[input.length()-1] <= 'Z') {
        
        toValue = input[input.length()-1];
        if (input[0] == '!' ) {
            toValue += '\'';
        }
        Gate *ret = new Value(toValue);

        gateStack.push_back(ret);
        return ret->getId();
    }
}

void printGraph(std::string const& fname, Gate *front) {
    std::ofstream myfile;
    myfile.open(fname);
    myfile << "graph { " << std::endl << "\trankdir=\"LR\" " << std::endl;
    myfile << "\tsplines=ortho " << std::endl;


    front->printToFile(myfile);


    myfile << "\tF[shape = plaintext]" << std::endl;
    myfile << "\t" << front->getId() << "--" << "F" << std::endl;
    myfile << "}";
    myfile.close();
}

bool containOper(std::string const& in){
    for(char a : in) {
        if (a = '*' || '+') {
            return true;
        }
    }
}

void createSystem(std::string const& input) {
    std::string workString = input;
    std::string inputValue;
    
    for(int i = 0; i < workString.length(); i++) {
        if (workString[i] >= 'A' && workString[i] <= 'Z') {
            if (i > 0 && workString[i-1] == '!') {
                inputValue = workString[i-1];
                inputValue += workString[i];
                workString.replace(i-1, 2, std::to_string(createInput(inputValue)));
                i = i-1;
            } else {
                inputValue = workString[i];
                workString.replace(i, 1, std::to_string(createInput(inputValue)));
            }
        }
    }
    
    while (containOper(workString)) {
        int i = 0;

        if (workString[0] != '(') {
            break;
        }
        
        std::string gate;
        
        int closeBracId = -1;
        int openBracId = -1;

        while (i < workString.length() && workString[i] != ')' ) {      
            if (workString[i] == '(' ) {
                openBracId = i;
            }
            closeBracId = ++i;
        }
        
        for (int a = 0; a + openBracId < closeBracId + 1; a++) {
            gate += workString[a + openBracId];
        }

        Gate *toPush = createGate(gate);

        if (openBracId != -1 && closeBracId != -1) {
            workString.replace(openBracId, closeBracId - openBracId + 1, std::to_string(toPush->getId()));
            i = i - (closeBracId - openBracId + 1);
        }

        i++;
    } 
}

int main() {
    createSystem("(((((A*B)+(C*D)+E)*(((F*G)+(H*I)+!J)))*((((K*L)+(M*N)+O)*(((P*Q)+(R*S)+!T))))))");
    
    printGraph("proba.txt", gateStack.back());

    return 0;
}

/* (A*B) */
/* ((A*B)+(C*D)+E) */
/* (((A*B)+(C*D)+E)*((F*G)+(H*I)+!J)) */
/* (((((A*B)+(C*D)+E)*(((F*G)+(H*I)+!J)))*((((K*L)+(M*N)+O)*(((P*Q)+(R*S)+!T))))))*/