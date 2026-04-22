#include<bits/stdc++.h>
using namespace std;

void reverse(int a[], int l, int r) {
    while (l < r) {
        swap(a[l], a[r]);
        l++;
        r--;
    }
}

int main() {

    int n = 5;

    int a[] = {1, 2, 3, 4, 5};

    int k = 33;

    k = k % n;

    reverse(a, n - k, n - 1);
    reverse(a, 0, n - k - 1);
    reverse(a, 0, n - 1);

    for (int i : a) {
        cout << i << " ";
    }
}