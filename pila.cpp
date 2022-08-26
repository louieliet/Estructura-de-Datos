#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

void foo(string);

int main()
{
    string valorx[81];
    string valory[81];
    double valorz[81];
    double xo = -10;
    valorx[0] = "-10";

    //Llenando el arreglo de valorx de -10 hasta 10 con intervalos de 0.25
    for(int i=1; i<81; i++)
    {
        xo = xo+0.25;
        valorx[i] = to_string(xo);
    }

    //Llenando el arreglo de valory de 0 a 81
    for(int i=0; i<81; i++)
    {
        valory[i] = to_string(i);
    }

    //Evaluando la función con los valores de los arrays previos y tabulando
    for(int i=0; i<81; i++)
    {
        cout << "x = " << valorx[i] << ", y = " << valory[i] << ", z = ";
        foo("0.5;"+valorx[i]+";*;10;+;sin;"+valory[i]+";0.3;*;5;+;cos;/");
        cout << endl;
    }
      
};

void foo(string cadena)
{

    stack<double> lStack;
    double lV01, lV02, lV03;
    istringstream lExp(cadena);
    string lStr = "";

    while (getline(lExp, lStr, ';')) {
        //cout << lStr << endl;
        if (isdigit(lStr[0])) {
            lStack.push(stod(lStr));
        }
        else 
            if ((lStr.length() > 1) && (lStr[0] == '-')) {
                lStack.push(stod(lStr));
            }
            else
            {
                if (lStr.length() == 1) {
                    lV02 = lStack.top(); lStack.pop();
                    lV01 = lStack.top(); lStack.pop();
                    switch (lStr[0]) {
                        case '+': lV03 = lV01 + lV02; break;
                        case '-': lV03 = lV01 - lV02; break;
                        case '*': lV03 = lV01 * lV02; break;
                        case '/': lV03 = lV01 / lV02; break;
                        case '%': lV03 = (int)lV01 % (int)lV02; break;
                    }
                    lStack.push(lV03);
                }
                else {
                    lV02 = lStack.top(); lStack.pop();
                    if (lStr == "sin")
                        lV03 = sin(lV02);
                    else if (lStr == "cos")
                        lV03 = cos(lV02);
                    else if (lStr == "tan")
                        lV03 = tan(lV02);
                    else if (lStr == "pow") {
                        lV01 = lStack.top(); lStack.pop();
                        lV03 = pow(lV01, lV02);
                    }
                    lStack.push(lV03);
                }
            }
    }

    lV03 = lStack.top();
    cout << lV03 << endl;
}



