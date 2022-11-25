
#include "Cortina.cpp"


int main()
{
    DLHor lLista = DLHor();
    PHNODE lHor = NULL;
    PVNODE lVer = NULL;

    cout << "1) Insertar 3 cats. con sus elementos." << endl;
    lLista.push("cat 01", "main 01", "extra 01");
    lLista.push("cat 01", "main 03", "extra 03");
    lLista.push("cat 02", "main 2-02", "extra 2-02");
    lLista.push("cat 02", "main 2-01", "extra 2-01");
    lLista.push("cat 03", "main", "extra");
    lLista.push("cat 01", "main 02", "extra 02");
    lLista.repr();
    cout << "---" << endl;
    lLista.repr(true);
    
    cout << endl << "2) Borrar elementos en 1 y 3 y toda la cat 2." << endl;
    lLista.del("cat 01", "main 02");
    lLista.del("cat 03", "main");
    lLista.del("cat 02");
    lLista.repr();
    lLista.clean();

    cout << endl << "3) Insertar de nuevo todos." << endl;
    lLista.push("cat 01", "main 01", "extra 01");
    lLista.push("cat 01", "main 03", "extra 03");
    lLista.push("cat 02", "main 2-02", "extra 2-02");
    lLista.push("cat 02", "main 2-01", "extra 2-01");
    lLista.push("cat 03", "main", "extra");
    lLista.push("cat 01", "main 02", "extra 02");
    lLista.repr();

    cout << endl << "4) Listar todos con get." << endl;
    do {
        lLista.get(&lHor, &lVer);
        if (lHor) {
            cout << lHor->sCat << endl;
            if (lVer) {
                cout << "\t" << lVer->sMain << ", " << lVer->sExtra << endl;
            }
        }
    } while (lHor != NULL);

    cout << endl << "5) Listar todos con get, en reversa." << endl;
    do {
        lLista.get(&lHor, &lVer, true);
        if (lHor) {
            cout << lHor->sCat << endl;
            if (lVer) {
                cout << "\t" << lVer->sMain << ", " << lVer->sExtra << endl;
            }
        }
    } while (lHor != NULL);

    cout << endl << "6) Obtener con get un elemento particular." << endl;
    lLista.get(&lHor, &lVer, "cat 02", "main 2-02");
    if (lHor) {
        cout << lHor->sCat << endl;
        if (lVer) {
            cout << "\t" << lVer->sMain << ", " << lVer->sExtra << endl;
        }
    }

    /*cout << endl << "7) Guardar a disco, limpiar memoria, leer de disco y listar." << endl;
    lLista.write("C:/temp/PyED/cortina.txt");
    lLista.clean();
    lLista.read("C:/temp/PyED/cortina.txt");
    lLista.repr();*/

}
