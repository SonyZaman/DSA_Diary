#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotate(vector<int>& arr, int k) {
        k = k % arr.size();  // Handle cases where k is greater than array size
        reverse(arr.begin(), arr.end());
        reverse(arr.begin(), arr.begin() + k);
        reverse(arr.begin() + k, arr.end());
    }
};


int main(){
    Solution sol;
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 2;
    sol.rotate(arr, k);
    for (int i : arr) {
        cout << i << " ";
    }
    return 0;
}
