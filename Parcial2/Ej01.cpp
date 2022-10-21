
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct DNODE* PDNODE; 
typedef struct DNODE {
    string sNombre;
    int sFrec;  
    PDNODE sNext; 
    PDNODE sPrev; 
};

class DList {
protected:
    PDNODE aHead; 
    PDNODE aTail; 
    PDNODE aCurr;
public:
    DList(void);
    ~DList(void);

    void clean(void);
    void push_front(string pNombre);
    void push_back(string pNombre);
    void push(string pNombre);

    void pushVector(vector<string> list);

    PDNODE top_front(void);
    PDNODE top_back(void);
    PDNODE get(bool pRev = false);

    void pop_front(void);
    void pop_back(void);


    bool isEmpty(void);
    void repr(bool pRev = false);

    long int* invertArray(long int* arr1, long int* arr2);

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
} 

PDNODE DList::top_front(void) {

    if (aHead) {
        return aHead;
    }
    return NULL;

}
PDNODE DList::top_back(void) {
    if (aHead) {
        return aTail;
    }
    return NULL;

} 

void DList::clean(void) {

    while (aHead) 
    {
        PDNODE lTemp = aHead->sNext;
        delete aHead;

        aHead = lTemp; 

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

} 
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

} 

void DList::push_front(string pNombre) {
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead; 
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
        aTail = aHead; 
    }
    else {
        PDNODE lTemp = getNewNode(pNombre);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;

    }

}

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

PDNODE DList:: search(string pNombre) { 

    PDNODE lTemp = aHead; 

    while (lTemp) {
        if (pNombre <= lTemp->sNombre) { 
            return lTemp; 
        }

        lTemp = lTemp->sNext; 
    }

    return NULL;

}

void DList::push(string pNombre) {

    if (aHead == NULL) {
        aHead = getNewNode(pNombre); 
        aTail = aHead; 

    }
    else {
        if (pNombre <= aHead->sNombre) { 
            push_front(pNombre);
        }
        else {

            if (pNombre >= aTail->sNombre) {
                push_back(pNombre);

            }
            else
            {
                PDNODE lItem = search(pNombre);
                if (lItem) {

                    PDNODE lTemp = getNewNode(pNombre); 
                    lTemp->sNext = lItem;
                    lTemp->sPrev = lItem->sPrev;
                    lItem->sPrev->sNext = lTemp;
                    lItem->sPrev = lTemp;   
                }
            }
        }
    }
}

bool DList::isEmpty(void) {
    return (aHead == NULL);
}

void DList::repr(bool pRev) { 

    if (aHead) {
        PDNODE lTemp = (pRev== false ? aHead : aTail); 
        while (lTemp) {
            cout << "->" << lTemp->sNombre;
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << "-> ||" << endl;
    }

} 

PDNODE DList::getNewNode(string pNombre) {
    PDNODE lTemp = new DNODE;
    if (lTemp) {
        lTemp->sNombre = pNombre;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;

    }

    return lTemp;
}

#define SIZE 10

long int* DList::invertArray(long int* arr1, long int* arr2){

    PDNODE lTemp;
    int x = 0;
    cout << "Original Array: " << endl;
    
    for(int i = 0; i < SIZE; i++){
        cout << arr1[i] << ", ";
    }

    for(int i = 0; i < SIZE; i++){
        push_back(to_string(arr1[i]));
    }
    
    cout << endl << "list" << endl;
    repr();

    while(lTemp = get(true)){
        arr2[x] = stoi(lTemp->sNombre);
        x++;
    }
    
    return arr2;
}


int main(){

    DList lLista = DList();

    vector<long int> list;
    long int array[SIZE] = {10,20,30,40,50,60,70,80,90,95};
    long int array2[SIZE] = {0,0,0,0,0,0,0,0,0,0};

    long int* invertedArray = lLista.invertArray(array,array2);

    cout << "Inverted Array: " << endl;

    for(int i = 0; i < SIZE; i++){
        cout << invertedArray[i] << ", ";
    }
    
}