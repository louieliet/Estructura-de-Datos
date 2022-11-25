#include <iostream>
#include <fstream>
#include <stack>
#include <chrono>
#include <string>
#include <sstream> 
#include <vector>

using namespace std;

typedef struct TNODE* PTNODE;

struct TNODE {
	string pVal[7];
	PTNODE sLft;
	PTNODE sRgt;
};

enum class Orden { asc, desc, sinorden };

class Arbol
{
protected:
	PTNODE aRoot;

public:
	Arbol(void);
	~Arbol(void);

	void clean(PTNODE pSub = NULL);


	void push(string pVal1, string pVal2, string pVal3, string pVal4, string pVal5,
		string pVal6, string pVal7);

	void pushbyname(string pVal1, string pVal2, string pVal3, string pVal4, string pVal5,
		string pVal6, string pVal7);


	void runGet(void(*pFunc)(string));

	void reprr(Orden pOrd = Orden::asc, PTNODE pSub = NULL);
	void repr(Orden pOrd = Orden::asc);

	void read(string pPath, bool name);
	void write(string pPath, Orden pOrd = Orden::sinorden);

private:

	PTNODE min(PTNODE pSub);
	PTNODE getNewNode(string pVal1, string pVal2, string pVal3, string pVal4, string pVal5,
		string pVal6, string pVal7);
};

Arbol::Arbol(void)
{
	aRoot = NULL;
} // Constructor

Arbol::~Arbol(void)
{
	clean();
} // Destructor

void Arbol::clean(PTNODE pSub)
{
	if (aRoot) {
		PTNODE lTemp = aRoot;
		if (pSub)
			lTemp = pSub;
		if (lTemp->sLft) clean(lTemp->sLft);
		if (lTemp->sRgt) clean(lTemp->sRgt);
		bool lRoot = lTemp == aRoot;
		delete lTemp;
		if (lRoot)
			aRoot = NULL;
	}

} // clean

void Arbol::push(string pVal1, string pVal2, string pVal3, string pVal4, string pVal5,
	string pVal6, string pVal7)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
			pVal6, pVal7);
	}
	else {
		PTNODE lTemp = aRoot;
		while (lTemp) {
			if (pVal1 < lTemp->pVal[0]) {
				// Menores
				if (lTemp->sLft)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
						pVal6, pVal7);
					lTemp = NULL;
				}
			}
			else if (pVal1 > lTemp->pVal[0]) {
				// Mayores
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
						pVal6, pVal7);
					lTemp = NULL;
				}
			}
			else {
				// Iguales
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
						pVal6, pVal7);
					lTemp = NULL;
				}
			}
		}
	}
} // push

void Arbol::pushbyname(string pVal1, string pVal2, string pVal3, string pVal4, string pVal5,
	string pVal6, string pVal7)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
			pVal6, pVal7);
	}
	else {
		PTNODE lTemp = aRoot;
		while (lTemp) {
			if (pVal1 < lTemp->pVal[3]) {
				// Menores
				if (lTemp->sLft)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
						pVal6, pVal7);
					lTemp = NULL;
				}
			}
			else if (pVal1 > lTemp->pVal[3]) {
				// Mayores
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
						pVal6, pVal7);
					lTemp = NULL;
				}
			}
			else {
				// Iguales
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(pVal1, pVal2, pVal3, pVal4, pVal5,
						pVal6, pVal7);
					lTemp = NULL;
				}
			}
		}
	}
} // push


void Arbol::repr(Orden pOrd)
{
	if (aRoot) {
		PTNODE lTemp = aRoot;
		stack<PTNODE> lStack;

		while (lTemp || (lStack.empty() == false)) {
			switch (pOrd) {
			case Orden::asc:
				if (lTemp) {
					lStack.push(lTemp);
					lTemp = lTemp->sLft;
				}
				else {
					lTemp = lStack.top();
					lStack.pop();
					cout << lTemp->pVal[0] << ", ";
					cout << lTemp->pVal[1] << ", ";
					cout << lTemp->pVal[2] << ", ";
					cout << lTemp->pVal[3] << ", ";
					cout << lTemp->pVal[4] << ", ";
					cout << lTemp->pVal[5] << ", ";
					cout << lTemp->pVal[6] << " | ";

					lTemp = lTemp->sRgt;
				}
				break;
			case Orden::desc:
				if (lTemp) {
					lStack.push(lTemp);
					lTemp = lTemp->sRgt;
				}
				else {
					lTemp = lStack.top();
					lStack.pop();
					cout << lTemp->pVal[0] << ", ";
					cout << lTemp->pVal[1] << ", ";
					cout << lTemp->pVal[2] << ", ";
					cout << lTemp->pVal[3] << ", ";
					cout << lTemp->pVal[4] << ", ";
					cout << lTemp->pVal[5] << ", ";
					cout << lTemp->pVal[6] << " | ";
					lTemp = lTemp->sLft;
				}
				break;
			case Orden::sinorden:
				if (lTemp) {
					cout << lTemp->pVal[0] << ", ";
					cout << lTemp->pVal[1] << ", ";
					cout << lTemp->pVal[2] << ", ";
					cout << lTemp->pVal[3] << ", ";
					cout << lTemp->pVal[4] << ", ";
					cout << lTemp->pVal[5] << ", ";
					cout << lTemp->pVal[6] << " | ";
					lStack.push(lTemp);
					lTemp = lTemp->sLft;
				}
				else {
					lTemp = lStack.top();
					lStack.pop();
					lTemp = lTemp->sRgt;
				}
				break;
			}
		}
	}
} // repr

void Arbol::read(string pPath, bool name)
{
	string lLine = "";
	ifstream lFile(pPath);
	vector<string> data;

	while (getline(lFile, lLine, '\n')) {
		
		data.clear();
		string strArr = lLine;
		stringstream test(strArr);
		string tokens;
		while (getline(test, tokens, ';')) {
			data.push_back(tokens);

		}
		if(name == true)
			pushbyname(data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
		else
			push(data[0], data[1], data[2], data[3], data[4], data[5], data[6]);
			
		
	}


	lFile.close();

} // read

void Arbol::write(string pPath, Orden pOrd)
{
	if (aRoot) {
		PTNODE lTemp = aRoot;
		stack<PTNODE> lStack;
		ofstream lFile(pPath);

		if (lFile.is_open()) {
			while (lTemp || (lStack.empty() == false)) {
				switch (pOrd) {
				case Orden::asc:
					if (lTemp) {
						lStack.push(lTemp);
						lTemp = lTemp->sLft;
					}
					else {
						lTemp = lStack.top();
						lStack.pop();
						lFile << lTemp->pVal[0] << ", ";
						lFile << lTemp->pVal[1] << ", ";
						lFile << lTemp->pVal[2] << ", ";
						lFile << lTemp->pVal[3] << ", ";
						lFile << lTemp->pVal[4] << ", ";
						lFile << lTemp->pVal[5] << ", ";
						lFile << lTemp->pVal[6] << " | ";
						lTemp = lTemp->sRgt;
					}
					break;
				case Orden::desc:
					if (lTemp) {
						lStack.push(lTemp);
						lTemp = lTemp->sRgt;
					}
					else {
						lTemp = lStack.top();
						lStack.pop();
						lFile << lTemp->pVal[0] << ", ";
						lFile << lTemp->pVal[1] << ", ";
						lFile << lTemp->pVal[2] << ", ";
						lFile << lTemp->pVal[3] << ", ";
						lFile << lTemp->pVal[4] << ", ";
						lFile << lTemp->pVal[5] << ", ";
						lFile << lTemp->pVal[6] << " | ";
						lTemp = lTemp->sLft;
					}
					break;
				case Orden::sinorden:
					if (lTemp) {
						lFile << lTemp->pVal[0] << ", ";
						lFile << lTemp->pVal[1] << ", ";
						lFile << lTemp->pVal[2] << ", ";
						lFile << lTemp->pVal[3] << ", ";
						lFile << lTemp->pVal[4] << ", ";
						lFile << lTemp->pVal[5] << ", ";
						lFile << lTemp->pVal[6] << " | ";
						lStack.push(lTemp);
						lTemp = lTemp->sLft;
					}
					else {
						lTemp = lStack.top();
						lStack.pop();
						lTemp = lTemp->sRgt;
					}
					break;
				}
			}
			lFile.close();
		}
	}
} // write



PTNODE Arbol::getNewNode(string pVal1, string pVal2, string pVal3, string pVal4, string pVal5,
	string pVal6, string pVal7)
{
	PTNODE lTemp = new TNODE;

	if (lTemp) {
		lTemp->pVal[0] = pVal1;
		lTemp->pVal[1] = pVal2;
		lTemp->pVal[2] = pVal3;
		lTemp->pVal[3] = pVal4;
		lTemp->pVal[4] = pVal5;
		lTemp->pVal[5] = pVal6;
		lTemp->pVal[6] = pVal7;
		lTemp->sLft = NULL;
		lTemp->sRgt = NULL;
	}

	return lTemp;
} // getNewNode



int main() {
	Arbol lArb = Arbol();
	Arbol lArbName = Arbol();

	lArb.read("Ej01.txt",false);
	cout  << "By SKU" << endl;
	lArb.repr(Orden::asc);
	cout << endl;
	lArb.write("Ej01_w.txt", Orden::asc);

	cout  << "By Name" << endl;
	lArbName.read("Ej01.txt",true);
	lArbName.repr(Orden::asc);
	cout << endl;
	lArbName.write("Ej01_wn.txt", Orden::asc);
}