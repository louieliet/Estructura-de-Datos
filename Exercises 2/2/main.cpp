
#include "Cortina.cpp"


int main()
{
    DLHor lLista = DLHor();
    PHNODE lHor = NULL;
    PVNODE lVer = NULL;

    lLista.push("Mexicana","Chilaquiles","2");
    lLista.push("Mexicana","Enfrijoladas","801");

    lLista.max();
    lLista.min();


}
