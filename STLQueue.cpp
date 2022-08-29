#include <iostream>
#include <queue>
using namespace std;

int main()
{
    queue<double> lQueue;

    lQueue.push(100);
    lQueue.push(200);
    lQueue.push(300);

    cout << lQueue.front() << endl; lQueue.pop();
    cout << lQueue.front() << endl; lQueue.pop();
    cout << lQueue.front() << endl; lQueue.pop();
    
}