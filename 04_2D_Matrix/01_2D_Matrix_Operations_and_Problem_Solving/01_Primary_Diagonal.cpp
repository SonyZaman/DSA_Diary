#include<bits/stdc++.h>
using namespace std;

int main(){

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    // Print primary diagonal

    // for(int i=0;i<matrix.size();i++){
    //     for(int j=0;j<matrix[i].size();j++){
    //         if(i==j){
    //             cout<<matrix[i][j]<<" ";
    //         }
    //     }   
    // }   
    for (int i = 0; i < matrix.size(); i++) {
        cout << matrix[i][i] << " ";
    }
    cout << endl;

    return 0;
}