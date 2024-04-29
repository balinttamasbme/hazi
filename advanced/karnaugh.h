#ifndef KARNAUGH_H
#define KARNAUGH_H

class Karnaugh{
    private:
        int variableNum;
        int x;
        int y;
        int dimensions[4][2];
    public:
        Karnaugh(int const);
        void displayKarnaugh(int const) const;
};

#endif