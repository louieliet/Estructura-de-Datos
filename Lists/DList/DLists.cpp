// DLists.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>

/*Cada nodo es una estructura*/
using namespace std;

typedef struct DNODE* PDNODE; // aapuntador del tipo DNODE
//typedef es una palabra reservada que nos permite definir un nuevo tipo
typedef struct DNODE {
    string sNombre;
    int sFrec; //para frecuencia 
    PDNODE sNext; //apunta a ruta de memoria siguiente
    PDNODE sPrev; //apunta a ruta de memoria anterior
};

class DList {
protected:
    PDNODE aHead; //donde empieza la lista
    PDNODE aTail; //posición donde termina la lista (temporal porque puedes agregar más datos)
    PDNODE aCurr;
public:
    DList(void);
    ~DList(void);

    void clean(void);
    void push_front(string pNombre);
    void push_back(string pNombre);
    void push(string pNombre);

    PDNODE top_front(void);
    PDNODE top_back(void);
    PDNODE get(bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    // void repr(void);

    bool isEmpty(void);
    void repr(bool pRev = false);

private:
    PDNODE getNewNode(string pNombre);
    PDNODE search(string pNombre);
};

DList::DList(void) {

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;

} //constructor

DList:: ~DList(void) {

    clean();
} //destructor

PDNODE DList::top_front(void) {

    if (aHead) {
        return aHead;
    }
    return NULL;

} //regresa el primer valor en la lista
PDNODE DList::top_back(void) {
    if (aHead) {
        return aTail;
    }
    return NULL;

} //regresa el ultimo valor de la lista

void DList::clean(void) {

    while (aHead) //tengo  la ruta de memoria de aHead, si no hay ruta, es null y no entra a la memoria
    {
        PDNODE lTemp = aHead->sNext;
        delete aHead;

        aHead = lTemp; //guarda la direccion de memoria de la siguiente ruta

    }

    aHead = NULL;
    aTail = NULL;

}//limpia

void DList::pop_front(void) {
    if (aHead) {
        PDNODE lTemp = aHead->sNext;

        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;

        if (aHead == NULL) {
            aTail = NULL;
            aCurr = NULL;
        }
        else {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead: aCurr);
        }
    }

} //borrar el primer lugar en la lista
void DList::pop_back(void) {

    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail == NULL) {
            aHead = NULL;
            aCurr = NULL;
        }
        else {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
    }

} //borrar el último lugat en la lista

void DList::push_front(string pNombre) {
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead; //si la lista está vacía, el atail y el ahead están en el mismo lugar
    }
    else {
        PDNODE lTemp = getNewNode(pNombre);
        lTemp->sNext = aHead;
        aHead->sPrev = lTemp;
        aHead = lTemp;

    }

}//hace un push antes de la primera  posición

void DList::push_back(string pNombre) {
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead; //si la lista está vacía, el atail y el ahead están en el mismo lugar
    }
    else {
        PDNODE lTemp = getNewNode(pNombre);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;

    }

} //hace un push después de la última posición

PDNODE DList::get(bool pRev) {

    PDNODE lTemp = NULL;
    if (aHead) {
        if (aCurr == NULL) {
            aCurr = (pRev == false ? aHead: aTail);
        }
        else {
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        }
        lTemp = aCurr;
    }
    return lTemp;

} //da d

PDNODE DList:: search(string pNombre) { //busca el nombre en la lista

    PDNODE lTemp = aHead; 

    while (lTemp) {
        if (pNombre <= lTemp->sNombre) { //Verifica que un string sea más pequeño que el otro.
            return lTemp; //si es más pequeño o igual te da un string.
        }

        lTemp = lTemp->sNext; //accede al siguiente nodo
    }

    return NULL;

}

void DList::push(string pNombre) {

    if (aHead == NULL) {
        aHead = getNewNode(pNombre); //crea nuevo nodo
        aTail = aHead; //si la lista está vacía, el atail y el ahead están en el mismo lugar

    }
    else {
        if (pNombre <= aHead->sNombre) { //ingresa un nombre menor al nombre en el head, entonces lo meterá antes
            push_front(pNombre);
        }
        else {

            if (pNombre >= aTail->sNombre) { //ingresa un nombre mayor al nombre en la cola, entonces lo meterá después
                push_back(pNombre);

            }
            else
            {
                PDNODE lItem = search(pNombre); //encuentra el lugar disponible o busca un lugar donde guardarlo.
                if (lItem) {

                    PDNODE lTemp = getNewNode(pNombre); //EL NUEVO DIGITO QUE SE QUIERE AGREGAR
                    lTemp->sNext = lItem;
                    lTemp->sPrev = lItem->sPrev;
                    lItem->sPrev->sNext = lTemp;
                    lItem->sPrev = lTemp;

                    
                }


            }

        }
    }
}//push ordenado

/*void DList::repr(void) {

    if (aHead) {
        PDNODE lTemp = aHead;
        while (lTemp) {
            cout << "->"<<lTemp->sNombre;
            lTemp = lTemp->sNext;
        }
        cout << "-> ||" << endl;
    }

} //repr*/

bool DList::isEmpty(void) {
    return (aHead == NULL);
}

void DList::repr(bool pRev) { //si pRev es falso, recorre en orden, si es cierto, recorre la lista inversamente (de aTail a aHead)

    if (aHead) {
        PDNODE lTemp = (pRev== false ? aHead : aTail); 
        while (lTemp) {
            cout << "->" << lTemp->sNombre;
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << "-> ||" << endl;
    }

} //repr inverso (recorre de la Tail)

PDNODE DList::getNewNode(string pNombre) {
    PDNODE lTemp = new DNODE;
    if (lTemp) {
        lTemp->sNombre = pNombre;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;

    }

    return lTemp;
} // Obtener un nuevo nodo


int main()
{
    DList lLista = DList();

    lLista.push("Peter Parker");
    lLista.push("Peter Adams");
    lLista.push("Peter Zi");
    lLista.push("Clark Kent");
    lLista.push("Diana Prince");
    lLista.push("alice");
    lLista.push("007");

    lLista.repr(false);
    /*PDNODE lPtr = lLista.top_front();
    if (lPtr) {
        cout << "1ero: " << lPtr->sNombre << endl;
    }

    lLista.pop_front();
    lLista.repr();
    lLista.pop_back();
    lLista.repr();

    while (!lLista.isEmpty()) {
        lLista.pop_front();
    }

    cout << "------------" << endl;
    lLista.repr(false); */


    PDNODE lTemp = NULL;
    while (lTemp = lLista.get(true)) {
        cout << "Nombre: " << lTemp -> sNombre << endl;
    }

    lLista.repr();
}


