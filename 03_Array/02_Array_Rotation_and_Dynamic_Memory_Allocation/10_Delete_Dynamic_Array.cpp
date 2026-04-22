#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 5;

    int *arr = new int[n];

    for(int i = 0; i < n; i++)
        arr[i] = i + 1;

    delete[] arr;   // deleting the dynamic array

    return 0;
}