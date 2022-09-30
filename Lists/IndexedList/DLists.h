
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
    void push_front(string pNombre, bool pDoFind = true);
    void push_back(string pNombre, bool pDoFind = true);
    void push(string pNombre);

    PDNODE top_front(void);
    PDNODE top_back(void);
    PDNODE get(bool pRev = false);

    void pop_front(void);
    void pop_back(void);
    // void repr(void);

    bool isEmpty(void);
    void repr(bool pRev = false);

    void del(string pNombre, bool pForce);

    void read(string pPath, char pMethod = 'b');
    void write(string pPath, bool pRev = false);

private:
    PDNODE getNewNode(string pNombre);
    PDNODE search(string pNombre);
    PDNODE find(string pNombre);
};