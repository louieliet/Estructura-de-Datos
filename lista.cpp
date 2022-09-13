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
    PDNODE aCurr;    ;

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
    PDNODE get(bool pRev = false);

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

PDNODE Dlist::get(bool pRev)
{
    PDNODE lTemp = NULL;

    if(aHead){

        if(aCurr == NULL)
            aCurr = (pRev == false ? aHead : aTail);
        else
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);

        lTemp = aCurr;

    }

    return lTemp;
}

void Dlist::pop_front()
{
    if(aHead){
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;
        if(aHead == NULL){
            aTail = NULL;
            aCurr = NULL;
        }
        else{
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
    }
    
}

void Dlist::pop_back()
{
    if(aHead){
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if(aTail == NULL){
            aHead = NULL;
            aCurr = NULL;
        }
        else{
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
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

    /*
    lLista.pop_front();
    lLista.repr();

    lLista.pop_back();
    lLista.repr();

    //Eliminar con pops
    while(!lLista.isEmpty()){
        lLista.pop_front();
    }

    lLista.repr();
    */

   lLista.repr();

   PDNODE lTemp = NULL;

    while(lTemp = lLista.get()){
        cout << "Nom: " << lTemp->sNombre << endl;
    }

    lLista.repr();



}
