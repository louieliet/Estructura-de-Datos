#include "Arbol.cpp"

int main(){
    
    Arbol lArb = Arbol();

    lArb.push("Manzana");
    lArb.push("Platanos");
    lArb.push("Pera");
    lArb.push("Durazno");
    lArb.push("Naranja");
    lArb.push("Cereza");
    lArb.push("Rambutan");
    lArb.push("Aguacate");

    lArb.repr(Orden::asc);
    cout << endl;
    lArb.repr(Orden::desc);
    cout << endl;
    lArb.repr(Orden::sinorden);
    cout << endl;
}