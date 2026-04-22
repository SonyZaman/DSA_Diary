#include<bits/stdc++.h>
using namespace std;

int main(){

    vector<vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<int>> matrix2 = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };

    vector<vector<int>> matrix(matrix1.size(), vector<int>(matrix1[0].size()));

    for (int i = 0; i < matrix1.size(); i++) {
        for (int j = 0; j < matrix1[i].size(); j++) {
            matrix[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
                cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}