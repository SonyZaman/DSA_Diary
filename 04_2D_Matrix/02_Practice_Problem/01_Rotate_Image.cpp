#include<bits/stdc++.h>
using namespace std;


class Solution{
    public:
        void rotate(vector<vector<int>>&matrix){

            vector<vector<int>> temp(matrix.size(), vector<int>(matrix[0].size()));
            for(int i=0;i<matrix.size();i++){
                for(int j=0;j<matrix[0].size();j++){
                    temp[j][matrix.size()-1-i] = matrix[i][j];
                }
            }
            matrix = temp;

            for(int i=0;i<matrix.size();i++){
                for(int j=0;j<matrix[0].size();j++){
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};

int main(){
    Solution sol;
    vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    sol.rotate(matrix);
    return 0;
}
