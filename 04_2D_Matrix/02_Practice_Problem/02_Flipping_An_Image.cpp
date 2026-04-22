#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
       for(int i=0;i<image.size();i++){
           for(int j=0;j<image[i].size()/2;j++){
               swap(image[i][j],image[i][image[i].size()-1-j]);
           }
       }

       for(int i=0;i<image.size();i++){
           for(int j=0;j<image[i].size();j++){
               image[i][j] = image[i][j] == 0 ? 1 : 0;
           }
       }
       return image;
    }
};

int main(){
    Solution sol;
    vector<vector<int>> image = {{1, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    vector<vector<int>> result = sol.flipAndInvertImage(image);
    for(const auto& row : result){
        for(int pixel : row){
            cout << pixel << " ";
        }
        cout << endl;
    }
    return 0;
}