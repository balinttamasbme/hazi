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
 * \subsection step8 8. bool valueOfBrace(const std::string &brace)
 * 
 * A kapott zárójeles műveletről mondja meg, hogy igaz-e vagy hamis.
 * 
 * \subsection step9 9. bool evaluateOperation(const std::string &binaryValue, const std::vector<char> &variables, const std::string &operation)
 * 
 * A teljes függvényt kiértékeli egy adott bemeneti kombinációra. Több segédfüggvényt felhasznál ehhez.
 * 
 * \subsection step10 10. void createTable(const std::string &input, const std::string &ofName)
 * 
 * Mindent felhasználva ez adja meg minden bemeneti kombinációra a függvény értékét, majd ezt egy, a felhasználó által megadott fájl kiírja.
 * 
 * \subsection step11 11. void freeStack()
 * 
 * A dinamikusan foglalt tömb elemeit törli.
 * 
 * \section use_sec Használat:
 * 
 * \subsection step12 1. Függvény
 * A bemenetként egy zárójelezett bemenet kell legyen, minden szint külön zárójelet igényel.
 * 
 * Mintabemenetek: \n
 * (A*B) \n 
 * ((A*B)+(C*D)+E) \n
 * (((A*B)+(C*D)+E)*((F*G)+(H*I)+!J)) \n
 * (((A*B)+(!C*D))+((!E*F)+(G*H))+((!I*J)+(K*L))) \n
 * ((A*B+!C*D*E*(F+!G+H))+(I*!J*K*(L+M*!N*O)*P)+(Q*R*M+!F)+(P*C*I*A)+(C*B*(A*B*C*D*!E*F*G*H*I*J))) \n
 * 
 */

//szükséges könyvtárak
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <string>
#include "gate.h"
#include "or.h"
#include "and.h"
#include "value.h"
#include "memtrace.h"

//ebbe helyezem el az összes kaput, melyek id-jai megegyeznek a vektorban elfoglalt helyük indexével.
std::vector<Gate *> gateStack;

/**
 * @brief Segédfüggvény. Megvizsgálja, hogy a kapott string tartalmaz e számunkra fontos operátort. \n
 * \b Bemenet:
 * 1. input: string amiben keresünk \n
 */
bool containOper(const std::string &input) {
    //végighalad a stringen és megvizsgálja, hogy az adott karakter operátor-e.
    for(char a : input) {
        if (a == '*' || a == '+') {
            //ha tartalmaz operátort a string, visszatér igazzal
            return true;
        }
    }

    //egyébként visszatér hamissal
    return false;
}

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

    return nullptr;
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

/**
 * @brief Létrehoz és összefűz egy teljes "fát" a logikai függvényünk alapján \n
 * \b Bemenet:
 * 1. input: string ami a logikai függvényünket tárolja \n
 */
Gate* createSystem(const std::string &input) {
     //egy módosítható stringbe átmásolom a logikai függvényt
    std::string workString = input;

    //egy leendő Value kapunak az értéke, melyet a függvényből nyerünk ki
    std::string inputValue;
    
    //végighalad a függvényen és minden betű karakterre (hálózati bemenetre) létrehoz egy Value object-et
    for(unsigned i = 0; i < workString.length(); i++) {
        if (workString[i] >= 'A' && workString[i] <= 'Z') {
            if (i > 0 && workString[i-1] == '!') {
                //ha negált a bemenetünk, akkor a Value értéke pl.: "A'" lesz
                inputValue = workString[i-1];
                inputValue += workString[i];
                Gate * gotGate = createInput(inputValue);

                //hibakezelés
                if (gotGate != nullptr) {
                    //behelyettesítjük a létrehozott Value kapu id-ját a függvénybe
                    workString.replace(i-1, 2, std::to_string(createInput(inputValue)->getId()));
                    i = i-1;
                } else {
                    std::cout << "Hiba a Value letrehozasakor!" << std::endl;
                    return nullptr;
                }    
                
            } else {
                //egyébként meg szimplán létrehozza az objektumot
                inputValue = workString[i];
                Gate * gotGate = createInput(inputValue);
                
                //hibakezelés
                if (gotGate != nullptr) {
                    //behelyettesítjük a létrehozott Value kapu id-ját a függvénybe
                    workString.replace(i, 1, std::to_string(gotGate->getId()));
                } else {
                    std::cout << "Hiba a Value letrehozasakor!" << std::endl;
                    return nullptr;
                }
            }
        }
    }
    
    //majd többször végigjárjuk a függvényt és a benne lévő id-k ból és operátorokból kapukat hozunk létre megfelelő logikával
    while (containOper(workString)) {
        
        //a stringen belüli indexeléshez
        unsigned i = 0;
        
        //egy adott kapu, mely már csak az operátorát és a bemenetei id-it tartalmazza pl: (3*4)
        std::string subGate;
        
        //kezdő és záró id egy-egy adott szinten lévő kapuhoz
        int closeBracId = -1;
        int openBracId = -1;

        //megkeresi az első záró zárójel előtti utolsó nyitó zárójelet, ezek indexeit elmenti
        while (i < workString.length() && workString[i] != ')' ) {      
            if (workString[i] == '(' ) {
                openBracId = i;
            }
            closeBracId = ++i;
        }
        
        //a fent megtalált kaput kimásolja a gate stringbe
        for (int a = 0; a + openBracId < closeBracId + 1; a++) {
            subGate += workString[a + openBracId];
        }

        //létrehozzuk a kaput a subGate alapján
        Gate *toPush = createGate(subGate);

        //hibakezelés
        if (toPush != nullptr) {
            //behelyettesíti létrehozott kapu id-ját a kapu helyére a stringben
            if (openBracId != -1 && closeBracId != -1) {
                workString.replace(openBracId, closeBracId - openBracId + 1, std::to_string(toPush->getId()));
                
                //korrigálja az i-t
                i = i - (closeBracId - openBracId + 1);
            }

            i++;
        } else {
            std::cout << "Hiba a kapu letrehozasakor!" << std::endl;
            return nullptr;
        }
    }

    return gateStack.back();
}

/**
 * @brief Ez a függvény végzi a gráf fájlba nyomtatását. Kiírja a gráf létezéséhez szükséges paramétereket, kifejezéseket, majd elindítja a felépített objektum fa nyomtató algoritmusát. \n
 * \b Bemenet:
 * 1. fName: ide írjuk ki dot nyelvben a gráf paramétereit \n
 * 2. head: a legfelső szintű kapu pointere \n
 */
void printGraph(const std::string &fName, Gate *head) {
    //létrehozom a fájlstream-et
    std::ofstream ofStream;
    ofStream.open(fName);
    
    //hibakezeles
    if (ofStream) {
        //alap kifejezesek
        ofStream << "graph { " << std::endl;
        ofStream << "\trankdir=\"LR\" " << std::endl;
        ofStream << "\tsplines=ortho " << std::endl;

        //az objektum fa nyomtató algoritmusa
        head->printToFile(ofStream);

        //további paraméterek, illetve kimenet "F" hozzáadása, a jobb szemléltethetőség érdekében
        ofStream << "\tF[shape = plaintext]" << std::endl;
        ofStream << "\t" << head->getId() << "--" << "F" << std::endl;
        ofStream << "}";

        ofStream.close();
    } else {
        std::cout << "Hiba a fajl megnyitasakor" << std::endl;
        return;
    }
}

/*----------------------------------------------------*/

/**
 * @brief Segédfüggvény. Megvizsgálja, hogy a kapott karaktert tartalmazza-e a kapott vektor \n
 * \b Bemenet:
 * 1. vect: a vektor amiben keresünk \n
 * 2. toFind: ezt a karaktert keressük \n
 */
bool doesInclude(const std::vector<char> &vect, const char toFind) {
    for (char a : vect) {
        //ha tartalmazza a karaktert a vektor, visszatér igazzal
        if(a == toFind) {
            return true;
        }
    }

    //ha nem tartalmazza, akkor hamissal
    return false;
}

/**
 * @brief Segédfüggvény. A kapott számot bináris számmá alakítja, melyet string formájában ad vissza \n
 * \b Bemenet:
 * 1. num: a binárissá konvertálni kívánt szám \n
 * 2. size: a szám hosszúsága bináris formában (hány bites) \n
 */
std::string toBinary(const int num, const int size) {
    //a visszatéréshez üres string
    std::string binaryStr ("");
    
    //és-eléshez 1-es
    int check = 1;

    //helyiérték szerint ÉS műveletet hajtunk végre
    for(int i = 0; i < size; i++) {
        if((check & num) >= 1){
            //ha az adott biten a számban 1-es van, 1-est teszünk a binaryStr-be
            binaryStr = "1" + binaryStr;
        } else {
            //ha 0, 0-át
            binaryStr = "0" + binaryStr;
        }
        //majd shifteljük az ellenőrző 1-esünket balra egyel
        check <<= 1;
    }

    //végül visszatérünk az értékével
    return binaryStr;
}


/**
 * @brief Segédfüggvény. Egy adott kapu logikai kiértékelését végzi. \n
 * \b Bemenet:
 * 1. brace: stringben eltárolt kapu \n
 */
bool valueOfBrace(const std::string &brace) {
    //egy módosítható stringbe átmásolom a kaput
    std::string workString = brace;
    
    //a kapu bemeneteinek értékéből álló stack
    std::vector<bool> valueStack;

    //stringből kivett szám
    bool value;
    
    //visszatérési érték
    bool returnValue;

    //a kapu operátorának fajtája
    char op;

    //megvizsgáljuk, milyen operátor van a kapuban
    for (char a : brace) {
        if (a == '*' || a == '+'){
            op = a;
            break;
        }
    }

    //helyettesítendő karakterek a stringben
    std::vector<char> toReplace = {'+', '*', '(', ')'};
    
    //lecserélünk minden fenti vektorban lévő karaktert ' ' karakterre, ezzel lehetővé téve a számok kinyerését
    for (char a : toReplace) {
        std::replace(workString.begin(), workString.end(), a, ' ');
    }

    //kinyerjük a stringben tárolt számokat, ezeket a valueStack tömbe pusholjuk
    std::stringstream ss(workString);
    while (ss >> value) {
        valueStack.push_back(value);
    }

    //operátor alapján elvégezzük a műveletet, majd visszatérünk annak értékével
    switch (op) {
    case '*':
        //AND művelet
        returnValue = 1;
        for (bool a : valueStack) {
            returnValue *= a;
        }
        return (bool)returnValue;

    case '+':
        //OR művelet
        returnValue = 0;
        for (bool a : valueStack) {
            returnValue += a;
        }
        return (bool)returnValue;

    default:
        break;
    }

    //hiba esetén hibajelzés
    std::cout << "Hiba a muvelet elvegzesekor! A kapu az alabbi: " << brace << std::endl;
    return false;
}

/**
 * @brief Segédfüggvény. A logikai függvényünk kiértékelését végzi, adott bemeneti kombinációra, melyet egy bináris szám formájában kap meg. \n
 * \b Bemenet:
 * 1. input: logikai függvény \n
 * 2. ofName: kiíráshoz fájlnév \n
 */
bool evaluateOperation(const std::string &binaryValue, const std::vector<char> &variables, const std::string &operation) {
    //egy módosítható stringbe átmásolom a logikai függvényt
    std::string workString = operation;

    //először a a változók helyére behelyettesítem az értéküket, ehhez végighaladok a workStingen
    for(unsigned i = 0; i < workString.length(); i++) {
        
        //megvizsgálom, hogy az adott karakter szerepel-e a változó tömbben
        for (unsigned z = 0; z < variables.size(); z++) {
            if (workString[i] == variables[z]) {
                
                //ha szerepel, behelyettesítek 
                workString[i] = binaryValue[z];
                
                //ha negált a bemenet, kiveszem a '!' -t és visszahelyettesítem a negált értéket
                if (workString[i-1] == '!') {
                    if (workString[i] == '0') {
                        workString[i] = '1';
                    } else {
                        workString[i] = '0';
                    }
                    workString.erase(i - 1, 1);
                    i -= 1;
                }
            }
        }
    }

    //majd újra és újra végighaladva a stringen, egyre magasabb szinten lévő kapukat kalkulálok ki és helyettesítek vissza
    while (containOper(workString)) {
        
        //a stringen belüli indexeléshez
        unsigned i = 0;
        
        //egy adott kapu, mely már csak operátort és logikai értéket tartalmaz pl: (1*1)
        std::string subGate;
        
        //kezdő és záró id egy-egy adott szinten lévő kapuhoz
        int closeBracId = -1;
        int openBracId = -1;

        //megkeresi az első záró zárójel előtti utolsó nyitó zárójelet, ezek indexeit elmenti
        while (i < workString.length() && workString[i] != ')' ) {      
            if (workString[i] == '(' ) {
                openBracId = i;
            }
            closeBracId = ++i;
        }
        
        //a fent megtalált kaput kimásolja a subGate stringbe
        for (int a = 0; a + openBracId < closeBracId + 1; a++) {
            subGate += workString[a + openBracId];
        }

        //kiszámolja a subGate-ben található kapura a logikai értéket és visszahelyettesíti azt
        if (openBracId != -1 && closeBracId != -1) {
            workString.replace(openBracId, closeBracId - openBracId + 1, std::to_string(valueOfBrace(subGate)));
            
            //korrigálja az i-t
            i = i - (closeBracId - openBracId + 1);
        }

        i++;
    }
    //visszatér a teljes függvény logikai értékével, mivel karakterként tároljuk a végerdményt, '0'-t kivonva megkapjuk ezt
    return (bool)(workString[0]-'0');
}

/**
 * @brief Ez hozza létre az igazságtáblázatot, majd írja azt ki egy fájl. \n
 * \b Bemenet: 
 * 1. input: logikai függvény \n
 * 2. ofName: kiíráshoz fájlnév \n
 */
void createTable(const std::string &input, const std::string &ofName) {
    
    //egy módosítható stringbe átmásolom a logikai függvényt
    std::string workString = input;

    //a függvényben előforduló különböző változóknak
    std::vector<char> variables;

    //fájl íráshoz
    std::ofstream ofStream;

    //fájl neve: ofName -> ez a mainben inputból érkezik
    ofStream.open(ofName);

    //végighalad a logikai függvény string-jén és minden eddig még nem eltárolt változót a variables vektorba push-olja.
    for (char a : workString) {
        if (a >= 'A' && a <= 'Z' && !doesInclude(variables, a)) {
            variables.push_back(a);
        }
    }
    
    //bubble sort, az ABC-ben legelöl lévő változó az MSB pl:'A'.
    for (unsigned i = 0; i < variables.size() - 1; i++) {
        for (unsigned j = 0; j < variables.size()- i - 1; j++) {
            if (variables[j] > variables[j + 1]) {
                char temp = variables[j];
                variables[j] = variables[j + 1];
                variables[j + 1] = temp;
            }
        }
    }

    //hibakezelés
    if (ofStream) {
        //a fájlba kiíírom a változókat fejlécként: A   B   C   |   F
        for (char a : variables) {
            ofStream << a << "\t";
        }
        // a függvény fejléce
        ofStream << "|\tF" << std::endl;

        //végighaladok az összes bemeneti kombináción, ezekre megvizsgálom a függvény kimeneti értékét
        //összesen ennyin lehetőségem van: 2^(változók darabszáma)
        for (unsigned i = 0; i < pow(2, variables.size()); i++) {
            //integerek bináris számmá való alakítása -> így tudom elérni az összes bemeneti kombinációt pl: 2 változó esetén 0-tól 3-ig
            std::string binaryNum = toBinary(i, variables.size());

            //kiírja az adott bemeneti kombinációt, az adott bináris számtól függően
            //pl: 8 -> "1000" -> A=1 B=C=D=0
            for (unsigned m = 0; m < variables.size(); m++) {
                ofStream << binaryNum[m] << "\t";
            }
            
            ofStream << "|\t";
            
            //a logikai függvény értéke az adott bemeneti kombinációra
            ofStream << evaluateOperation(binaryNum, variables, workString) << std::endl;
        }
    } else {
        std::cout << "Hiba az igazsagtablazat fajljanak megnyitasakor!" << std::endl;
        return;
    }

    //fájl bezárása
    ofStream.close();
}

/**
 * @brief A bemeneti logikai függvényt vizsgálja meg. Ha nem egyezik meg a nyitó és záró zárójelek száma, hibát ad vissza.
 * \b Bemenet: 
 * 1. input: logikai függvény \n
 */
bool checkInput(const std::string &input){
    //nyitó zárójelek "("
    int openBrac = 0;

    //záró zárójelek ")"
    int closeBrac = 0;

    //megszámolja, hogy miből, mennyi van
    for(const char a : input){
        if (a == '(') {
            openBrac++;
        } else if (a == ')') {
            closeBrac++;
        }
    }

    //ha nem egyezik meg a nyitó és záró zárójelek száma, hamis értékkel tér vissza
    if (openBrac != closeBrac) {
        return false;
    }

    //egyébként igazzal tér vissza
    return true;
}

/**
 * @brief Felszabadítja a memóriát. A gateStack-en végighalad, töröl minden elemet.
 */
void freeStack() {
    //A gateStack minden elemét törli.
    for (Gate* a : gateStack) {
        delete[] a;
    }
}

int main() {
    //változók
    std::string function; 
    std::string graphFile; 
    std::string tableFile; 

    std::cout << "Kerem adja meg a halozat fuggvenyet: " << std::endl;
    
    //logikai függvény
    std::cin >> function; 

    //megvizsgáljuk a bemenetet
    if (!checkInput(function)) {
        std::cout << "Hibas bemenet, hiba a zarojelekkel!" << std::endl;
        return 1;
    }
    
    std::cout << "Kerem adja meg a graf celfajlanak nevet: " << std::endl;
    
    //gráf fájl bemenet
    std::cin >> graphFile; 

    //kiterjesztés hozzáadása
    graphFile += ".dot";

    std::cout << "Kerem adja meg az igazsagtabla celfajlanak nevet: " << std::endl;
    
    //igazság táblázat fájl bemenet
    std::cin >> tableFile; 

    //kiterjesztés hozzáadása
    tableFile += ".txt";

    //a kész hálózat teteje
    Gate* system = createSystem(function);

    //a gráf fájlba nyomtatása Graphviz segítségével
    if (system == nullptr) {
        std::cout << "A halozat letrehozasa sikertelen!" << std::endl;
        return 1;
    } else {
        printGraph(graphFile, system);
    }
    
    //létrehozza az igazságtáblázatot
    createTable(function, tableFile);

    //felszabadítjuk a gateStack vektort
    freeStack();

    return 0;
}