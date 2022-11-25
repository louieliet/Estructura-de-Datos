#include "Arbol.h"

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
	cout << "Bye!" << endl;
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
			if (lTemp->sLft)
				pushr(pVal, lTemp->sLft);
			else
				lTemp->sLft = getNewNode(pVal);
		} 
		else if (pVal >= lTemp->sVal) {
			if (lTemp->sRgt)
				pushr(pVal, lTemp->sRgt);
			else
				lTemp->sRgt = getNewNode(pVal);
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
				if (lTemp->sLft)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(pVal);
					lTemp = NULL;
				}
			}
			else if (pVal > lTemp->sVal) {
				// Mayores
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(pVal);
					lTemp = NULL;
				}
			}
			else {
				// Iguales
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(pVal);
					lTemp = NULL;
				}
			}
		}
	}
} // push

void Arbol::delr(string pVal)
{
	aRoot = pdelr(aRoot, pVal);
} // del

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
	if (aRoot) {
		PTNODE lTemp = aRoot;
		if (pSub)
			lTemp = pSub;
		switch (pOrd) {
			case Orden::asc:
				if (lTemp->sLft) reprr(pOrd, lTemp->sLft);
				cout << lTemp->sVal << ", ";
				if (lTemp->sRgt) reprr(pOrd, lTemp->sRgt);
				break;
			case Orden::desc:
				if (lTemp->sRgt) reprr(pOrd, lTemp->sRgt);
				cout << lTemp->sVal << ", ";
				if (lTemp->sLft) reprr(pOrd, lTemp->sLft);
				break;
			case Orden::sinorden:
				cout << lTemp->sVal << ", ";
				if (lTemp->sLft) reprr(pOrd, lTemp->sLft);
				if (lTemp->sRgt) reprr(pOrd, lTemp->sRgt);
				break;
		}
	}
} // reprr

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
					cout << lTemp->sVal << ", ";
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
					cout << lTemp->sVal << ", ";
					lTemp = lTemp->sLft;
				}
				break;
			case Orden::sinorden:
				if (lTemp) {
					cout << lTemp->sVal << ", ";
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

void Arbol::read(string pPath)
{
	auto lStart = chrono::high_resolution_clock::now();
	string lLine = "";
	ifstream lFile(pPath);

	while (getline(lFile, lLine)) {
		push(lLine);
	}

	lFile.close();

	auto lElapsed = chrono::high_resolution_clock::now() - lStart;
	long long lMS = chrono::duration_cast<chrono::microseconds>
		(lElapsed).count();
	cout << lMS << " ms" << endl;
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
						lFile << lTemp->sVal << endl;
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
						lFile << lTemp->sVal << endl;
						lTemp = lTemp->sLft;
					}
					break;
				case Orden::sinorden:
					if (lTemp) {
						lFile << lTemp->sVal << endl;
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

PTNODE Arbol::pdelr(PTNODE pSub, string pVal)
{
	if (pSub == NULL)
		return pSub;

	if (pVal < pSub->sVal) {
		// Menores
		pSub->sLft = pdelr(pSub->sLft, pVal);
	}
	else if (pVal > pSub->sVal) {
		// Mayores
		pSub->sRgt = pdelr(pSub->sRgt, pVal);
	}
	else {
		// Igual

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

		// 2 hijos
		PTNODE lTemp = min(pSub->sRgt);

		pSub->sVal = lTemp->sVal; // Borrado virtual

		pSub->sRgt = pdelr(pSub->sRgt, lTemp->sVal);
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
	}

	return lTemp;
} // getNewNode
