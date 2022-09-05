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
    void repr(void);
    void push(string pNombre);

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
void Dlist::repr(void){
    if(aHead){
        PDNODE lTemp = aHead;
        while (lTemp)
        {
            cout << "-> ";
            cout << lTemp->sNombre;
            lTemp = lTemp->sNext;
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
                PDNODE lTemp = search(pNombre);
                //Aqui 
            }
    }
}

int main()
{
    Dlist lLista = Dlist();

    lLista.push_front("Peter Parker");
    lLista.push_back("Clark Kent");
    lLista.push_front("Diana Prince");

    lLista.repr();

}
