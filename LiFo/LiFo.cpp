
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

private:
    void resize(void);
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
            aErr = -4; // Intento de top en vac?a
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
            aErr = -5; // Intento de top en vac?a
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
            aErr = -6; // Intento de get en vac?a
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
    cout << "||";
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
    LiFo<int> lPila = LiFo<int>(4, 2);

    lPila.repr();
    lPila.push(11);    lPila.repr();
    lPila.push(-22);    lPila.repr();
    lPila.push(303);    lPila.repr();
    lPila.push(-44);    lPila.repr();
    lPila.push(55);    lPila.repr();
    lPila.push(-66);    lPila.repr();

    cout << lPila.top() << endl;   lPila.repr();

    /*cout << lPila.top() << endl;   lPila.pop();  lPila.repr();
    cout << lPila.top() << endl;   lPila.pop();  lPila.repr();
    cout << lPila.top() << endl;   lPila.pop();  lPila.repr();
    cout << lPila.top() << endl;   lPila.pop();  lPila.repr();
    cout << lPila.top() << endl;   lPila.pop();  lPila.repr();
    cout << lPila.top() << endl;   lPila.pop();  lPila.repr();*/

    cout << lPila.get(3) << endl;   lPila.repr();
    cout << lPila.get(6) << endl;   lPila.repr();
    cout << lPila.get(-1) << endl;   lPila.repr();
    cout << lPila[0] << endl;   lPila.repr();

}
