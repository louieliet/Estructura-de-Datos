
#include <iostream>
using  namespace std;


void funcion(int* a, int* b)
{
    int c;
    
    c=*a;
    *a=*b;
    *b = c;

    
   
}
void aumentar(int* valor)
{

    (*valor)++;
}

int main()
{
    int a=1,b=2;

    int* ptr = &a;
    int ptrvalue = *ptr;

    int valor = 5;
    
    cout << valor;

    /*cout << a << " " << b << endl;
    funcion(&a,&b);
    cout << a << " " << b << endl;*/
    aumentar(&valor);

    
    cout << valor;

}



/*
Delacacion de un apuntador
 int* ptrA= &a

 DEREFERENCIAR (obtener el valor del apuntador)

 *ptrA
 
 Direccion de memoria
 &a
 
 
 
 */






