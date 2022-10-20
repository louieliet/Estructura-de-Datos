
#include "Cortina.h"

typedef struct DNODE* PDNODE;

struct DNODE {
    string sNombre;
    int sFrec;
    PDNODE sPrev;
    PDNODE sNext;
};

class DList
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;
    bool aFrec;

public:
    DList(bool pFrec = false);
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
    void del(string pNombre, bool pForce = false);

    bool isEmpty(void);
    void repr(bool pRev = false);
    void read(string pPath, char pMethod = 'b');
    void write(string pPath, bool pRev = false);

private:
	PDNODE find(string pNombre);
    PDNODE search(string pNombre);
    PDNODE getNewNode(string pNombre);
};

DList::DList(bool pFrec)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFrec = pFrec;
} // Constructor

DList::~DList(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DList::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DList::push_front(string pNombre)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else {
        bool lDo = true;
        if (aFrec) {
            if (pNombre == aHead->sNombre) {
                (aHead->sFrec)++;
                lDo = false;
            }
            else {
                PDNODE lItem = find(pNombre);
                if (lItem != NULL) {
                    (lItem->sFrec)++;
                    lDo = false;
                }
            }
        } 
        if (lDo) {
            PDNODE lTemp = getNewNode(pNombre);
            aHead->sPrev = lTemp;
            lTemp->sNext = aHead;
            aHead = lTemp;
        }
    }
} // push_front

void DList::push_back(string pNombre)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else {
        bool lDo = true;
        if (aFrec) {
            if (pNombre == aTail->sNombre) {
                (aTail->sFrec)++;
                lDo = false;
            }
            else {
                PDNODE lItem = find(pNombre);
                if (lItem != NULL) {
                    (lItem->sFrec)++;
                    lDo = false;
                }
            }
        }
        if (lDo) {
            PDNODE lTemp = getNewNode(pNombre);
            aTail->sNext = lTemp;
            lTemp->sPrev = aTail;
            aTail = lTemp;
        }
    }
} // push_back

void DList::push(string pNombre)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre);
        aTail = aHead;
    }
    else {
        if (pNombre <= aHead->sNombre)
            push_front(pNombre);
        else if (pNombre >= aTail->sNombre)
            push_back(pNombre);
        else {
            PDNODE lItem = search(pNombre);
            if (lItem) {
                if (aFrec && (lItem->sNombre == pNombre)) {
                    (lItem->sFrec)++;
                }
                else {
                    PDNODE lTemp = getNewNode(pNombre);
                    lTemp->sNext = lItem;
                    lTemp->sPrev = lItem->sPrev;
                    lItem->sPrev->sNext = lTemp;
                    lItem->sPrev = lTemp;
                }
            }
        }
    }
} // push

PDNODE DList::top_front(void)
{
    if (aHead) {
        return aHead;
    }
    return NULL;
} // top_front

PDNODE DList::top_back(void)
{
    if (aHead) {
        return aTail;
    }
    return NULL;
} // top_back

PDNODE DList::get(bool pRev)
{
   PDNODE lTemp = NULL;

   if (aHead) {
       if (aCurr == NULL)
           aCurr = (pRev == false ? aHead : aTail);
       else
           aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
       lTemp = aCurr;
   }

   return lTemp;
} // get

void DList::pop_front(void)
{
    bool lDo = true;

    if (aHead) {
        if (aFrec) {
            (aHead->sFrec)--;
            if (aHead->sFrec > 0)
                lDo = false;
        }
    }
    else
        lDo = false;
    if (lDo) {
        PDNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        delete aHead;
        aHead = lTemp;
        if (aHead) {
            aHead->sPrev = NULL;
            aCurr = (lEqual ? aHead : aCurr);
        }
        else {
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DList::pop_back(void)
{
    bool lDo = true;

    if (aHead) {
        if (aFrec) {
            (aTail->sFrec)--;
            if (aTail->sFrec > 0)
                lDo = false;
        }
    }
    else
        lDo = false;
    if (lDo) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) {
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

void DList::del(string pNombre, bool pForce)
{
    if (aHead) {
        if (aHead->sNombre == pNombre)
            pop_front();
        else if (aTail->sNombre == pNombre)
            pop_back();
        else {
            PDNODE lTemp = find(pNombre);
            if (lTemp) {
                if (!aFrec)
                    lTemp->sFrec = 0;
                else
                    if (!pForce)
                        (lTemp->sFrec)--;
                    else
                        lTemp->sFrec = 0;
                if (lTemp->sFrec == 0) {
                    if (aCurr == lTemp)
                        aCurr = lTemp->sNext;
                    lTemp->sPrev->sNext = lTemp->sNext;
                    lTemp->sNext->sPrev = lTemp->sPrev;
                    delete lTemp;
                }
            }
        }
    }
} // del

bool DList::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DList::repr(bool pRev)
{
    if (aHead) {
        PDNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " -> ";
            cout << lTemp->sNombre;
            if (aFrec)
                cout << " #" << lTemp->sFrec;
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " ->|| " << endl;
    }
} // repr

void DList::read(string pPath, char pMethod)
{
    auto lStart = chrono::high_resolution_clock::now();
    string lLine = "";
    ifstream lFile(pPath);

    while (getline(lFile, lLine)) {
        switch (pMethod) {
            case 'b': 
            	push_back(lLine);
            	break;
            case 'f':
            	push_front(lLine);
            	break;
            default:
                push(lLine);
                break;
        }
    }

    lFile.close();

    auto lElapsed = chrono::high_resolution_clock::now() - lStart;
    long long lMS = chrono::duration_cast<chrono::microseconds>
        (lElapsed).count();
    cout << lMS << " ms" << endl;
} // read

void DList::write(string pPath, bool pRev)
{
    if (aHead) {
        ofstream lFile(pPath);
        if (lFile.is_open()) {
            PDNODE lTemp = (pRev == false ? aHead : aTail);
            while (lTemp) {
                lFile << lTemp->sNombre << endl;
                lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
            }
            lFile.close();
        }
    }
} // write

PDNODE DList::find(string pNombre)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pNombre == lTemp->sNombre)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PDNODE DList::search(string pNombre)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pNombre <= lTemp->sNombre)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DList::getNewNode(string pNombre)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sNombre = pNombre;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode


