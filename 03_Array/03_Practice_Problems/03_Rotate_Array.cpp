#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void rotateArray(vector<int>& arr, int k) {
        
        k = k % arr.size(); // Handle cases where k is greater than array size
        vector<int>temp;
        for(int i=arr.size()-k;i<arr.size();i++){
            temp.push_back(arr[i]);
        }
        for(int i=0;i<arr.size()-k;i++){
            temp.push_back(arr[i]);
        }
        arr = temp;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {1, 2, 3, 4, 5};
    int k = 2;
    sol.rotateArray(arr, k);
    for (int i : arr) {
        cout << i << " ";
    }
    return 0;
}
