#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <sstream>

using namespace std;

typedef struct VNODE* PVNODE;

struct VNODE {
    string sPlatillo;
    string sVotos;
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

    void push(string pMain, string sFreq);

    PVNODE get(bool pRev = false);
    PVNODE get(string pMain);
    void resetCurr(void);

    void del(string pMain);

    bool isEmpty(void);
    void repr(bool pRev = false);
    void max();
    void min();

private:
    void push_front(string pMain, string sVotos);
    void push_back(string pMain, string sVotos);
    
    void pop_front(void);
    void pop_back(void);

    PVNODE find(string pMain);
    PVNODE search(string pMain);
    PVNODE getNewNode(string pMain, string sVotos);
};

//--

typedef struct HNODE* PHNODE;

struct HNODE {
    string sCat;
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
    void max();
    void min();

private:
    void push_front(string pCat, string pMain, string pVotos);
    void push_back(string pCat, string pMain, string pVotos);

    void pop_front(void);
    void pop_back(void);

	PHNODE find(string pCat);
    PHNODE search(string pCat);
    PHNODE getNewNode(string pCat);
};
