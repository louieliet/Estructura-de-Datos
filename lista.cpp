#include <iostream>
#include <string>

using namespace std;

typedef struct DNODE* PDNODE;

struct DNODE{

    string sNombre;
    int sFrec;
    PDNODE sNext;
    PDNODE sPrev;

};

class Dlist{

protected:
    PDNODE aHead;
    PDNODE aTail;

public:
    Dlist(void);
    ~Dlist(void);

    void clean(void); //Liberar de memoria todos los nodos
    void push_front(string pNombre);
    void push_back(string pNombre);
    void push(string pNombre);
    void repr(bool pRev = false);

    void pop_front(void);
    void pop_back(void);

    PDNODE top_front(void);
    PDNODE top_back(void);

    bool isEmpty(void);

private:
    PDNODE getNewNode(string pNombre);
    PDNODE search(string pNombre);
};


Dlist::Dlist(void){
    aHead = NULL;
    aTail = NULL;
}
Dlist::~Dlist(void){
    clean();
}
void Dlist::clean(void){

    while(aHead){
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
}
void Dlist::push_front(string pNombre){
    //Si no hay nodos
    if(aHead == NULL){
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else{
        PDNODE lTemp = getNewNode(pNombre);
        lTemp->sNext = aHead;
        aHead->sPrev = lTemp;
        aHead = lTemp;
    }
}
void Dlist::push_back(string pNombre){

    if(aHead == NULL){
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else{
        PDNODE lTemp = getNewNode(pNombre);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}
void Dlist::repr(bool pRev){
    if(aHead){
        PDNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp)
        {
            cout << "-> ";
            cout << lTemp->sNombre;
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << "->|| " << endl;
        
    }
}

PDNODE Dlist::search(string pNombre){

    PDNODE lTemp = aHead;
    while(!lTemp){
        if(pNombre <= lTemp->sNombre){
            return lTemp;
        }
        lTemp = lTemp->sNext;
    }

    return NULL;
}

PDNODE Dlist::getNewNode(string pNombre){
    PDNODE lTemp = new DNODE;
    if(lTemp){
        lTemp->sNombre = pNombre;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
}

void Dlist::push(string pNombre){
    if(aHead == NULL){
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else{
        if(pNombre <= aHead->sNombre){
            push_front(pNombre);
        }
        else
            if(pNombre >= aTail->sNombre){
                push_back(pNombre);
            }
            else{
                PDNODE lItem = search(pNombre);
                if(lItem){
                    PDNODE lTemp = getNewNode(pNombre);
                    lTemp->sNext = lItem;
                    lTemp->sPrev = lItem->sPrev;
                    lItem->sPrev->sNext = lTemp;
                    lItem->sPrev = lTemp;
                }
            }
    }
}


PDNODE Dlist::top_front(void)
{
    if(aHead)
    {
        return aHead;
    }
    return NULL;
}

PDNODE Dlist::top_back(void)
{
    if(aHead)
    {
        return aTail;
    }
    return NULL;
}

void Dlist::pop_front()
{
    if(aHead){
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
        if(aHead == NULL){
            aTail = NULL;
        }
        else{
            aHead->sPrev = NULL;
        }
    }
    
}

void Dlist::pop_back()
{
    if(aHead){
        PDNODE lTemp = aTail->sPrev;
        delete aTail;
        aTail = lTemp;
        if(aTail == NULL){
            aHead = NULL;
        }
        else{
            aTail->sNext = NULL;
        }
    }
    
}

bool Dlist::isEmpty(void)
{
    return (aHead == NULL);
}


int main()
{
    Dlist lLista = Dlist();

    lLista.push("C");
    lLista.push("B");
    lLista.push("D");
    lLista.push("007");

    lLista.repr(true);

    PDNODE lPtr = lLista.top_front();

    if(lPtr)
    {
        cout << "1ero: " << lPtr->sNombre << endl;
    }


    lLista.pop_front();
    lLista.repr();

    lLista.pop_back();
    lLista.repr();

    //Eliminar con pops
    while(!lLista.isEmpty()){
        lLista.pop_front();
    }
    
    lLista.repr();
}
