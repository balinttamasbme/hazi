#ifndef KAPUK_H
#define KAPUK_H

#include <iostream>

using namespace std;

class Input {
    char inputName;
    int value;
    public:
        Input(char const n,int const v) {inputName = n; v > 1 || v < 0 ? value = -1 : value = v;}

        char getInputName() const {return inputName;}
        int getValue() const {return value;}
        void printInput() const;
};

class Kapu {
    private:
        char gateName[5];
        int inputNum;
        bool inputValue[4];
    public:
};

bool operator + (Input const &a, Input const &b) {
   if(a.getValue() == b.getValue()){} 

   return true;
}

/*
class And : Kapu{};

class Nand : Kapu{};

class Or : Kapu{};

class Nor : Kapu{};

class Not : Kapu{};
*/

#endif