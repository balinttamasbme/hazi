/**
 * \mainpage Bálint Tamás (CM1JC2) - Programozás alapjai 2. : Házifeldat 
 * 
 * \section intro_sec Bevezetés
 * 
 * A házifeldatom kombinációs hálózatokról szól. Egy tetszőleges inputból felépít egy hálózatot objektumokkal és kirajzolja azt gráfként valamint megadja az igazságtáblázatát.
 * Alapvetően az inputot szintenként dologzom fel, először az input value-kat helyettesítem a id-jukkal (amely megegyezik a gateStackben elfoglalt helyükkel is) a stringben, majd ezt fogom a továbbiakban feldolgozni. \n
 * A működés szemléltetése az alábbi stringgel: \n
 * 1. "(((A*!D)+(D*!C))*C)" \n
 * 2. "(((0*1)+(2*3))*4)" \n
 * 3. "((5+6)*4)" \n
 * 4. "(7*4)" \n
 * \section install_sec A mainben használt függvények
 * 
 * \subsection step1 1. Gate* createInput(std::string const&  input)
 * 
 * Ez a függvény felelős azért, hogy a kapott stringben minden betűre hozzon létre egy Value objektumot, azt elhelyezi a gateStack-en, majd visszatér a pointerével.  \n
 * Pl: (((A*!D)+(D*!C))*C) \n
 * (((0*1)+(2*3))*4) \n
 * 
 * \subsection step2 2. Gate* createGate(std::string const& input)
 * 
 * Ez a függvény felelős azért, hogy adott id-val rendelkező kapu kimeneteket összeköt megfelelő kaputípussal és elhelyezi a gateStacken. \n
 * 
 * Pl: (A*B) \n 
 * A-id = 0 \n
 * B-id = 1 \n
 * 
 * (0*1) -> And kapu, bemenetei a 0-s és az 1-es id-val rendelkező kapuk. Ezt a kaput elhelyezi a gateStack-ben és visszatér az adott kapu pointerével.
 * 
 * \subsection step3 3. bool containOper(std::string const& in)
 * 
 * Segédfüggvény, ha van még a stringben operátor, visszatér true-val;
 * 
 * \subsection step4 4. Gate* createSystem(std::string const& input)
 * 
 * Ez a függvény a többi függvény segítségével összeállítja a hálózatot, összekapcsolja a kapukat id-k segítéségével. A fent már bemutatott működés alapján dolgozza fel az inputot: \n
 * ((A*B)+(C*D)+E) \n
 * ((0*1)+(2*3)+4) \n
 * (5+6+4) \n
 * 7 \n
 * 
 * \subsection step5 5. void printGraph(std::string const& fname, Gate *front)
 * 
 * Egy tetszőleges fájlba létrehozza a gráfot dot nyelven. Graphviz-et használtam a gráf elkészítéséhez.
 * 
 * \subsection step6 6. bool doesInclude(const std::vector<char> &vect, char x)
 * 
 * Segédfüggvény. Azt vizsgálja meg, hogy a paraméterben kapott vektorban előfordul-e már a megadott karakter.
 * 
 * \subsection step7 7. std::string toBinary(const int num, const int size)
 * 
 * A kapott integert egy "size" bites bináris számmá alakítja. Az num bitjeivel össze "és"-eli az 1-et így megkapjuk, a num-ot binárisan.
 * 
 * \section use_sec Használat:
 * Mintabemenetek: \n
 * (A*B) \n 
 * ((A*B)+(C*D)+E) \n
 * (((A*B)+(C*D)+E)*((F*G)+(H*I)+!J)) \n
 * (((A*B)+(!C*D))+((!E*F)+(G*H))+((!I*J)+(K*L))) \n
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <bitset>
#include <cmath>
#include <string>

#include "gate.h"
#include "or.h"
#include "and.h"
#include "value.h"

std::vector<std::string> stringStack;
std::vector<Gate *> gateStack;


Gate* createInput(const std::string &input) {
    std::string toValue;

    if(input[input.length()-1] >= 'A' && input[input.length()-1] <= 'Z') {
        
        toValue = input[input.length()-1];
        if (input[0] == '!' ) {
            toValue += '\'';
        }
        Gate *ret = new Value(toValue);

        gateStack.push_back(ret);
        return ret;
    }
}

Gate* createGate(const std::string &input) {
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

bool containOper(const std::string &in) {
    for(char a : in) {
        if (a = '*' || '+') {
            return true;
        }
    }
    return false;
}

Gate* createSystem(const std::string &input) {
    std::string workString = input;
    std::string inputValue;
    
    for(int i = 0; i < workString.length(); i++) {
        if (workString[i] >= 'A' && workString[i] <= 'Z') {
            if (i > 0 && workString[i-1] == '!') {
                inputValue = workString[i-1];
                inputValue += workString[i];
                workString.replace(i-1, 2, std::to_string(createInput(inputValue)->getId()));
                i = i-1;
            } else {
                inputValue = workString[i];
                workString.replace(i, 1, std::to_string(createInput(inputValue)->getId()));
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

    return gateStack.back();
}

void printGraph(const std::string &fName, Gate *front) {
    std::ofstream oFile;
    oFile.open(fName);

    oFile << "graph { " << std::endl;
    oFile << "\trankdir=\"LR\" " << std::endl;
    oFile << "\tsplines=ortho " << std::endl;

    front->printToFile(oFile);

    oFile << "\tF[shape = plaintext]" << std::endl;
    oFile << "\t" << front->getId() << "--" << "F" << std::endl;
    oFile << "}";

    oFile.close();
}

/*----------------------------------------------------*/

bool doesInclude(const std::vector<char> &vect, char x) {
    for (char m : vect) {
        if(m == x) {
            return true;
        }
    }
    return false;
}

std::string toBinary(const int num, const int size) {
    std::string binaryStr ("");
    int check = 1;
    for(int i = 0; i < size; i++) {
        if((check & num) >= 1){
            binaryStr = "1" + binaryStr;
        } else {
            binaryStr = "0" + binaryStr;
        }
        check <<= 1;
    }

    return binaryStr;
}

bool valueOfBrace(const std::string &brace) {
    
    std::string workString = brace;
    std::vector<bool> valueStack;
    bool value;
    bool returnValue;

    char op;

    for (char a : brace) {
        if (a == '*' || a == '+'){
            op = a;
            break;
        }
    }

    std::vector<char> toReplace = {'+', '*', '(', ')'};
    
    for (char a : toReplace) {
        std::replace(workString.begin(), workString.end(), a, ' ');
    }

    std::stringstream ss(workString);

    while (ss >> value) {
        valueStack.push_back(value);
    }

    switch (op) {
    case '*':
        returnValue = 1;
        for (bool a : valueStack) {
            returnValue *= a;
        }
        return (bool)returnValue;

    case '+':
        returnValue = 0;
        for (bool a : valueStack) {
            returnValue += a;
        }
        return (bool)returnValue;

    default:
        break;
    }
}

bool evaluateOperation(const std::string &binaryValue, const std::vector<char> &variables, const std::string &operation) {
    
    std::string workString = operation;

    for(int i = 0; i < workString.length(); i++) {
        for (int z = 0; z < variables.size(); z++) {
            if (workString[i] == variables[z]) {
                workString[i] = binaryValue[z];
            }

            if (workString[i-1] == '!') {
                if (workString[i] == '0') {
                    workString[i] = '1';
                } else {
                    workString[i] = '0';
                }
                workString.erase(i - 1, 1);
                i-=1;
            }
        }
    }

    while (containOper(workString)) {
        int i = 0;

        if (workString[0] != '(') {
            break;
        }
        
        std::string subOp;
        
        int closeBracId = -1;
        int openBracId = -1;

        while (i < workString.length() && workString[i] != ')' ) {      
            if (workString[i] == '(' ) {
                openBracId = i;
            }
            closeBracId = ++i;
        }
        
        for (int a = 0; a + openBracId < closeBracId + 1; a++) {
            subOp += workString[a + openBracId];
        }
        
        if (openBracId != -1 && closeBracId != -1) {
            workString.replace(openBracId, closeBracId - openBracId + 1, std::to_string(valueOfBrace(subOp)));
            i = i - (closeBracId - openBracId + 1);
        }

        i++;
    }
    return (bool)(workString[0]-'0');
}

bool createTable(const std::string &input, const std::string &ofName) {
    std::string workString = input;
    std::vector<char> variables;

    std::ofstream ofStream;
    ofStream.open(ofName);

    for (char a : workString) {
        if (a >= 'A' && a <= 'Z' && !doesInclude(variables, a)) {
            variables.push_back(a);
        }
    }
    
    //bubble sort
    for (int i = 0; i < variables.size() - 1; i++) {
        for (int j = 0; j < variables.size()- i - 1; j++) {
            if (variables[j] > variables[j + 1]) {
                char temp = variables[j];
                variables[j] = variables[j + 1];
                variables[j + 1] = temp;
            }
        }
    }

    const int varNum = variables.size(); 
    
    for (char a : variables) {
        ofStream << a << "\t";
    }
    ofStream << "|\tF" << std::endl << std::endl;

    for (int i = 0; i < pow(2, varNum); i++) {
        std::string binaryNum = toBinary(i, varNum);
        for (int m = 0; m < varNum; m++) {
            ofStream << binaryNum[m] << "\t";
        }
        ofStream << "|\t";
        ofStream << evaluateOperation(binaryNum, variables, workString) << std::endl;
    }

    ofStream.close();
    
    return 0;
}

/*----------------------------------------------------*/

void freeStack(){
    std::vector<Gate *> gateStack;

    for (Gate* a : gateStack) {
        delete[] a;
    }

    for (std::string a : stringStack) {
        delete[] &a;
    }
}

int main() {
    std::string function;
    std::string graphFile;
    std::string tableFile;

    std::cout << "Kerem adja meg a halozat fuggvenyet: " << std::endl;
    std::cin >> function;

    std::cout << "Kerem adja meg a graf celfajlanak nevet: " << std::endl;
    std::cin >> graphFile;

    std::cout << "Kerem adja meg a graf celfajlanak nevet: " << std::endl;
    std::cin >> tableFile;

    printGraph(graphFile, createSystem(function));

    createTable(function, tableFile);

    return 0;
}