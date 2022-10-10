#include "DLists.cpp"

int main(){

    DList lLista = DList();

    lLista.push_back("Albert","Einstein","1879-03-14",100);
    lLista.push_back("Issac","Newton","1643-01-04",300);
    lLista.push_back("Neils","Bohr","1885-10-07",200);
    lLista.push_back("Hipatia","De Alejandria","455-01-01",90);

    lLista.repr(ECampos::nombre);

    cout << endl;
    
    lLista.del("Issac");
    lLista.del("Neils");


    lLista.repr(ECampos::nombre);

    /*lLista.repr(ECampos::salario);

    cout << endl;

    PDATA lItem = NULL;
    while(lItem = lLista.get(ECampos::apellido, true)){
        cout << "" << lItem->sNombre << " " << lItem->sApellido << endl;
    }*/
    
}


