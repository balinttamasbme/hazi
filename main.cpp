#include <iostream>
#include <fstream>
#include "kapuk.h"

using namespace std; 

int main() {
    
    ofstream myfile;

    myfile.open ("diagram.txt");
    char a = 'A';
    char b = 'B';
    myfile << "digraph{" << a << "->" << b <<"}";
    cout << "kuki";
    myfile.close();
    return 0;
}
