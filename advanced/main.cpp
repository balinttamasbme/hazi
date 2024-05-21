#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include "kapuk.h"

using namespace std;

std::vector<std::string> stringStack;

void parseBraces(std::string input){
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

int main() {
    std::string input;
    cin >> input;
    
    parseBraces(input);
    
    for (string i : stringStack) {
        cout << i << endl;
    }

    return 0;
}


/* ((A*B*C)+(B*-C)*(A*S*C)+(S*-C)) */