#include "DLists.h"

DList::DList(bool freq) {
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFreq = freq;
} 

DList:: ~DList(void) { clean(); } 

void DList::clean(void) {

    while (aHead){ 
        PDNODE lTemp = aHead->sNext;
        if(aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
    }

}

void DList::push_back(string pNombre, string pApellido, string pFNac, double pSalario) {
    
    if (aHead == NULL) {
        aHead = getNewNode(pNombre, pApellido, pFNac, pSalario);
        aTail = aHead;
    }
    else {

        PDNODE lTemp = getNewNode(pNombre, pApellido, pFNac, pSalario);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}

PDATA DList::get(ECampos pCampo, bool pRev) {

    PDATA lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL) 
            aCurr = (pRev == false ? aHead: aTail);
        else 
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        if(aCurr->sData)
            lTemp = aCurr->sData;
    }

    return lTemp;
}

bool DList::isEmpty(void) { return (aHead == NULL); }

void DList::repr(ECampos pCampo, bool pRev) { 

    if (aHead) {

        PDNODE lTemp = (pRev== false ? aHead : aTail); 
        while (lTemp) {
            cout << "->";
            cout << "[ " << lTemp->sData->sNombre << ", ";
            cout << lTemp->sData->sApellido << ", ";
            cout << lTemp->sData->sFNac << ", ";
            cout << lTemp->sData->sSalario << "] ";
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << "-> ||" << endl;
    }
}

PDNODE DList::getNewNode(string pNombre, string pApellido, string pFNac, double pSalario) {

    PDNODE lTemp = new DNODE;
    
    if(lTemp)
    {
        lTemp->sData = new DATA;
        if(lTemp->sData){
            lTemp->sData->sNombre = pNombre;
            lTemp->sData->sApellido = pApellido;
            lTemp->sData->sFNac = pFNac;
            lTemp->sData->sSalario = pSalario;
        }
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }
} 
