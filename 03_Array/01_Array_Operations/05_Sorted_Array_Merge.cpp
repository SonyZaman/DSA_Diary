#include<bits/stdc++.h>
using namespace std;

int main(){
    

    int arr1[]={1, 3, 5, 7, 9};
    int arr2[]={2, 4, 6, 8, 10,12,20};

    int n1=sizeof(arr1)/sizeof(arr1[0]);
    int n2=sizeof(arr2)/sizeof(arr2[0]);
    int i=0,j=0;
    int merged[n1+n2];
    int k=0;
    while(i<n1 && j<n2){
        if(arr1[i]<arr2[j]){
            merged[k++]=arr1[i++];
        }
        else{
            merged[k++]=arr2[j++];
        }
    }
    while(i<n1){
        merged[k++]=arr1[i++];
    }   
    
    while(j<n2){
        merged[k++]=arr2[j++];
    }
    for(auto x:merged) cout<<x<<" ";
    return 0;

}