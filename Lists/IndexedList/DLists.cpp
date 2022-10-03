#include "DLists.h"

DLIndex::DLIndex(ECampos pType, bool freq) {
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFreq = freq;
    aType = pType;
} 

DLIndex:: ~DLIndex(void) { clean(); } 

void DLIndex::clean(void) {

    while (aHead){ 
        PDNODE lTemp = aHead->sNext;
        delete aHead;
        aHead = lTemp;
    }
}

void DLIndex::push_back(PDATA pData) {
    
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {

        PDNODE lTemp = getNewNode(pData);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
    }
}

void DLIndex::push_front(PDATA pData) {
    
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {

        PDNODE lTemp = getNewNode(pData);
        lTemp->sNext = aHead;
        aHead->sPrev = lTemp;
        aHead = lTemp;
    }
}

void DLIndex::push(PDATA pData) {

    if (aHead == NULL) {
        aHead = getNewNode(pData); 
        aTail = aHead; 
    }
    else {
        if (comp(pData, aHead->sData) <= 0) { 
            push_front(pData);
        }
        else if (comp(pData, aHead->sData) >= 0) { 
            push_back(pData);
        }
        else{
            PDNODE lItem = search(pData);
            if(lItem)
            {
                PDNODE lTemp = getNewNode(pData);
                lTemp->sNext = lItem;
                lTemp->sPrev = lItem->sPrev;
                lItem->sPrev->sNext = lTemp;
                lItem->sPrev = lTemp;
            }   
        }
    }
}

PDATA DLIndex::get(bool pRev) {

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

bool DLIndex::isEmpty(void) { return (aHead == NULL); }

void DLIndex::repr(bool pRev) { 

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

PDNODE DLIndex::search(PDATA pData) { 

    PDNODE lTemp = aHead; 

    while (lTemp) {
        if (comp(pData, lTemp->sData) == 0) { 
            return lTemp; 
        }

        lTemp = lTemp->sNext; 

        return NULL;
    }

}

PDNODE DLIndex::getNewNode(PDATA pData) {

    PDNODE lTemp = new DNODE;
    
    if(lTemp)
    {
        lTemp->sData = pData;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }
} 

int DLIndex::comp(PDATA pA, PDATA pB){
    
    int lRes = 0;

    switch(aType){
        case ECampos::nombre:
            if(pA->sNombre < pB->sNombre) lRes = -1;
            else if(pA->sNombre == pB->sNombre) lRes = 0;
            else lRes = 1;
            break;

        case ECampos::apellido:
            if(pA->sApellido < pB->sApellido) lRes = -1;
            else if(pA->sApellido == pB->sApellido) lRes = 0;
            else lRes = 1;
            break;

        case ECampos::fnac:
            if(pA->sFNac < pB->sFNac) lRes = -1;
            else if(pA->sFNac == pB->sFNac) lRes = 0;
            else lRes = 1;
            break;

        case ECampos::salario:
            if(pA->sSalario< pB->sSalario) lRes = -1;
            else if(pA->sSalario== pB->sSalario) lRes = 0;
            else lRes = 1;
            break;
    }
}

DList::DList(bool freq) {

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFreq = freq;

    aINom = new DLIndex(ECampos::nombre);
    aIApe= new DLIndex(ECampos::apellido);
    aIFNa = new DLIndex(ECampos::fnac);
    aISal = new DLIndex(ECampos::salario);

} 

DList:: ~DList(void) { 
    
    clean(); 
    if(aINom) delete aINom;
    if(aIApe) delete aIApe;
    if(aIFNa) delete aIFNa;
    if(aISal) delete aISal;

} 

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

        aINom->push(aHead->sData);
        aIApe->push(aHead->sData);
        aIFNa->push(aHead->sData);
        aISal->push(aHead->sData);

    }
    else {

        PDNODE lTemp = getNewNode(pNombre, pApellido, pFNac, pSalario);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;

        aINom->push(lTemp->sData);
        aIApe->push(lTemp->sData);
        aIFNa->push(lTemp->sData);
        aISal->push(lTemp->sData);
    }
}

PDATA DList::get(ECampos pCampo, bool pRev) {

    PDATA lTemp = NULL;

    switch(pCampo){
        case ECampos::nombre : lTemp = aINom->get(pRev); break;
        case ECampos::apellido : lTemp = aIApe->get(pRev); break;
        case ECampos::fnac : lTemp = aIFNa->get(pRev); break;
        case ECampos::salario : lTemp = aISal->get(pRev); break;
    }
}

bool DList::isEmpty(void) { return (aHead == NULL); }

void DList::repr(ECampos pCampo, bool pRev) { 

    if (aHead) {

        switch(pCampo){
        case ECampos::nombre : aINom->repr(pRev); break;
        case ECampos::apellido : aIApe->repr(pRev); break;
        case ECampos::fnac : aIFNa->repr(pRev); break;
        case ECampos::salario : aISal->repr(pRev); break;
        }
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
