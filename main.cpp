#include <iostream>
#include <fstream>
//#include "kapuk.h"

using namespace std; 

int main() {
    std::string input;
    int closeBracId;
    int openBracId;

    cin >> input;
    std::string gate;
    
    for (int i = 0; input[i] != ')'; i++)
    {      
        if (input[i] == '(') {
            openBracId = i;
        }
        closeBracId = i+1;
    }

    for (int i = 0; i + openBracId < closeBracId+1; i++)
    {
        gate += input[i + openBracId];
    }
    

    cout << openBracId << ' ' << closeBracId << endl;
    cout << gate << endl;
    return 0;
}


/* ((A*B*C)+(B*-C))*B   */