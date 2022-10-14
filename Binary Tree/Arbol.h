#pragma once
#include <iostream>

using namespace std;

typedef struct TNODE* PTNODE;

struct TNODE{
    string sVal;
    PTNODE sLeft;
    PTNODE sRight;
};

enum class Orden {asc,desc,sinorden};

class Arbol{
protected:
    PTNODE aRoot;
public:
    Arbol(void);
    ~Arbol(void);

    void clean(void);
    void pushr(string pVal, PTNODE pSub = NULL);
    void repr(Orden pOrd = Orden::asc, PTNODE pSub = NULL);
private:
    PTNODE getNewNode(string pVal);
};
