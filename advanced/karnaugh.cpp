#include "karnaugh.h"
#include <iostream>

using namespace std;

Karnaugh::Karnaugh(int const dim){
    
}

void Karnaugh::displayKarnaugh(int const size)const{
    
    int matrix[4][4] = {{1,0,0,1}, {0,1,1,0}, {0,0,0,1}, {1,1,0,0}};  
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //cout << matrice[i][j] << " ";
        }
        cout << endl;
    }
}