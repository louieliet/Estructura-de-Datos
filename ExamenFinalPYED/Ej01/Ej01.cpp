#include "Ej01source.cpp"

int main() {
	Arbol lArb = Arbol();
	Arbol lArb2 = Arbol();

	lArb.read("log.txt",false);
	cout  << "Indexed by IP: " << endl;
	lArb.repr(Orden::desc);
	cout << endl;
	lArb.write("Ej01.txt", Orden::desc);

	cout  << "Indexed by Nombre: " << endl;
	lArb2.read("log.txt",true);
	lArb2.repr(Orden::desc);
	cout << endl;
	lArb2.write("Ej01n.txt", Orden::desc);
}