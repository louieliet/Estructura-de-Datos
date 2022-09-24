using namespace std;

#include <iostream>

template <class T>
class LiFo {
protected:
    T* aData;
    int aMax;
    int aCur;
    int aErr;
    int aStep;

public:
    LiFo(int pMax, int pStep = 0);
    ~LiFo(void);

    void push(T pVal);
    T top(void);
    void pop(void);
    bool isEmpty(void);
    bool isFull(void);

    int error(void);
    T get(int pIdx);
    T operator [](int pIdx);
    void repr(void);
    int getaMax(void);
    int getIdxMin(void);
    double getMemory(void);
    int getpCount(void);

private:
    void resize(void);
    int pCount = 0;
};


template<class T>
int LiFo<T>::getpCount(void){
    return pCount;
}
template<class T>
int LiFo<T>::getaMax(void){
    return aMax;
}

template<class T>
int LiFo<T>::getIdxMin(void){

    T menor = aData[0];
    int Idx;

    for(int i = 0; i < pCount; i++)
    {
        if(aData[i] < menor){
            menor = aData[i];
        }
    }
    for(int i = 0; i < pCount; i++)
    {
        if(menor == aData[i]){
            Idx = i;
            break;
        }
    }
    return Idx;
}

template <class T>
double LiFo<T>::getMemory(void)
{

    double porcentaje = 0;

    double memorytotal = sizeof(T) * aMax;
    double usedmemory = sizeof(T) * aCur;

    porcentaje = (usedmemory*100)/memorytotal;

    return porcentaje;
};


template <class T>
LiFo<T>::LiFo(int pMax, int pStep)
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
LiFo<T>::~LiFo(void)
{
    aErr = 0;
    aMax = 0;
    aCur = 0;

    if (aData)
        delete[] aData;
}  // Destructor

template <class T>
void LiFo<T>::push(T pVal)
{
    aErr = 0;

    if (aData) {
        if (!isFull()) {

            aData[aCur] = pVal;
            aCur++;
            pCount++;

            /*if(pVal % 2 != 0){
                pCount++;
            }*/

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
T LiFo<T>::top(void)
{
    aErr = 0;

    if (aData) {
        if (!isEmpty()) {
            return aData[aCur - 1];
        }
        else {
            aErr = -4; // Intento de top en vac�a
        }
    }
    return (T)0;
} // top

template <class T>
void LiFo<T>::pop(void)
{
    aErr = 0;

    if (aData) {
        if (!isEmpty()) {
            aCur--;
        }
        else {
            aErr = -5; // Intento de top en vac�a
        }
    }
} // pop

template <class T>
bool LiFo<T>::isEmpty(void)
{
    return (aCur == 0);
} // isEmpty

template <class T>
bool LiFo<T>::isFull(void)
{
    return (aCur == aMax);
} // isFull

template <class T>
int LiFo<T>::error(void)
{
    return aErr;
} // error

template <class T>
T LiFo<T>::get(int pIdx)
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
T LiFo<T>::operator [](int pIdx)
{
    return get(pIdx);
} // operator []

template <class T>
void LiFo<T>::repr(void)
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
    cout << "|| Pila: ";
    for (int lIdx = 0; lIdx < aCur; lIdx++) {
        cout << aData[lIdx];
        cout << ", ";
    }
    cout << endl;
} // repr

template <class T>
void LiFo<T>::resize(void)
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



int main()
{
    LiFo<double> Pila(250,0);

    cout << Pila.getMemory() << endl;

    for(int i = 0; i < Pila.getaMax(); i++)
    {
        
        if(Pila.getMemory() < 75)
        {
            double random = rand() % (75-25) + 25;
            random = random/100;
            Pila.push(random);
        }
    }
    Pila.repr();
    cout << endl;
    cout << "El valor mas pequenio se encuentra en el indice: " << Pila.getIdxMin() << endl;
    cout << "Memoria usada:" << Pila.getMemory() << endl;

    for(int i = 0; i < Pila.getaMax(); i++)
    {
        if(Pila.getMemory() > 25)
        {
            Pila.pop();
        }
        else if (Pila.getMemory() <= 25)
        {
            break;
        }
        
    }
    
    Pila.repr();
    cout << "Memoria usada:" << Pila.getMemory() << endl;

}