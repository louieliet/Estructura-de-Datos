#include "Arbol.cpp"

int main(){
    
    Arbol lArb = Arbol();

    lArb.push("Manzana");
    lArb.push("Platano");
    lArb.push("Pera");
    lArb.push("Durazno");
    lArb.push("Naranja");
    lArb.push("Cereza");
    lArb.push("Rambutan");
    lArb.push("Aguacate");

    lArb.repr(Orden::asc);
    cout << endl;

    lArb.delr("Manzana");

    lArb.repr(Orden::asc);
    cout << endl;

    lArb.delr("Durazno");
    lArb.delr("Cereza");
    lArb.delr("Aguacate");

    lArb.repr(Orden::asc);
    cout << endl;
}