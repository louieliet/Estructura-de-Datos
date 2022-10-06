#include "DLists.h"

DLIndex::DLIndex(ECampos pType, bool pFrec)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFrec = pFrec;
    aType = pType;
} // Constructor

DLIndex::~DLIndex(void)
{
    clean();
    // cout << "Bye!" << endl;
} // Destructor

void DLIndex::clean(void)
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

void DLIndex::push_front(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        /*bool lDo = true;
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
        if (lDo) {*/
            PDNODE lTemp = getNewNode(pData);
            aHead->sPrev = lTemp;
            lTemp->sNext = aHead;
            aHead = lTemp;
        //}
    }
} // push_front

void DLIndex::push_back(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        /*bool lDo = true;
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
        if (lDo) {*/
        PDNODE lTemp = getNewNode(pData);
        aTail->sNext = lTemp;
        lTemp->sPrev = aTail;
        aTail = lTemp;
        //}
    }
} // push_back

void DLIndex::push(PDATA pData)
{
    if (aHead == NULL) {
        aHead = getNewNode(pData);
        aTail = aHead;
    }
    else {
        if (comp(pData, aHead->sData) <= 0)
            push_front(pData);
        else if (comp(pData, aTail->sData) >= 0)
            push_back(pData);
        else {
            PDNODE lItem = search(pData);
            if (lItem) {
                /*if (aFrec && (lItem->sNombre == pNombre)) {
                    (lItem->sFrec)++;
                }
                else {*/
                    PDNODE lTemp = getNewNode(pData);
                    lTemp->sNext = lItem;
                    lTemp->sPrev = lItem->sPrev;
                    lItem->sPrev->sNext = lTemp;
                    lItem->sPrev = lTemp;
                //}
            }
        }
    }
} // push

void DLIndex::pop_front(void) //borrar la direccion de memoria de aHead
{
    if (aHead) {
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
    else {
        return;
    }
} // pop_front

void DLIndex::pop_back(void) // borra la ultima dirección de memoria, actúa parecido que el pop_front
{
    bool lDo = true;

    if (aHead) {

        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) { //solo que aquí cambia el sNext porque si es la ultima posición, debe ser nulo su next
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }


    }
    else {
        return;
    }

} // pop_back


PDATA DLIndex::get(bool pRev)
{
    PDATA lTemp = NULL;

    if (aHead) {
        if (aCurr == NULL)
            aCurr = (pRev == false ? aHead : aTail);
        else
            aCurr = (pRev == false ? aCurr->sNext : aCurr->sPrev);
        if (aCurr)
            lTemp = aCurr->sData;
    }

    return lTemp;
} // get

PDNODE DLIndex::find(PDATA pData) // solo busca que sea igual a un nombre en una dirección de memoria, si no, regresa NULL
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pData, lTemp->sData) == 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find 

void DLIndex::del(PDATA pData) //borra un elemento cualquiera de la lista
{
    if (aHead) { //verifica que la lista exista
        if (aHead->sData->sNombre == pData->sNombre) //si el string que se quiere borrar es igual al nombre guardado en aHead, hace un pop_front
            pop_front();
        else if (aTail->sData->sNombre == pData->sNombre) //si el string que se quiere borrar es igual al nombre guardado en aTail, hace un pop_back
            pop_back();
        else { //si no está ni en aHead ni aTail
            PDNODE lTemp = find(pData); //busca dónde está el nombre
            if (lTemp) { //si existe esa direccion de memoria
                if (aCurr == lTemp)
                    aCurr = lTemp->sNext;
                lTemp->sPrev->sNext = lTemp->sNext;
                lTemp->sNext->sPrev = lTemp->sPrev;
                delete lTemp;
            }
        }
    }
}

bool DLIndex::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DLIndex::repr(bool pRev)
{
    if (aHead) {
        PDNODE lTemp = (pRev == false ? aHead : aTail);
        while (lTemp) {
            cout << " -> ";
            cout << "[ " << lTemp->sData->sNombre << ", ";
            cout << lTemp->sData->sApellido << ", ";
            cout << lTemp->sData->sFNac << ", ";
            cout << lTemp->sData->sSalario << "] ";
            /*if (aFrec)
                cout << " #" << lTemp->sFrec;*/
            lTemp = (pRev == false ? lTemp->sNext : lTemp->sPrev);
        }
        cout << " ->|| " << endl;
    }
} // repr

int DLIndex::comp(PDATA pA, PDATA pB)
{
    int lRes = 0;

    switch (aType) {
    case ECampos::nombre:
        if (pA->sNombre < pB->sNombre) lRes = -1;
        else if (pA->sNombre == pB->sNombre) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::apellido:
        if (pA->sApellido < pB->sApellido) lRes = -1;
        else if (pA->sApellido == pB->sApellido) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::fnac:
        if (pA->sFNac < pB->sFNac) lRes = -1;
        else if (pA->sFNac == pB->sFNac) lRes = 0;
        else lRes = 1;
        break;
    case ECampos::salario:
        if (pA->sSalario < pB->sSalario) lRes = -1;
        else if (pA->sSalario == pB->sSalario) lRes = 0;
        else lRes = 1;
        break;
    }

    return lRes;
}

PDNODE DLIndex::search(PDATA pData)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (comp(pData, lTemp->sData) <= 0)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // search

PDNODE DLIndex::getNewNode(PDATA pData)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sData = pData;
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode


//-----------


DList::DList(bool pFrec)
{
    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
    aFrec = pFrec;

    aINom = new DLIndex(ECampos::nombre);
    aIApe = new DLIndex(ECampos::apellido);
    aIFNa = new DLIndex(ECampos::fnac);
    aISal = new DLIndex(ECampos::salario);
} // Constructor

DList::~DList(void)
{
    clean();

    if (aINom) delete aINom;
    if (aIApe) delete aIApe;
    if (aIFNa) delete aIFNa;
    if (aISal) delete aISal;

} // Destructor

void DList::clean(void)
{
    while (aHead) {
        PDNODE lTemp = aHead->sNext;
        if (aHead->sData)
            delete aHead->sData;
        delete aHead;
        aHead = lTemp;
    }

    aHead = NULL;
    aTail = NULL;
    aCurr = NULL;
} // clean

void DList::push_back(string pNombre, string pApellido,
    string pFNac, double pSalario)
{
    if (aHead == NULL) {
        aHead = getNewNode(pNombre, pApellido, pFNac, pSalario);
        aTail = aHead;

        aINom->push(aHead->sData);
        aIApe->push(aHead->sData);
        aIFNa->push(aHead->sData);
        aISal->push(aHead->sData);
    }
    else {
        /*bool lDo = true;
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
        if (lDo) {*/
            PDNODE lTemp = getNewNode(pNombre, pApellido, pFNac, pSalario);
            aTail->sNext = lTemp;
            lTemp->sPrev = aTail;
            aTail = lTemp;

            aINom->push(lTemp->sData);
            aIApe->push(lTemp->sData);
            aIFNa->push(lTemp->sData);
            aISal->push(lTemp->sData);
        //}
    }
} // push_back

void DList::pop_front(void) //borrar la direccion de memoria de aHead
{
    if (aHead) {
        PDNODE lTemp = aHead->sNext; //crea una direccion de memoria temporal con la siguiente direccion de memoria al aHead
        bool lEqual = (aHead == aCurr); //si el aHead es igual al Acurr, lEqual será verdadero, sino falso
        delete aHead; //borra el aHead
        aHead = lTemp; //ahora el aHead será la variable temporal
        if (aHead) { //si existe el aHead
            aHead->sPrev = NULL; //el previo del aHead será nulo 
            aCurr = (lEqual ? aHead : aCurr); //y aCurr será aHead si estaba en el aHead, sino seguirá siendo aCurr
        }
        else { //si no existe la lista, el aTail y el aCurr serán nulos
            aTail = NULL;
            aCurr = NULL;
        }
    }
} // pop_front

void DList::pop_back(void) // borra la ultima dirección de memoria, actúa parecido que el pop_front
{
    if (aHead) {
        PDNODE lTemp = aTail->sPrev;
        bool lEqual = (aTail == aCurr);
        delete aTail;
        aTail = lTemp;
        if (aTail) { //solo que aquí cambia el sNext porque si es la ultima posición, debe ser nulo su next
            aTail->sNext = NULL;
            aCurr = (lEqual ? aTail : aCurr);
        }
        else {
            aHead = NULL;
            aCurr = NULL;
        }
    }
} // pop_back

PDATA DList::get(ECampos pCampo, bool pRev)
{
    PDATA lTemp = NULL;

    switch (pCampo) {
        case ECampos::nombre: lTemp = aINom->get(pRev); break;
        case ECampos::apellido: lTemp = aIApe->get(pRev); break;
        case ECampos::fnac: lTemp = aIFNa->get(pRev); break;
        case ECampos::salario: lTemp = aISal->get(pRev); break;
    }

    return lTemp;
} // get


void DList::del(string pNombre)
{
    PDNODE lTemp = find(pNombre);
    if (lTemp) {
        aINom->del(lTemp->sData);
        aIApe->del(lTemp->sData);
        aIFNa->del(lTemp->sData);
        aISal->del(lTemp->sData);
    }
    if (aHead->sData->sNombre == pNombre) {
        pop_front();
    }
    else if (aTail->sData->sNombre == pNombre) {
        pop_back();
    }
    else {
        if (lTemp) {
            if (aCurr == lTemp)
                aCurr = lTemp->sNext;
            lTemp->sPrev->sNext = lTemp->sNext;
            lTemp->sNext->sPrev = lTemp->sPrev;
            delete lTemp;
        }
    }
} // del

bool DList::isEmpty(void)
{
    return (aHead == NULL);
} // isEmpty

void DList::repr(ECampos pCampo, bool pRev)
{
    if (aHead) {
        switch (pCampo) {
            case ECampos::nombre: aINom->repr(pRev); break;
            case ECampos::apellido: aIApe->repr(pRev); break;
            case ECampos::fnac: aIFNa->repr(pRev); break;
            case ECampos::salario: aISal->repr(pRev); break;
        }
    }
} // repr


PDNODE DList::find(string pNombre)
{
    PDNODE lTemp = aHead;

    while (lTemp) {
        if (pNombre == lTemp->sData->sNombre)
            return lTemp;
        lTemp = lTemp->sNext;
    }

    return NULL;
} // find


PDNODE DList::getNewNode(string pNombre, string pApellido,
    string pFNac, double pSalario)
{
    PDNODE lTemp = new DNODE;

    if (lTemp) {
        lTemp->sData = new DATA;
        if (lTemp->sData) {
            lTemp->sData->sNombre = pNombre;
            lTemp->sData->sApellido = pApellido;
            lTemp->sData->sFNac = pFNac;
            lTemp->sData->sSalario = pSalario;
        }
        lTemp->sFrec = 1;
        lTemp->sNext = NULL;
        lTemp->sPrev = NULL;
    }

    return lTemp;
} // getNewNode
