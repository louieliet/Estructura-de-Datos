#include "Arbol.cpp"


int main() {

    Arbol lArb = Arbol();
    
    string strArr;
    string tokens;

    string* strvectror;

    cout << "Ingresa un texto con puntos: " << endl;
    getline(cin, strArr);

    stringstream teststream(strArr);

    while (getline(teststream, tokens, ';')) {
        cout << tokens << endl;
    }

}

