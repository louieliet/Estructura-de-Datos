#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>
#include "CPUID.h"

using namespace std;

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

typedef struct HNODE* PHNODE;

struct HNODE {
    string sPath;
    int sIdt;
    DLVer* sVer;
    PHNODE sPrev;
    PHNODE sNext;
};

class DLHor
{
protected:
    PHNODE aHead;
    PHNODE aTail;
    PHNODE aCurr;

public:
    DLHor(void);
    ~DLHor(void);

    void clean(void);

    void push(string pCat, string pMain, string pExtra);

    void get(PHNODE *pHor, PVNODE *pVer, bool pRev = false);
    void get(PHNODE* pHor, PVNODE* pVer, string pCat, string pMain);

    void del(string pCat);
    void del(string pCat, string pMain);

    bool isEmpty(void);
    void repr(bool pRev = false);
    void read(string pPath);
    void write(string pPath, bool pRev = false);

private:
    void push_front(string pCat, string pMain, string pExtra);
    void push_back(string pCat, string pMain, string pExtra);

    void pop_front(void);
    void pop_back(void);

	PHNODE find(string pCat);
    PHNODE search(string pCat);
    PHNODE getNewNode(string pCat);
};
