
#include "DLists.cpp"

typedef vector <string> strVec;

void strSplit(string& pStr, char pDelim, strVec& pOut)
{
    stringstream lStream(pStr);
    string lChunk;
    while (getline(lStream, lChunk, pDelim)) {
        pOut.push_back(lChunk);
        // cout << lChunk.c_str() << endl;
    }
} // strSplit

DLVer::DLVer(void)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // Constructor

DLVer::~DLVer(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DLVer::clean(void)
{
    while (aHead) {
        PVNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DLVer::push(string pMain, string pExtra)
{
    if (aHead == NULL) {
        aHead = getNewNode(pMain, pExtra);
        aTail = aHead;
    }
    else {
        if (pMain <= aHead->sMain)
            push_front(pMain, pExtra);
        else if (pMain >= aTail->sMain)
            push_back(pMain, pExtra);
        else {
            PVNODE lItem = search(pMain);
            if (lItem) {
                PVNODE lTemp = getNewNode(pMain, pExtra);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }
        }
    }
} // push

PVNODE DLVer::get(bool pRev)
{
    PVNODE lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL)
            aCurr = (pRev == false ? aHead : aTail);
        else
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        lTemp = aCurr;
    }

    return lTemp;
} // get

PVNODE DLVer::get(string pMain)
{
    PVNODE lTemp = NULL;

    if (aHead) {
        lTemp = find(pMain);
    }

    return lTemp;
} // get

void DLVer::resetCurr(void)
{
    aCurr = NULL;
} // resetCurr

void DLVer::del(string pMain)
{
    if (aHead) {
        if (aHead->sMain == pMain)
            pop_front();
        else if (aTail->sMain == pMain)
            pop_back();
        else {
            PVNODE lTemp = find(pMain);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }
} // del

bool DLVer::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DLVer::repr(bool pRev)
{
    if (aHead) {
        PVNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " > ";
            cout << lTemp->sMain << ", " << lTemp->sExtra;
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " >| ";
    }
} // repr

void DLVer::push_front(string pMain, string pExtra)
{
    if (aHead == NULL) {
        aHead = getNewNode(pMain, pExtra);
        aTail = aHead;
    }
    else {
        PVNODE lTemp = getNewNode(pMain, pExtra);
        aHead->sPrev = lTemp;
        lTemp->sNext = aHead;
        aHead = lTemp;
    }
} // push_front

void DLVer::push_back(string pMain, string pExtra)
{
    if (aHead == NULL) {
        aHead = getNewNode(pMain, pExtra);
        aTail = aHead;
    }
    else {
        PVNODE lTemp = getNewNode(pMain, pExtra);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
} // push_back

void DLVer::pop_front(void)
{
    if (aHead) {
        PVNODE lTemp = aHead->sNext;
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

void DLVer::pop_back(void)
{
    if (aHead) {
        PVNODE lTemp = aTail->sPrev;
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

PVNODE DLVer::find(string pMain)
{
    PVNODE lTemp = aHead;

    while (lTemp) {
        if (pMain == lTemp->sMain)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PVNODE DLVer::search(string pMain)
{
    PVNODE lTemp = aHead;

    while (lTemp) {
        if (pMain <= lTemp->sMain)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PVNODE DLVer::getNewNode(string pMain, string pExtra)
{
    PVNODE lTemp = new VNODE;

    if (lTemp) {
        lTemp->sMain = pMain;
        lTemp->sExtra = pExtra;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode

//---------------

DLHor::DLHor(void)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // Constructor

DLHor::~DLHor(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DLHor::clean(void)
{
    while (aHead) {
        PHNODE lTemp = aHead->sNext;
        if (aHead->sVer)
            delete aHead->sVer;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DLHor::push(string pCat, string pMain, string pExtra)
{
    if (aHead == NULL) {
        aHead = getNewNode(pCat);
        aTail = aHead;
        aHead->sVer = new DLVer();
        if (aHead->sVer)
            aHead->sVer->push(pMain, pExtra);
    }
    else {
        if (pCat <= aHead->sCat)
            push_front(pCat, pMain, pExtra);
        else if (pCat >= aTail->sCat)
            push_back(pCat, pMain, pExtra);
        else {
            PHNODE lItem = search(pCat);
            if (lItem) {
                if (lItem->sCat != pCat) {
                    PHNODE lTemp = getNewNode(pCat);
                    lTemp->sNext = lItem;
                    lTemp->sPrev = lItem->sPrev;
                    lItem->sPrev->sNext = lTemp;
                    lItem->sPrev = lTemp;
                    lTemp->sVer = new DLVer();
                    if (lTemp->sVer)
                        lTemp->sVer->push(pMain, pExtra);
                }
                else {
                    if (lItem->sVer == NULL)
                        lItem->sVer = new DLVer();
                    if (lItem->sVer)
                        lItem->sVer->push(pMain, pExtra);
                }
            }
        }
    }
} // push

void DLHor::get(PHNODE *pHor, PVNODE *pVer, bool pRev)
{
   *pHor = NULL;
   *pVer = NULL;

   if (aHead) {
       if (aCurr == NULL) {
           aCurr = (pRev == false ? aHead : aTail);
           if (aCurr->sVer) {
               *pVer = aCurr->sVer->get(pRev);
           }
       }
       else {
           if (aCurr->sVer) {
               *pVer = aCurr->sVer->get(pRev);
           }
           if (*pVer == NULL) {
               aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
               if (aCurr)
                   if (aCurr->sVer) {
                       *pVer = aCurr->sVer->get(pRev);
                   }
           }
       }
       *pHor = aCurr;
   }
} // get

void DLHor::get(PHNODE* pHor, PVNODE* pVer, string pCat, string pMain)
{
    *pHor = NULL;
    *pVer = NULL;

    if (aHead) {
        *pHor = find(pCat);
        if (*pHor) {
            if ((*pHor)->sVer) {
                *pVer = (*pHor)->sVer->get(pMain);
            }
        }
    }
} // get

void DLHor::del(string pCat)
{
    if (aHead) {
        if (aHead->sCat == pCat)
            pop_front();
        else if (aTail->sCat == pCat)
            pop_back();
        else {
            PHNODE lTemp = find(pCat);
            if (lTemp) {
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                if (lTemp->sVer)
                    delete lTemp->sVer;
                delete lTemp;
            }
        }
    }
} // del

void DLHor::del(string pCat, string pMain)
{
    if (aHead) {
        if (aHead->sCat == pCat) {
            if (aHead->sVer)
                aHead->sVer->del(pMain);
        }
        else if (aTail->sCat == pCat) {
            if (aTail->sVer)
                aTail->sVer->del(pMain);
        }
        else {
            PHNODE lTemp = find(pCat);
            if (lTemp) {
                if (lTemp->sVer)
                    lTemp->sVer->del(pMain);
            }
        }
    }
} // del

bool DLHor::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DLHor::repr(bool pRev)
{
    if (aHead) {
        PHNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " -> ";
            cout << lTemp->sCat << "( ";
            if (lTemp->sVer)
                lTemp->sVer->repr(pRev);
            cout << ")";
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " ->|| " << endl;
    }
} // repr

void DLHor::read(string pPath)
{
    string lLine = "";
    ifstream lFile(pPath);
    string lCat = "";
    strVec lOut;

    while (getline(lFile, lLine)) {
        if (lLine[0] != '\t')
            lCat = lLine;
        else {
            if (lCat != "") {
                lLine.replace(lLine.find("\t"), 1, "");
                strSplit(lLine, '|', lOut);
                push(lCat, lOut[0], lOut[1]);
                lOut.clear();
            }
        }
    }

    lFile.close();
} // read

void DLHor::write(string pPath, bool pRev)
{
    if (aHead) {
        ofstream lFile(pPath);
        if (lFile.is_open()) {
            PHNODE lTemp = (pRev == false ? aHead : aTail);
            while (lTemp) {
                lFile << lTemp->sCat << endl;
                if (lTemp->sVer) {
                    lTemp->sVer->resetCurr();
                    PVNODE lItem = NULL;
                    while (lItem = lTemp->sVer->get()) {
                        lFile << "\t" << lItem->sMain << "|" << lItem->sExtra << endl;
                    }
                }
                lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
            }
            lFile.close();
        }
    }
} // write

void DLHor::push_front(string pCat, string pMain, string pExtra)
{
    if (aHead == NULL) {
        aHead = getNewNode(pCat);
        aTail = aHead;
        aHead->sVer = new DLVer();
        if (aHead->sVer)
            aHead->sVer->push(pMain, pExtra);
    }
    else
        if (aHead->sCat != pCat) {
            PHNODE lTemp = getNewNode(pCat);
            aHead->sPrev = lTemp;
            lTemp->sNext = aHead;
            aHead = lTemp;
            lTemp->sVer = new DLVer();
            if (lTemp->sVer)
                lTemp->sVer->push(pMain, pExtra);
        }
        else {
            if (aHead->sVer == NULL)
                aHead->sVer = new DLVer();
            if (aHead->sVer)
                aHead->sVer->push(pMain, pExtra);
        }
} // push_front

void DLHor::push_back(string pCat, string pMain, string pExtra)
{
    if (aHead == NULL) {
        aHead = getNewNode(pCat);
        aTail = aHead;
        aTail->sVer = new DLVer();
        if (aTail->sVer)
            aTail->sVer->push(pMain, pExtra);
    }
    else
        if (aTail->sCat != pCat) {
            PHNODE lTemp = getNewNode(pCat);
            aTail->sNext = lTemp;
            lTemp->sPrev = aTail;
            aTail = lTemp;
            lTemp->sVer = new DLVer();
            if (lTemp->sVer)
                lTemp->sVer->push(pMain, pExtra);
        }
        else {
            if (aTail->sVer == NULL)
                aTail->sVer = new DLVer();
            if (aTail->sVer)
                aTail->sVer->push(pMain, pExtra);
        }
} // push_back

void DLHor::pop_front(void)
{
    if (aHead) {
        PHNODE lTemp = aHead->sNext;
        bool lEqual = (aHead == aCurr);
        if (aHead->sVer)
            delete aHead->sVer;
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

void DLHor::pop_back(void)
{
    if (aHead) {
        PHNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        if (aTail->sVer)
            delete aTail->sVer;
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

PHNODE DLHor::find(string pCat)
{
    PHNODE lTemp = aHead;

    while (lTemp) {
        if (pCat == lTemp->sCat)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find

PHNODE DLHor::search(string pCat)
{
    PHNODE lTemp = aHead;

    while (lTemp) {
        if (pCat <= lTemp->sCat)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PHNODE DLHor::getNewNode(string pCat)
{
    PHNODE lTemp = new HNODE;

    if (lTemp) {
        lTemp->sCat = pCat;
        lTemp->sVer = NULL;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode

