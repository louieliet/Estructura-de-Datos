
using namespace std;
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

vector<int> fillDistribution(vector<int> v)
{
    
    vector<int> vtf = v;

    for(int x = 0; x < 3; x++)
    {
        vtf.push_back(1);
    }
    for(int x = 0; x < 7; x++)
    {
        vtf.push_back(2);
    }
    for(int x = 0; x < 10; x++)
    {
        vtf.push_back(3);
    }
    for(int x = 0; x < 7; x++)
    {
        vtf.push_back(4);
    }
    
    for(int x = 0; x < 4; x++)
    {
        vtf.push_back(5);
    }
        
    vtf.push_back(6);

    random_shuffle(vtf.begin(),vtf.end());
    

    return vtf;

}

int main()
{
    vector<int> distribution;

    distribution = fillDistribution(distribution);

    for(auto i : distribution)
    {
        cout << i;
    }

    cout << endl;

    for(auto i : distribution)
    {
        cout << i;
    }

    cout << endl; 
    int lOper[32];

    for(auto x : distribution)
    {
        lOper[x] = distribution[rand() % (32 - 1) + 1];
        cout << lOper[x];
        distribution.pop_back();

    }


}


