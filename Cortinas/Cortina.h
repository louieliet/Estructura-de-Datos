#pragma once

#include <iostream>
using namespace std;

typedef struct DNODE* PDNODE;
typedef struct DATA* PDATA;

struct DATA{
    string title;
    string date;
};

struct DNODE{
    PDATA data;
    PDNODE sPrev;
    PDNODE sNext;
};

class DList{
protected:
    
}

