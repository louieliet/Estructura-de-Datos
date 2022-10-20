
#include "Cortina.cpp"


int main()
{
    DLHor lLista = DLHor();
    PHNODE lHor = NULL;
    PVNODE lVer = NULL;

    lLista.push("Mexicana","Chilaquiles","2");
    lLista.push("Mexicana","Enfrijoladas","801");
    lLista.push("Mexicana","Tortas","1");
    lLista.push("Peruana","Palomas","801");
    lLista.push("Peruana","Aire con tierra","4");
    lLista.push("Peruana","Cuyos","1");

    lLista.max();

}
