
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

	lArb.push("1");
	lArb.push("3");
	lArb.push("2");
	lArb.push("5");
	lArb.push("7");

	lArb.reprr(Orden::sinorden);
	cout << endl;
	lArb.reprr(Orden::asc);
	cout << endl;
	lArb.reprr(Orden::desc);
	cout << endl;

	// 5,1,2
	//   	2
	//  1 			5 
	//			3	    7

	//1,2,5 acendente
	//5,2,1 decendente
	//2riz ,1ram,5ram sin orden
	

	


}
