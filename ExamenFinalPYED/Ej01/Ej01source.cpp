#include "Ej01.h"

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

void Arbol::push(string sDataIP1, string sDataIP2, string sDataIP3, string sDataIP4, string sDataIP5,
	string sDataIP6, int sDataErr)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
			sDataIP6, sDataErr);
	}
	else {
		PTNODE lTemp = aRoot;
		while (lTemp) {
			if (sDataIP1 < lTemp->sDataIP[3]) {
				if (lTemp->sLft)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
						sDataIP6, sDataErr);
					lTemp = NULL;
				}
			}
			else if (sDataIP1 > lTemp->sDataIP[3]) {
				// Mayores
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
						sDataIP6, sDataErr);
					lTemp = NULL;
				}
			}
			else {
				// Iguales
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
						sDataIP6, sDataErr);
					lTemp = NULL;
				}
			}
		}
	}
} // push

void Arbol::pushn
(string sDataIP1, string sDataIP2, string sDataIP3, string sDataIP4, string sDataIP5,
	string sDataIP6, int sDataErr)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
			sDataIP6, sDataErr);
	}
	else {
		PTNODE lTemp = aRoot;
		while (lTemp) {
			if (sDataIP1 < lTemp->sDataIP[2]) {
				// Menores
				if (lTemp->sLft)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
						sDataIP6, sDataErr);
					lTemp = NULL;
				}
			}
			else if (sDataIP1 > lTemp->sDataIP[2]) {
				// Mayores
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
						sDataIP6, sDataErr);
					lTemp = NULL;
				}
			}
			else {
				// Iguales
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(sDataIP1, sDataIP2, sDataIP3, sDataIP4, sDataIP5,
						sDataIP6, sDataErr);
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
                    for(auto i : lTemp->sDataIP){
                        cout << i << ", ";
                    }
                    cout << "w err: " << lTemp->sDataErr << endl;
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
                    for(auto i : lTemp->sDataIP){
                        cout << i << ", ";
                    }
                    cout << "w err: " << lTemp->sDataErr << endl;
					lTemp = lTemp->sLft;
				}
				break;
			case Orden::sinorden:
				if (lTemp) {
                    for(auto i : lTemp->sDataIP){
                        cout << i << ", ";
                    }
                    cout << "w err: " << lTemp->sDataErr << endl;
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
	vector<string> sElements;

	while (getline(lFile, lLine, '\n')) {
		sElements.clear();
		string array = lLine;
		stringstream lLine2(array);
		string element;
		while (getline(lLine2, element, ';')) {
			sElements.push_back(element);
		}
		if(name){
			pushn(sElements[0], sElements[1], sElements[2], sElements[3], 
                    sElements[4], sElements[5], stoi(sElements[6]));
        }
        else{
			push(sElements[0], sElements[1], sElements[2], sElements[3], 
                    sElements[4], sElements[5], stoi(sElements[6]));
            
        }
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
                        for(auto i : lTemp->sDataIP){
                            lFile << i << ", ";
                        }
                        lFile << "w err: " << lTemp->sDataErr << endl;
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
                        for(auto i : lTemp->sDataIP){
                            lFile << i << ", ";
                        }
                        lFile << "w err: " << lTemp->sDataErr << endl;
						lTemp = lTemp->sLft;
					}
					break;
				case Orden::sinorden:
					if (lTemp) {
                        for(auto i : lTemp->sDataIP){
                            lFile << i << ", ";
                        }
                        lFile << "w err: " << lTemp->sDataErr << endl;
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



PTNODE Arbol::getNewNode(string sDataIP1, string sDataIP2, string sDataIP3, string sDataIP4, string sDataIP5,
	string sDataIP6, int sDataErr)
{
	PTNODE lTemp = new TNODE;

	if (lTemp) {
		lTemp->sDataIP.push_back(sDataIP1);
		lTemp->sDataIP.push_back(sDataIP2);
		lTemp->sDataIP.push_back(sDataIP3);
		lTemp->sDataIP.push_back(sDataIP4);
		lTemp->sDataIP.push_back(sDataIP5);
		lTemp->sDataIP.push_back(sDataIP6);
		lTemp->sDataErr = sDataErr;
		lTemp->sLft = NULL;
		lTemp->sRgt = NULL;
	}

	return lTemp;
} // getNewNode



