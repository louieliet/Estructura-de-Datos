#include "Ej02.h"

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

void Arbol::push(string sMovieTitle)
{
	if (aRoot == NULL) {
		aRoot = getNewNode(sMovieTitle);
	}
	else {
		PTNODE lTemp = aRoot;
		while (lTemp) {
			if (sMovieTitle < lTemp->sMovieTitle) {
				if (lTemp->sLft)
					lTemp = lTemp->sLft;
				else {
					lTemp->sLft = getNewNode(sMovieTitle);
					lTemp = NULL;
				}
			}
			else if (sMovieTitle > lTemp->sMovieTitle) {
				if (lTemp->sRgt)
					lTemp = lTemp->sRgt;
				else {
					lTemp->sRgt = getNewNode(sMovieTitle);
					lTemp = NULL;
				}
			}
			else {
                if(aFreq){
                    (lTemp->sFreq)++;
                    lTemp = NULL;
                }
                else{
                    if (lTemp->sRgt)
                        lTemp = lTemp->sRgt;
                    else {
                        lTemp->sRgt = getNewNode(sMovieTitle);
                        lTemp = NULL;
                    }
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
                    cout << "Movie title: " << lTemp->sMovieTitle << ", w freq ("
                    << lTemp->sFreq << endl;
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
                    cout << "Movie title: " << lTemp->sMovieTitle << ", w freq ("
                    << lTemp->sFreq << endl;
					lTemp = lTemp->sLft;
				}
				break;
			case Orden::sinorden:
				if (lTemp) {
                    cout << "Movie title: " << lTemp->sMovieTitle << ", w freq ("
                    << lTemp->sFreq << endl;
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
	string lLine = "";
	ifstream lFile(pPath);
	vector<string> sElements;

	while (getline(lFile, lLine, '\n')) {
        push(lLine);
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
                        lFile << "Movie title: " << lTemp->sMovieTitle << ", w freq ("
                        << lTemp->sFreq << endl;
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
                        lFile << "Movie title: " << lTemp->sMovieTitle << ", w freq ("
                        << lTemp->sFreq << endl;
						lTemp = lTemp->sLft;
					}
					break;
				case Orden::sinorden:
					if (lTemp) {
                        lFile << "Movie title: " << lTemp->sMovieTitle << ", w freq ("
                        << lTemp->sFreq << endl;
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



PTNODE Arbol::getNewNode(string sMovieTitle)
{
	PTNODE lTemp = new TNODE;

	if (lTemp) {
		lTemp->sMovieTitle = sMovieTitle;
        lTemp->sFreq = 1;
		lTemp->sLft = NULL;
		lTemp->sRgt = NULL;
	}

	return lTemp;
} // getNewNode

