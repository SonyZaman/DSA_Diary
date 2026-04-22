#include<bits/stdc++.h>
using namespace std;

int main(){

    int arr[]={1, 2, 3, 4, 5};
    int n=sizeof(arr)/sizeof(arr[0]);
    bool isSorted=true;
    for(int i=1;i<n;i++){
        if(arr[i]<arr[i-1]){
            isSorted=false;
            break;
        }
    }
    if(isSorted){
        cout<<"Array is sorted";
    }
    else{
        cout<<"Array is not sorted";
    }
    return 0;
}