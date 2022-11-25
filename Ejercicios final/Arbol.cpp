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
void Arbol::push(string pVal){
    if(aRoot == NULL){
        aRoot = getNewNode(pVal);
    }
    else{
        PTNODE lTemp = aRoot;
        while(lTemp){
            if(pVal < lTemp->sVal){
                if(lTemp->sLeft) lTemp = lTemp->sLeft;
                else {lTemp->sLeft = getNewNode(pVal);
                lTemp = NULL;}
            }
            else if(pVal > lTemp->sVal){
                if(lTemp->sRight) lTemp = lTemp->sRight;
                else{lTemp->sRight = getNewNode(pVal); lTemp = NULL;}
            }
            else{
                if(lTemp->sRight) lTemp = lTemp->sRight;
                else{lTemp->sRight = getNewNode(pVal); lTemp = NULL;}
            }
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

void Arbol::delr(string pVal){
    aRoot = pdelr(aRoot,pVal);
}

void Arbol::reprr(Orden pOrd, PTNODE pSub){
    if(aRoot){
        PTNODE lTemp = aRoot;
        if(pSub)
            lTemp = pSub;
        switch(pOrd){
            case Orden::asc: 
                if(lTemp->sLeft) reprr(pOrd, lTemp->sLeft);
                cout << lTemp->sVal << ", ";
                if(lTemp->sRight) reprr(pOrd, lTemp->sRight);
                break;
            case Orden::desc: 
                if(lTemp->sRight) reprr(pOrd, lTemp->sRight);
                cout << lTemp->sVal << ", ";
                if(lTemp->sLeft) reprr(pOrd, lTemp->sLeft);
                break;
            case Orden::sinorden: 
                cout << lTemp->sVal << ", ";
                if(lTemp->sLeft) reprr(pOrd, lTemp->sLeft);
                if(lTemp->sRight) reprr(pOrd, lTemp->sRight);
                break;
        }
    }
}

void Arbol::repr(Orden pOrd){
    if(aRoot){
        PTNODE lTemp = aRoot;
        stack<PTNODE> lStack;
        while(lTemp || lStack.empty() == false){

            switch(pOrd){
                case Orden::asc: 
                    if(lTemp){
                        lStack.push(lTemp);
                        lTemp = lTemp->sLeft;
                    }
                    else{
                        lTemp = lStack.top();
                        lStack.pop();
                        cout << lTemp->sVal << ", ";
                        lTemp = lTemp->sRight;
                    }
                    break;
                case Orden::desc: 
                    if(lTemp){
                        lStack.push(lTemp);
                        lTemp = lTemp->sRight;
                    }
                    else{
                        lTemp = lStack.top();
                        lStack.pop();
                        cout << lTemp->sVal << ", ";
                        lTemp = lTemp->sLeft;
                    }
                    break;
                case Orden::sinorden: 
                    if(lTemp){
                        cout << lTemp->sVal << ", ";
                        lStack.push(lTemp);
                        lTemp = lTemp->sLeft;
                    }
                    else{
                        lTemp = lStack.top();
                        lStack.pop();
                        lTemp = lTemp->sRight;
                    }
                    break;
            }
        }
    }
}

PTNODE Arbol::pdelr(PTNODE pSub, string pVal){
    if(pSub == NULL){
        return pSub;
    }
    if(pVal < pSub->sVal){
        pSub->sLeft = pdelr(pSub->sLeft,pVal);
    }
    else if(pVal > pSub->sVal){
        pSub->sRight = pdelr(pSub->sRight,pVal);
    }
    else{
        if(pSub->sLeft == NULL){
            PTNODE lTemp = pSub->sRight;
            delete pSub;
            return lTemp;
        }
        else if(pSub->sRight == NULL){
            PTNODE lTemp = pSub->sLeft;
            delete pSub;
            return lTemp;
        }
        PTNODE lTemp = min(pSub->sRight);
        pSub->sVal = lTemp->sVal; //Virtual delete
        pSub->sRight = pdelr(pSub->sRight, lTemp->sVal);   
    }
    return pSub;
}

void Arbol::runGet(void(*pFunc)(string)){

    if(aRoot && (pFunc != NULL)){
        PTNODE lTemp = aRoot;
        stack <PTNODE> lStack;

        while(lTemp || lStack.empty() == false){
            if(lTemp){
                lStack.push(lTemp);
                lTemp = lTemp->sLeft;
            }
            else{
                lTemp = lStack.top();
                lStack.pop();
                pFunc(lTemp->sVal);
                lTemp = lTemp->sRight;
            }
        }
    }
}
PTNODE Arbol::min(PTNODE pSub){
    PTNODE lTemp = pSub;
    while(lTemp && (lTemp->sLeft)){
        lTemp = lTemp->sLeft;
    }
    return lTemp;
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

void Arbol::read(string pPath){
    auto lStart = chrono::high_resolution_clock::now();
    string lLine = " ";
    ifstream lFile(pPath);

    while(getline(lFile, lLine))
    {
        push(lLine);
    }

    lFile.close();

    auto lElapsed = chrono::high_resolution_clock::now() - lStart;
    long long lMS = chrono::duration_cast<std::chrono::microseconds> (lElapsed).count();
    cout << lMS << "ms" << endl;
}

void Arbol::write(string pPath, Orden pOrd){
    if(aRoot){
        PTNODE lTemp = aRoot;
        stack<PTNODE> lStack;
        ofstream lFile(pPath);

        if(lFile.is_open()){
            while(lTemp || (lStack.empty() == false)){
                switch(pOrd){
                    case Orden::asc:
                        if(lTemp){
                            lStack.push(lTemp);
                            lTemp = lTemp->sLeft;
                        }
                        else{
                            lTemp = lStack.top();
                            lStack.pop();
                            lFile << lTemp->sVal << endl;
                        }
                }
            }
        }
    }
}


