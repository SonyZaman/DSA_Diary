#include<bits/stdc++.h> 
using namespace std;


class Solution{
public:
    int kthLargest(vector<int>& arr, int k) {
        vector<int> cnt(20001,0);

        for(int i=0;i<arr.size();i++){
            cnt[arr[i]+10000]++;
        }

        for(int i=20000;i>=0;i--){

            k-=cnt[i];  

            if(k<=0) return i-10000;
        }

        return -1;
    }


   
};


 int main(){
    Solution sol;
    vector<int> arr = {30, 21, 45, 22, 73, 45};
    int k = 1;
    cout << "Kth largest element is: " << sol.kthLargest(arr, k) << endl;
    return 0;
}

