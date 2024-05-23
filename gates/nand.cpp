#include "nand.h"
#include <iostream>

/**
 * @brief Ez a kapu saját dot nyelvű fájlba való kííró függvénye \n
 * \b Bemenet: 
 * 1. ofStream: file out stream \n
 */
void Nand::printToFile(std::ofstream& ofStream) {
    //alap tulajdonságok
    ofStream << "\t" << id << parameters << std::endl;

    //hozzá kapcsolódó Gate objektumok magához kapcsolása, illetve azok printToFile() függvényének meghívása
    for (Gate* a : inputs) {
        a->printToFile(ofStream);
        ofStream << std::endl << "\t" <<a->getId() << "--" << id <<std::endl;
    }
}