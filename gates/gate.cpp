#include "gate.h"

//statikus idBase beállítása
int Gate::idBase = 0;

void Gate::printToFile(std::ofstream& of) {}

std::ofstream& operator<<(std::ofstream& ofStream, Gate* gatePrint){
    ofStream << "\t" << gatePrint->getId() << gatePrint->getParameters() << std::endl;

    //hozzá kapcsolódó Gate objektumok magához kapcsolása, illetve azok fájlba nyomtatása
    for (Gate* a : gatePrint->inputs) {
        
        ofStream << a;
        ofStream << std::endl << "\t" << a->getId() << "--" << gatePrint->getId() << std::endl;
    }

    return ofStream;
};