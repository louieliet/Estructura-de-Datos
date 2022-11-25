#pragma once
#include <iostream>
#include <stack>
#include <chrono>
#include <fstream>


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

    void clean(PTNODE pSub = NULL);
    void pushr(string pVal, PTNODE pSub = NULL);
    void push(string pVal);
    void reprr(Orden pOrd = Orden::asc, PTNODE pSub = NULL);
    void repr(Orden pOrd = Orden::asc);
    void delr(string pVal);
    void runGet(void(*pFunc)(string));

    void read(string pPath);
    void write(string pPath, Orden pOrd = Orden::sinorden);
private:
    PTNODE getNewNode(string pVal);
    PTNODE pdelr(PTNODE pSub, string pVal);
    PTNODE min(PTNODE pSub);
};
