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
	vector<string> sDataIP;
	int sDataErr;
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


	void push(string sDataIP1, string sDataIP2, string sDataIP3, string sDataIP4, string sDataIP5,
		string sDataIP6, int sDataErr);

	void pushn(string sDataIP1, string sDataIP2, string sDataIP3, string sDataIP4, string sDataIP5,
		string sDataIP6, int sDataErr);


	void runGet(void(*pFunc)(string));

	void reprr(Orden pOrd = Orden::asc, PTNODE pSub = NULL);
	void repr(Orden pOrd = Orden::asc);

	void read(string pPath, bool name);
	void write(string pPath, Orden pOrd = Orden::sinorden);

private:

	PTNODE min(PTNODE pSub);
	PTNODE getNewNode(string sDataIP1, string sDataIP2, string sDataIP3, string sDataIP4, string sDataIP5,
		string sDataIP6, int sDataErr);
};