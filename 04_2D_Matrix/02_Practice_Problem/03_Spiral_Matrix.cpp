#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row_start=0,row_last=matrix.size()-1,col_start=0,col_last=matrix[0].size()-1;
        vector<int>ans;

        while(row_start<=row_last && col_start<=col_last){

            for(int i=col_start;i<=col_last;i++){
                ans.push_back(matrix[row_start][i]);
            }
            row_start++;

            for(int i=row_start;i<=row_last;i++){
                ans.push_back(matrix[i][col_last]);
            }
            col_last--;

            if(row_start<=row_last){
                for(int i=col_last;i>=col_start;i--){
                    ans.push_back(matrix[row_last][i]);
                }
                row_last--;
            }

            if(col_start<=col_last){
                for(int i=row_last;i>=row_start;i--){
                    ans.push_back(matrix[i][col_start]);
                }
                col_start++;
            }

        }

        return ans;
    }
};