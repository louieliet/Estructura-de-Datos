#include "Ej02source.cpp"

int main() {

	Arbol lArb = Arbol();
    lArb.read("Ej02.txt");
    lArb.repr(Orden::desc);
    lArb.write("Ej02out.txt",Orden::desc);
}

