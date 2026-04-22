#include<bits/stdc++.h>
using namespace std;

int main(){


    int arr[]={30, 21, 45, 22, 73,45};

    int n=sizeof(arr)/sizeof(arr[0]);
    int first=-1,second=-1;

    for(int i=0;i<n;i++){
        if(arr[i]>first){
            second=first;
            first=arr[i];
        }
        else if(arr[i]>second && arr[i]!=first){
            second=arr[i];
        }
    }
    cout<<"Second largest element is: "<<second<<endl;
}