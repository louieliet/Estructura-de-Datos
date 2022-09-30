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

class DList {
protected:
    PDNODE aHead; 
    PDNODE aTail; 
    PDNODE aCurr;
    bool aFreq;
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