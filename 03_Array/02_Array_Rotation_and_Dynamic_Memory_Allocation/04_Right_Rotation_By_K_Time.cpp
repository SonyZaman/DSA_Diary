#include<bits/stdc++.h>
using namespace std;

int main(){

   int n=5;

   int a[]={1,2,3,4,5};

   int k=33;

   int temp[n];

   for(int i=0;i<n;i++){

       k=k%n;
       int idx=(i+k)%n;
       temp[i]=a[idx];
   }

   for(int i:temp){
    cout<<i<<" ";
   }
}