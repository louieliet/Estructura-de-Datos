
#include "Arbol.cpp"

string gTodas = "";

void showVal(string pVal)
{
	cout << "De afuera: " << pVal << endl;
	gTodas += pVal + " ";
} // showVal

int main()
{
	Arbol lArb = Arbol();

	lArb.read("C:/temp/PyED/LTolstoy_WAP.txt");

	/*lArb.push("Manzana");
	lArb.push("Platano");
	lArb.push("Pera");
	lArb.push("Durazno");
	lArb.push("Naranja");
	lArb.push("Cereza");
	lArb.push("Rambutan");
	lArb.push("Aguacate");

	lArb.repr();
	cout << endl;

	lArb.write("C:/temp/PyED/arb_01_asc", Orden::asc);
	lArb.write("C:/temp/PyED/arb_01_desc", Orden::desc);
	lArb.write("C:/temp/PyED/arb_01");*/

	/*lArb.push("Manzana");
	lArb.push("Platano");
	lArb.push("Pera");
	lArb.push("Durazno");
	lArb.push("Naranja");
	lArb.push("Cereza");
	lArb.push("Rambutan");
	lArb.push("Aguacate");

	lArb.repr();
	cout << endl;

	lArb.runGet(&showVal);
	cout << gTodas << endl;*/

	// lArb.repr(Orden::desc);
	// cout << endl;
	// lArb.repr(Orden::sinorden);
	// cout << endl;

	/*lArb.delr("Manzana");
	lArb.repr();
	cout << endl;

	lArb.delr("Durazno");
	lArb.delr("Cereza");
	lArb.delr("Aguacate");
	lArb.repr();
	cout << endl;*/

}
