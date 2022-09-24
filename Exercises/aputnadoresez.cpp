#include <iostream>

using namespace std;

void invertir(int* x, int* y)
{
    int aux;
    aux = *x;
    *x = *y;
    *y = aux;

}


int main()
{
    int a = 1, b = 2;

    cout << "a= " << a << "b= " << b << endl;

    invertir(&a, &b);
    
    cout << "a= " << a << "b= " << b << endl;
  
}