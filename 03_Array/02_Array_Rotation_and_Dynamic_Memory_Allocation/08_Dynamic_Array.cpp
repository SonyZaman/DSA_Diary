#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 5;

    int *arr = new int[n];  // dynamic array

    for(int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }

    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    delete[] arr;  // free array memory

    return 0;
}