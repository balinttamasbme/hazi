#pragma once

#include <iostream>
#include <vector>

class Kapu { 
    public:
        std::vector<Kapu*> inputs;
        ~Kapu();

        virtual void printInputs() const;
};

class Value : public Kapu {
    private:
        char value;

    public:
        Value(const char a): value(a) {}

        void setValue(char a) {value = a;};
        //ertekkiiras
        void printInputs() const override;
};

class And : public Kapu{
    public:
        //ertekkiiras
        void printInputs() const override;
};