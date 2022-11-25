#include <fstream>
#include <chrono>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

typedef struct TNODE* PTNODE;

struct TNODE {
	string sVal;
	int sFrec;
	PTNODE sLft;
	PTNODE sRgt;
};

enum class Orden { asc, desc, sinorden };

class Arbol
{
protected:
	PTNODE aRoot;
	bool aChkFrec;
	long long aMicroSeconds;

public:
	Arbol(bool pChkFrec = false);
	~Arbol(void);

	void clean(PTNODE pSub = NULL);

	void pushr(string pVal, PTNODE pSub = NULL);
	void push(string pVal);
	void read(string pPath);

	void delr(string pVal, bool pForce = false);
	long long getMS(void);

	void runGet(void(*pFunc)(string));

	void reprr(Orden pOrd = Orden::asc, PTNODE pSub = NULL);
	void repr(Orden pOrd = Orden::asc);

private:
	PTNODE pdelr(PTNODE pSub, string pVal, bool pForce = false);
	PTNODE min(PTNODE pSub);
	PTNODE getNewNode(string pVal);
};



Arbol::Arbol(bool pChkFrec)
{
	aRoot = NULL;
	aChkFrec = pChkFrec;
	aMicroSeconds = 0;
} // Constructor

Arbol::~Arbol(void)
{
	clean();
} // Destructor

void Arbol::clean(PTNODE pSub)
{
	PTNODE lTemp = aRoot;
	bool lRoot = false;
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

void Arbol::pushr(string pVal, PTNODE pSub)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(pVal);
	}
	else {
		PTNODE lTemp = aRoot;
		if (pSub)
			lTemp = pSub;
		if (pVal < lTemp->sVal) {
			if (lTemp->sLft != NULL)
				pushr(pVal, lTemp->sLft);
			else {
				lTemp->sLft = getNewNode(pVal);
			}
		}
		else if (pVal >= lTemp->sVal) {
			if (lTemp->sRgt != NULL) {
				pushr(pVal, lTemp->sRgt);
			}
			else {
				lTemp->sRgt = getNewNode(pVal);
			}
		}
		else {
			if (aChkFrec) {
				lTemp->sFrec++;
				lTemp = NULL;
			}
			else {
				// Repite el código de la Derecha
				if (lTemp->sRgt != NULL) {
					pushr(pVal, lTemp->sRgt);
				}
				else {
					lTemp->sRgt = getNewNode(pVal);
				}
			}
		}
	}


} // pushr

void Arbol::push(string pVal)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(pVal);
	}
	else {
		PTNODE lTemp = aRoot;
		while (lTemp) {
			if (pVal < lTemp->sVal) {
				// Menores
				if (lTemp->sLft != NULL)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(pVal);
					lTemp = NULL;
				}
			}
			else if (pVal > lTemp->sVal) {
				// Mayores
				if (lTemp->sRgt != NULL) {
					lTemp = lTemp->sRgt;
				}
				else {
					lTemp->sRgt = getNewNode(pVal);
					lTemp = NULL;
				}
			}
			else {
				// Iguales
				if (aChkFrec) {
					lTemp->sFrec++;
					lTemp = NULL;
				}
				else {
					if (lTemp->sRgt != NULL) {
						lTemp = lTemp->sRgt;
					}
					else {
						lTemp->sRgt = getNewNode(pVal);
						lTemp = NULL;
					}
				}
			}
		}
	}
} // push

void Arbol::delr(string pVal, bool pForce)
{
	aRoot = pdelr(aRoot, pVal, pForce);
} // del

long long Arbol::getMS(void)
{
	return aMicroSeconds;
} // getMS


void Arbol::runGet(void(*pFunc)(string))
{
	if (aRoot && (pFunc != NULL)) {
		PTNODE lTemp = aRoot;
		stack<PTNODE> lStack;

		while (lTemp || (lStack.empty() == false)) {
			if (lTemp) {
				lStack.push(lTemp);
				lTemp = lTemp->sLft;
			}
			else {
				lTemp = lStack.top();
				lStack.pop();
				pFunc(lTemp->sVal);
				lTemp = lTemp->sRgt;
			}
		}
	}
} // runGet

void Arbol::reprr(Orden pOrd, PTNODE pSub)
{
	PTNODE lTemp = aRoot;
	int num = 1;
	if (aRoot) {
		if (pSub != NULL)
			lTemp = pSub;
		switch (pOrd) {
		case Orden::asc:
			if (lTemp->sLft != NULL) reprr(pOrd, lTemp->sLft);
			cout << num << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")" : "") << ", ";
			if (lTemp->sRgt != NULL) reprr(pOrd, lTemp->sRgt);
			break;
		case Orden::desc:
			if (lTemp->sRgt != NULL) reprr(pOrd, lTemp->sRgt);
			cout << num << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")" : "") << ", ";
			if (lTemp->sLft != NULL) reprr(pOrd, lTemp->sLft);
			break;
		case Orden::sinorden:
			cout << num << lTemp->sVal << (aChkFrec ? "(" + to_string(lTemp->sFrec) + ")" : "") << ", ";
			if (lTemp->sLft != NULL) reprr(pOrd, lTemp->sLft);
			if (lTemp->sRgt != NULL) reprr(pOrd, lTemp->sRgt);
			break;
		}
	}
} // reprr

void Arbol::read(string pPath)
{
	auto lStart = chrono::high_resolution_clock::now();
	ifstream lFile;
	string lLine = "";
	lFile.open(pPath, ios::app);

	while (getline(lFile, lLine)) {

		push(lLine);
	}

	lFile.close();

	auto lElapsed = chrono::high_resolution_clock::now() - lStart;
	long long lMS = chrono::duration_cast<chrono::microseconds>
		(lElapsed).count();
} // read

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
					cout << "(" << lTemp->sFrec << ")";
					cout << "Libro:" << lTemp->sVal << endl;
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
					cout << "(" << lTemp->sFrec << ")";
					cout << "Libro:" << lTemp->sVal << endl;
					lTemp = lTemp->sLft;
				}
				break;
			case Orden::sinorden:
				if (lTemp) {
					cout << "(" << lTemp->sFrec << ")";
					cout << "Libro:" << lTemp->sVal << endl;
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

PTNODE Arbol::pdelr(PTNODE pSub, string pVal, bool pForce)
{
	if (pSub == NULL)
		return pSub;

	if (pVal < pSub->sVal) {
		// Menores
		pSub->sLft = pdelr(pSub->sLft, pVal, pForce);
	}
	else if (pVal > pSub->sVal) {
		// Mayores
		pSub->sRgt = pdelr(pSub->sRgt, pVal, pForce);
	}
	else {
		// Igual
		// Hay que borrar

		if (pForce)
			pSub->sFrec = 1;
		if (aChkFrec && (pSub->sFrec > 1)) {
			pSub->sFrec--;
			return pSub;
		}
		{

			// 0 o +1 hijos
			if (pSub->sLft == NULL) {
				PTNODE lTemp = pSub->sRgt;
				delete pSub;
				return lTemp;
			}
			else if (pSub->sRgt == NULL) {
				PTNODE lTemp = pSub->sLft;
				delete pSub;
				return lTemp;
			}
			else
				if (pSub->sRgt == NULL) {
					PTNODE lTemp = pSub->sLft;
					delete pSub;
					return lTemp;
				}
		}

		// 2 hijos
		PTNODE lTemp = min(pSub->sRgt);

		pSub->sVal = lTemp->sVal; // Borrado virtual

		pSub->sRgt = pdelr(pSub->sRgt, lTemp->sVal, false);
	}

	return pSub;
} // pdelr

PTNODE Arbol::min(PTNODE pSub)
{
	PTNODE lTemp = pSub;

	while (lTemp && (lTemp->sLft))
		lTemp = lTemp->sLft;

	return lTemp;
} // min

PTNODE Arbol::getNewNode(string pVal)
{
	PTNODE lTemp = new TNODE;

	if (lTemp) {
		lTemp->sVal = pVal;
		lTemp->sLft = NULL;
		lTemp->sRgt = NULL;
		lTemp->sFrec = 1;
	}

	return lTemp;
} // getNewNode

string gTodas = "";

void showVal(string pVal)
{
	cout << "De afuera: " << pVal << endl;
	gTodas += pVal + " ";
} // showVal

int main()
{

	Arbol lArb = Arbol(true);
	lArb.read("Libros_Prueba.txt");
	lArb.repr(Orden::asc);

	cout << endl << endl;

}
