#pragma once

#include <iostream>
#include <vector>

class Input {
    char inputName;
    bool value;
    public:
        Input(char const n,int const v) {inputName = n; value = 0;}

        char getInputName() const {return inputName;}
        int getValue() const {return value;}
        void printInput() const;

};  

class Kapu {
    private:
        char name[5];
        std::vector<Kapu const&> inputs;
        bool inputValue[4];
        /* std::vector<const Kapu&> inputs;
            
            bool output;
            char type; //pl. '*', '+'
            void setOutput()
            {
                switch (type):
                    case '*':
                        for 
        
        A B C D
        0 1 1 0
            }
        */
    public:
        void addInput(Kapu const &in) {
            inputs.push_back(in);
        }

        void printInput() const{
            std::cout<< "asdasd";
        }

        void print() {
            for (const Kapu& input : inputs) {
                input.printInput();
            }
            
        }
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
