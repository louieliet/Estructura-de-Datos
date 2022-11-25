#include <iostream>

using namespace std;

int main(){

    string phrase = "Me gusta Lizbeth";
    int spacecount = 0;
  
    for(int i = 0; i < phrase.length(); i++){
        cout << phrase[i] << endl;
        /*if(isspace(phrase[i])){
            spacecount++;
        }*/
        if(phrase[i] == ' '){
            spacecount++;
        }
    }

    cout << phrase.length() - spacecount<< endl;

}