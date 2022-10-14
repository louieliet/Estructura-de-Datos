#include "Arbol.cpp"

int main(){
    
    Arbol lArb = Arbol();

    lArb.pushr("Manzana");
    lArb.pushr("Platanos");
    lArb.pushr("Pera");
    lArb.pushr("Durazno");
    lArb.pushr("Naranja");
    lArb.pushr("Cereza");
    lArb.pushr("Rambutan");
    lArb.pushr("Aguacate");

    lArb.repr();
    cout << endl;

    lArb.repr(Orden::desc);
    cout << endl;
    
    lArb.repr(Orden::sinorden);
    cout << endl;
}