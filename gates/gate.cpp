#include "gate.h"

//statikus idBase beállítása
int Gate::idBase = 0;

void Gate::printToFile(std::ofstream& of) {}

/**
 * @brief Shift operátor, ami egyszerűbbé teszi a dolgok fájlba printelését \n
 * \b Bemenet: 
 * 1. ofStream: file out stream
 * 2. gatePrint: ezt a Gate-et printeljük ki \n
 */
std::ofstream& operator<<(std::ofstream& ofStream, Gate* gatePrint){
    ofStream << "\t" << gatePrint->getId() << gatePrint->getParameters() << std::endl;

    //hozzá kapcsolódó Gate objektumok magához kapcsolása, illetve azok fájlba nyomtatása
    for (Gate* a : gatePrint->inputs) {
        //meghívjuk a child elementre is a << operátort
        ofStream << a;
        //kapcsolat a child és a parent element között
        ofStream << std::endl << "\t" << a->getId() << "--" << gatePrint->getId() << std::endl;
    }

    return ofStream;
};