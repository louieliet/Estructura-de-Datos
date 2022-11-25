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
    int sFreq;
	string sMovieTitle;
	PTNODE sLft;
	PTNODE sRgt;
};

enum class Orden { asc, desc, sinorden };

class Arbol{

protected:
	PTNODE aRoot;
    bool aFreq;

public:
	Arbol(void);
	~Arbol(void);

	void clean(PTNODE pSub = NULL);


	void push(string sMovieTitle);

	void runGet(void(*pFunc)(string));

	void reprr(Orden pOrd = Orden::asc, PTNODE pSub = NULL);
	void repr(Orden pOrd = Orden::asc);

	void read(string pPath);
	void write(string pPath, Orden pOrd = Orden::sinorden);

private:

	PTNODE min(PTNODE pSub);
	PTNODE getNewNode(string sMovieTitle);
};

//Cortina

typedef struct VNODE* PVNODE;

struct VNODE {
    string sMain;
    string sExtra;
    PVNODE sPrev;
    PVNODE sNext;
};


class DLVer
{
protected:
    PVNODE aHead;
    PVNODE aTail;
    PVNODE aCurr;

public:
    DLVer(void);
    ~DLVer(void);

    void clean(void);

    void push(string pMain, string pExtra);

    PVNODE get(bool pRev = false);
    PVNODE get(string pMain);
    void resetCurr(void);

    void del(string pMain);

    bool isEmpty(void);
    void repr(bool pRev = false);

private:
    void push_front(string pMain, string pExtra);
    void push_back(string pMain, string pExtra);
    
    void pop_front(void);
    void pop_back(void);

    PVNODE find(string pMain);
    PVNODE search(string pMain);
    PVNODE getNewNode(string pMain, string pExtra);
};

//--
