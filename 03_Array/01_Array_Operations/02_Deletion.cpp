#include<bits/stdc++.h>
using namespace std;

int main(){

    int n;cin>>n;

    int arr[n];

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

   int indx;
   cin>>indx;

   for(int i=indx;i<n-1;i++){
       arr[i]=arr[i+1];
   }
   arr[n-1]=-1;

   for(int i=0;i<n-1;i++){
       cout<<arr[i]<<" ";
   }
}