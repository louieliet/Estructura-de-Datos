
#include "Cortina.cpp"


int main()
{
    DLHor lLista = DLHor();
    PHNODE lHor = NULL;
    PVNODE lVer = NULL;

    lLista.push("Mexicana","Chilaquiles","2");
    lLista.push("Mexicana","Enfrijoladas","801");

    lLista.push("Peruana","Palomas","40");
    lLista.push("Peruana","Tierra","3");

    lLista.repr();

    lLista.max();
    lLista.min();


}
