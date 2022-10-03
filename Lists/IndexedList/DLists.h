#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
typedef struct DNODE* PDNODE; 
typedef struct DATA* PDATA;

struct DATA {
    string sNombre;
    string sApellido;
    string sFNac;
    double sSalario;
};

struct DNODE {
    PDATA sData;
    int sFrec;  
    PDNODE sNext; 
    PDNODE sPrev; 
};

enum ECampos{nombre,apellido,fnac,salario};


class DLIndex {
protected:
    PDNODE aHead; 
    PDNODE aTail; 
    PDNODE aCurr;
    bool aFreq;
    ECampos aType;
public:
    DLIndex(ECampos pType, bool freq = false);
    ~DLIndex(void);

    void clean(void);

    void push_front(PDATA pData);
    
    void push_back(PDATA pData);
    
    void push(PDATA pData);
    
    PDATA get(bool pRev = false);

    bool isEmpty(void);

    void repr(bool pRev = false);

    PDNODE search(PDATA pData);

private:
    int comp(PDATA pA, PDATA pB);
    PDNODE getNewNode(PDATA pData);

};


class DList {
protected:
    PDNODE aHead; 
    PDNODE aTail; 
    PDNODE aCurr;
    bool aFreq;

    DLIndex *aINom;
    DLIndex *aIApe;
    DLIndex *aIFNa;
    DLIndex *aISal;

public:
    DList(bool freq = false);
    ~DList(void);

    void clean(void);

    void push_back(string pNombre, string pApellido, 
            string pFNac, double pSalario);

    PDATA get(ECampos pCampo, bool pRev = false);

    bool isEmpty(void);

    void repr(ECampos pCampo, bool pRev = false);

private:
    PDNODE getNewNode(string pNombre, string pApellido, 
            string pFNac, double pSalario);

};