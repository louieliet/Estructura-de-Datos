#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;

typedef struct DNODE* PDNODE;


struct DNODE {
    string* sData;
    PDNODE sPrev;
    PDNODE sNext;
};


class DLIndex
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;


public:
    DLIndex();
    ~DLIndex(void);

    void clean(void);

    void push_front(PDATA pData);
    void push_back(PDATA pData);
    void push(PDATA pData);

    PDNODE top_front(void);
    PDNODE top_back(void);
    PDATA get(bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    void del(PDATA pData);

    bool isEmpty(void);
    void repr(bool pRev = false);
    //void read(string pPath, char pMethod = 'b');
    //void write(string pPath, bool pRev = false);

private:
    int comp(PDATA pA, PDATA pB);
    PDNODE find(PDATA pData);
    PDNODE search(PDATA pData);
    PDNODE getNewNode(PDATA pData);
}; //DLIndex

class DList
{
protected:
    PDNODE aHead;
    PDNODE aTail;
    PDNODE aCurr;
    bool aFrec;

    DLIndex* aINom;
    DLIndex* aIApe;
    DLIndex* aIFNa;
    DLIndex* aISal;

public:
    DList(bool pFrec = false);
    ~DList(void);

    void clean(void);

    //void push_front(string pNombre);
    void push_back(string pNombre, string pApellido, 
        string pFNac, double pSalario);
    //void push(string pNombre);

    //PDNODE top_front(void);
    //PDNODE top_back(void);
    PDATA get(ECampos pCampo, bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    void del(string pNombre);

    bool isEmpty(void);
    void repr(ECampos pCampo, bool pRev = false);
    //void read(string pPath, char pMethod = 'b');
    //void write(string pPath, bool pRev = false);

private:
    PDNODE find(string pNombre);
    //PDNODE search(string pNombre);
    PDNODE getNewNode(string pNombre, string pApellido,
        string pFNac, double pSalario);
}; // DList

//#endif
