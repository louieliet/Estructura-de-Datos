
using namespace std;

#include <iostream>

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
            for(int lIdx = 0; lIdx < aCur; lIdx++)
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
#define K_MAX_Lugares 10
#define K_MAX_Cajas 2
#define K_MAX_Opers 5

int random(int pMin, int pMax)
{
    return (rand() % (pMax - pMin) + pMin);
}


int main()
{
    FiFo<int> lCola = FiFo<int>(K_MAX_Lugares, 0);
    int lCajas[K_MAX_Cajas];
    int lPersonas = 0;
    int lCiclos = 0;
    int lRebotes = 0;
    int lOpers = 0;

    do
    {
        //--Generador de personas
        lOpers = random(1,K_MAX_Opers);
        cout << lOpers  << endl;


    } while (false);
    

}
