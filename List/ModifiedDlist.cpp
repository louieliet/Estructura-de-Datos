// DLists.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

/*Cada nodo es una estructura*/
using namespace std;

typedef struct DNODE* PDNODE; // aapuntador del tipo DNODE
//typedef es una palabra reservada que nos permite definir un nuevo tipo
struct DNODE {
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
    bool aFreq;
public:
    DList(bool freq);
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

    void del(string pNombre);
    void delall(string pNombre);

    void read(string pPath, char pMethod = 'b');
    void write(string pPath, bool pRev = false);

private:
    PDNODE getNewNode(string pNombre);
    PDNODE search(string pNombre);
    PDNODE find(string pNombre);
};

DList::DList(bool freq) {

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFreq = freq;
    

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

        if(aFreq == true && aHead->sFrec > 1)
        {
            aHead->sFrec--;
        }
        else
        {
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
    }

} //borrar el primer lugar en la lista
void DList::pop_back(void) {

    if (aHead) {

        if(aFreq == true && aTail->sFrec > 1)
        {
            aTail->sFrec--;
        }
        else{
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
    }
} //borrar el último lugat en la lista

void DList::push_front(string pNombre) {
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead; //si la lista está vacía, el atail y el ahead están en el mismo lugar
    }
    else {
        if(aFreq == true && pNombre == aHead->sNombre){
            aHead->sFrec++;
        }
        else{

            PDNODE lTemp = getNewNode(pNombre);
            lTemp->sNext = aHead;
            aHead->sPrev = lTemp;
            aHead = lTemp;
        }
    }
}//hace un push antes de la primera  posición

void DList::push_back(string pNombre) {
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead; //si la lista está vacía, el atail y el ahead están en el mismo lugar
    }
    else {
        if(aFreq == true && pNombre == aTail->sNombre){
            aTail->sFrec++;
        }
        else{
            PDNODE lTemp = getNewNode(pNombre);
            aTail->sNext = lTemp;
            lTemp->sPrev = aTail;
            aTail = lTemp;
        }
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

PDNODE DList::search(string pNombre) { //busca el nombre en la lista

    PDNODE lTemp = aHead; 

    while (lTemp) {
        if (pNombre <= lTemp->sNombre) { //Verifica que un string sea más pequeño que el otro.
            return lTemp; //si es más pequeño o igual te da un string.
        }

        lTemp = lTemp->sNext; //accede al siguiente nodo
    }

    return NULL;

}

PDNODE DList::find(string pNombre) { //busca el nombre en la lista

    PDNODE lTemp = aHead; 

    while (lTemp) {
        if (pNombre == lTemp->sNombre) { //Verifica que un string sea igual que el otro.
            return lTemp; //si es igual te da un string.
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
                PDNODE lEqual = find(pNombre);

                if(aFreq == true && lEqual)
                {
                    lEqual->sFrec++;
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

        if(aFreq == true)
        {
            PDNODE lTemp = (pRev== false ? aHead : aTail); 
            while (lTemp) {
                cout << "->" << lTemp->sNombre;
                cout << " (with f: " << lTemp->sFrec << ")";
                lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
            }
            cout << "-> ||" << endl;
        }
        else
        {
            PDNODE lTemp = (pRev== false ? aHead : aTail); 
            while (lTemp) {
                cout << "->" << lTemp->sNombre;
                lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
            }
            cout << "-> ||" << endl;

        }
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


void DList::del(string pNombre){

    if(pNombre == aHead->sNombre){
        pop_front();
    }
    else if(pNombre == aTail->sNombre){
        pop_back();
    }
    else{

        PDNODE lTemp = find(pNombre);
        if(aFreq == true && lTemp->sFrec > 1){
            lTemp->sFrec--;
        }
        else{
            lTemp->sNext->sPrev = lTemp->sPrev;
            lTemp->sPrev->sNext = lTemp->sNext;
        }
        
        delete lTemp;
    }

}

void DList::delall(string pNombre){

    if(pNombre == aHead->sNombre){
        
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
    }
    else if(pNombre == aTail->sNombre){
        if(aHead)
        {
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
    }
    else{

        PDNODE lTemp = find(pNombre);

        lTemp->sNext->sPrev = lTemp->sPrev;
        lTemp->sPrev->sNext = lTemp->sNext;
        
        delete lTemp;
    }

}


void DList::read(string pPath, char pMethod)
{
    auto lStart = chrono::high_resolution_clock::now();
    string lLine = " ";
    ifstream lFile(pPath);

    while(getline(lFile, lLine))
    {
        switch(pMethod)
        {
            case 'b' : push_back(lLine); break;
            case 'f' : push_front(lLine); break;
            default:
                push(lLine); break;
        }
    }

    lFile.close();

    auto lElapsed = chrono::high_resolution_clock::now() - lStart;
    long long lMS = chrono::duration_cast<std::chrono::microseconds> (lElapsed).count();
    cout << lMS << "ms" << endl;
}

void DList::write(string pPath, bool pRev)
{
    if (aHead) {

        ofstream lFile(pPath);

        if(lFile.is_open()){

            PDNODE lTemp = (pRev== false ? aHead : aTail); 
            while (lTemp) {
                lFile << lTemp->sNombre << endl;
                lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
            }
            lFile.close();
        }
    }
}

int main()
{
    DList lLista = DList(false);

    lLista.read("C:/Users/juane/OneDrive/Documentos/GitHub/Estructura-de-Datos/List/prueba.txt", 's');
    lLista.repr();
    
    lLista.write("C:/Users/juane/OneDrive/Documentos/GitHub/Estructura-de-Datos/List/prueba_out.txt");

    /*lLista.push("007");
    lLista.push("007");
    lLista.push("Amanda");
    lLista.push("Amanda");
    lLista.repr();
    lLista.del("Amanda");
    lLista.delall("007");
    lLista.repr();*/



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
    lLista.repr(false); 


    PDNODE lTemp = NULL;
    while (lTemp = lLista.get(true)) {
        cout << "Nombre: " << lTemp -> sNombre << endl;
    }*/

}


