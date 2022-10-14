#include "Arbol.h"

Arbol::Arbol(void){
    aRoot = NULL;
}

Arbol::~Arbol(void){
    clean();
}

void Arbol::pushr(string pVal, PTNODE pSub){
    if(aRoot == NULL){
        aRoot = getNewNode(pVal);
    }
    else{
        PTNODE lTemp = aRoot;
        if(pSub)
            lTemp = pSub;
        if(pVal < lTemp->sVal){
            if(lTemp->sLeft)
                pushr(pVal, lTemp->sLeft);
            else
                lTemp->sLeft = getNewNode(pVal);
        }
        else if(pVal >= lTemp->sVal){
            if(lTemp->sRight)
                pushr(pVal, lTemp->sRight);
            else
                lTemp->sRight = getNewNode(pVal);
        }
    }
}

void Arbol::clean(PTNODE pSub){
    if(aRoot){
        PTNODE lTemp = aRoot;
        if(pSub)
            lTemp = pSub;
        if(lTemp->sLeft) clean(lTemp->sLeft);
        if(lTemp->sRight) clean(lTemp->sRight);
        bool lRoot = lTemp == aRoot;
        delete lTemp;
        if(lRoot)
            aRoot = NULL;
    }
}

void Arbol::repr(Orden pOrd, PTNODE pSub){
    if(aRoot){
        PTNODE lTemp = aRoot;
        if(pSub)
            lTemp = pSub;
        switch(pOrd){
            case Orden::asc: 
                if(lTemp->sLeft) repr(pOrd, lTemp->sLeft);
                cout << lTemp->sVal << ", ";
                if(lTemp->sRight) repr(pOrd, lTemp->sRight);
                break;
            case Orden::desc: 
                if(lTemp->sRight) repr(pOrd, lTemp->sRight);
                cout << lTemp->sVal << ", ";
                if(lTemp->sLeft) repr(pOrd, lTemp->sLeft);
                break;
            case Orden::sinorden: 
                cout << lTemp->sVal << ", ";
                if(lTemp->sLeft) repr(pOrd, lTemp->sLeft);
                if(lTemp->sRight) repr(pOrd, lTemp->sRight);
                break;
        }
    }
}

PTNODE Arbol::getNewNode(string pVal){
    PTNODE lTemp = new TNODE;
    if(lTemp){
        lTemp->sVal = pVal;
        lTemp->sRight = NULL;
        lTemp->sLeft = NULL;
    }
    return lTemp;
}

