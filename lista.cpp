#include <iostream>
#include <string>

using namespace std;

typedef struct DNODE* PDNODE;

typedef struct DNODE{

    string sNombre;
    int sFrec;
    PDNODE sNext;
    PDNODE sPrev;


};
