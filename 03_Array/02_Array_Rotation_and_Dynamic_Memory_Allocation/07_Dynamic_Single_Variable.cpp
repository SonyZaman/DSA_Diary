#include <bits/stdc++.h>
using namespace std;

int main()
{
    int *p = new int;   // allocate memory for one integer
    //Return address
    *p = 10;

    cout << "Value: " << *p << endl;

    delete p;  // free memory

    return 0;
}