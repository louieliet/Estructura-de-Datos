#include "DLists.cpp"

int main()
{
    DList lLista = DList();

    lLista.push_front("uno");
    lLista.push_front("dos");
    lLista.push_front("tres");
    lLista.push_front("cuatro");
    lLista.push_front("cinco");

    lLista.repr();

    lLista.get();
    lLista.get();

    PDNODE lItem = lLista.get();

    lItem->sPrev = NULL;
    lLista.repr();
    lLista.repr(true);

}


