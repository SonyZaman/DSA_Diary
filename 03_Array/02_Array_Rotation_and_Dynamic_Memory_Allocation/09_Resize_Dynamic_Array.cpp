#include <bits/stdc++.h>
using namespace std;

int main()
{
    int oldSize = 5;

    int *oldArr = new int[oldSize];

    for(int i = 0; i < oldSize; i++)
        oldArr[i] = i;

    int newSize = 8;

    int *newArr = new int[newSize];

    for(int i = 0; i < oldSize; i++)
        newArr[i] = oldArr[i];

    for(int i = oldSize; i < newSize; i++)
        newArr[i] = i;

    delete[] oldArr;

    for(int i = 0; i < newSize; i++)
        cout << newArr[i] << " ";

    delete[] newArr;

    return 0;
}