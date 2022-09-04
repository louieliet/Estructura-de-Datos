using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
class FiFo {
protected:
    T* aData;
    int aMax;
    int aCur;
    int aErr;
    int aStep;

public:
    FiFo(int pMax, int pStep = 0);
    ~FiFo(void);

    void push(T pVal);
    T top(void);
    void pop(void);
    bool isEmpty(void);
    bool isFull(void);

    int error(void);
    T get(int pIdx);
    T operator [](int pIdx);
    void repr(void);

private:
    void resize(void);
};

template <class T>
FiFo<T>::FiFo(int pMax, int pStep)
{
    aCur = 0;
    aErr = 0;
    aData = NULL;
    aStep = pStep;
    aMax = 0;

    if (pMax > 0) {
        aMax = pMax;
        aData = new T[aMax];
        if (aData == NULL)
            aErr = -2; // No hay memoria
    }
    else
        aErr = -1; // Max fuera de rango
} // Constructor

template <class T>
FiFo<T>::~FiFo(void)
{
    aErr = 0;
    aMax = 0;
    aCur = 0;

    if (aData)
        delete[] aData;
}  // Destructor

template <class T>
void FiFo<T>::push(T pVal)
{
    aErr = 0;

    if (aData) {
        if (!isFull()) {
            aData[aCur] = pVal;
            aCur++;
        }
        else {
            if (aStep != 0) {
                resize();
                if (aErr == 0) {
                    aData[aCur] = pVal;
                    aCur++;
                }
            } else
                aErr = -3; // Intento de push en llena
        }
    }
} // push

template <class T>
T FiFo<T>::top(void)
{
    aErr = 0;

    if (aData) {
        if (!isEmpty()) {
            return aData[0];
        }
        else {
            aErr = -4; // Intento de top en vac�a
        }
    }
    return (T)0;
} // top

template <class T>
void FiFo<T>::pop(void)
{
    aErr = 0;

    if (aData) {
        if (!isEmpty()) {
            for(int lIdx = 0; lIdx < aMax - 1; lIdx++)
            {
                aData[lIdx] = aData[lIdx+1];
            }
            aCur--;
        }
        else {
            aErr = -5; // Intento de top en vac�a
        }
    }
} // pop

template <class T>
bool FiFo<T>::isEmpty(void)
{
    return (aCur == 0);
} // isEmpty

template <class T>
bool FiFo<T>::isFull(void)
{
    return (aCur == aMax);
} // isFull

template <class T>
int FiFo<T>::error(void)
{
    return aErr;
} // error

template <class T>
T FiFo<T>::get(int pIdx)
{
    aErr = 0;

    if (aData) {
        if (!isEmpty()) {
            if ((0 <= pIdx) && (pIdx < aCur)) {
                return aData[pIdx];
            }
            else {
                aErr = -7; // Intento de get fuera de rango
            }
        }
        else {
            aErr = -6; // Intento de get en vac�a
        }
    }
    return (T)0;
} // get

template <class T>
T FiFo<T>::operator [](int pIdx)
{
    return get(pIdx);
} // operator []

template <class T>
void FiFo<T>::repr(void)
{
    cout << (isEmpty() == true ? "1" : "0");
    cout << "|";
    cout << (isFull() == true ? "1" : "0");
    cout << "|";
    cout << aMax;
    cout << "|";
    cout << aCur;
    cout << "|";
    cout << aErr;
    cout << "||";
    for (int lIdx = 0; lIdx < aCur; lIdx++) {
        cout << aData[lIdx];
        cout << ", ";
    }
    cout << endl;
} // repr

template <class T>
void FiFo<T>::resize(void)
{
    int lMax = 0;
    T* lData = NULL;

    aErr = 0;

    if (aData) {
        if (aStep > 0) {
            lMax = aMax + aStep;
            lData = new T[lMax];
            if (lData) {
                for (int lIdx = 0; lIdx < aMax; lIdx++)
                    lData[lIdx] = aData[lIdx];
                delete[] aData;
                aData = lData;
                aMax = lMax;
            }
            else
                aErr = -9; // No memoria para resize
        }
        else
            aErr = -8; // Intento de resize fuera de rango
    }
} // resize


#define K_MAX_Personas 1000
#define K_MAX_Lugares 20
#define K_MAX_Cajas 4
#define K_MAX_Opers 6


int random(int pMin, int pMax, vector<int> v)
{
    return (v[rand() % (pMax - pMin) + pMin]);
}


vector<int> fillDistribution(vector<int> v)
{
    
    vector<int> vtf = v;

    for(int x = 0; x < 3; x++)
    {
        vtf.push_back(1);
    }
    for(int x = 0; x < 7; x++)
    {
        vtf.push_back(2);
    }
    for(int x = 0; x < 10; x++)
    {
        vtf.push_back(3);
    }
    for(int x = 0; x < 7; x++)
    {
        vtf.push_back(4);
    }
    
    for(int x = 0; x < 4; x++)
    {
        vtf.push_back(5);
    }
        
    vtf.push_back(6);

    random_shuffle(vtf.begin(),vtf.end());

    return vtf;

}

int main()
{
    FiFo<int> lCola = FiFo<int>(K_MAX_Lugares, 0);
    int lCaja[K_MAX_Cajas];
    int lPersonas = 0;
    int lCiclos = 0;
    int lRebotes = 0;
    int lOpers = 0;
    bool lSalida = false;
    int lCajaVacia = 0;

    vector<int> distribution;
    distribution = fillDistribution(distribution);

    for(int x = 0; x < K_MAX_Cajas; x++)
    {
        lCaja[x] = 0;
    }

    do
    {
        //--Generador de personas
        if(lPersonas < K_MAX_Personas)
        {
            lPersonas++;
            lOpers = random(1,K_MAX_Opers,distribution);
            //lOpers = 1;
            cout << "#Opers: " << lOpers  << ", #Pers: " << lPersonas << endl;
            //--Ingresar en la cola
            if (!lCola.isFull())
            {
                lCola.push(lOpers);
            } else { 
                lRebotes++;
            }
        }

        //--Pedir gente y hacer operaciones
        lCola.repr();
        lCajaVacia = 0;


        if(lOpers == 1)
        {
            cout << "Caja #0 : " << lCaja[0] << endl;
            if(lCaja[0] != 0){
                lCaja[0]--;
            }
            else{
                if(!lCola.isEmpty()){
                    lCaja[0] = lCola.top();
                    lCola.pop();
                } 
                else{ lCajaVacia = K_MAX_Cajas;}
            }
            cout << "," << lCaja[0] << endl;

        }
        else{

            for(int x = 0; x < K_MAX_Cajas; x++)
            {   
    
                cout << "Caja #" << x << ": " << lCaja[x] << endl;
                if(lCaja[x] != 0){
                    lCaja[x]--;
                }
                else{
                    if(!lCola.isEmpty()){
                        lCaja[x] = lCola.top();
                        lCola.pop();
                    } 
                    else{ lCajaVacia++;}
                }
                cout << "," << lCaja[x] << endl;
               
            }

        }

        lCola.repr();

        //--Determinar el fin de la simulación
        lSalida = 
            (lPersonas == K_MAX_Personas) &&
            (lCola.isEmpty()) &&
            (lCajaVacia == K_MAX_Cajas);
        //1. No más personas, 2. Que no haya personas en la cola, 3. No personas en caja

        lCiclos++;
        cout << "------" << lCiclos << "-----" << endl;

    } while (!lSalida);

    cout << "Max Personas: " << K_MAX_Personas << endl;
    cout << "Max Lugares: " << K_MAX_Lugares << endl;
    cout << "Max Cajas: " << K_MAX_Cajas << endl;
    cout << "Max Opers: " << K_MAX_Opers << endl;
    cout << "Ciclos: " << lCiclos << endl;
    cout << "Rebotes: " << lRebotes << endl;
}


/*
Max Personas: 1000
Max Lugares: 10
Max Cajas: 2
Max Opers: 5
Ciclos: 1017
Rebotes: 408

Max Personas: 1000
Max Lugares: 10
Max Cajas: 3
Max Opers: 5
Ciclos: 1011
Rebotes: 120

Max Personas: 1000
Max Lugares: 20
Max Cajas: 4
Max Opers: 5
Ciclos: 1003
Rebotes: 0


*/