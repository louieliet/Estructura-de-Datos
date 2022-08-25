#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int calculator(string cadena);


int main()
{

    calculator("11;2;pow");

};


int calculator(string cadena)
{

    stack<double> lStack;
    double lV01, lV02, lV03;
    istringstream lExp(cadena);
    string lStr = "";

    while (getline(lExp, lStr, ';')) {
        cout << lStr << endl;
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
    cout << "Res = " << lV03 << endl;

    return 0;
}

