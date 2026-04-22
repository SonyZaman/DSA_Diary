#include<bits/stdc++.h>
using namespace std;

int main(){


    int n;cin>>n;

    int arr[n+1];

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

   int indx,val;
   cin>>indx>>val;

   for(int i=n;i>=indx;i--){
       arr[i+1]=arr[i];
   }
   arr[indx]=val;

   for(int i=0;i<=n;i++){
       cout<<arr[i]<<" ";
   }

}