# Matrix Practice Problems

This directory contains advanced matrix manipulation problems from Online Judges like LeetCode.

---

## Table of Contents
1. [Rotate Image](#1-rotate-image)
2. [Flipping an Image](#2-flipping-an-image)
3. [Spiral Matrix](#3-spiral-matrix)

---

## 1. Rotate Image

### Problem Title
Rotate a Matrix by 90 Degrees.
**Problem Link:** [LeetCode 48 - Rotate Image](https://leetcode.com/problems/rotate-image/)

### Problem Statement
Given an $n \times n$ 2D matrix, rotate it 90 degrees clockwise in-place.

### Approach
- **Extra Space:** For each cell $(i, j)$, its new position is $(j, n-1-i)$. Store in a temporary matrix and copy back.
- **In-Place (Better):** Transpose the matrix (swap `(i, j)` with `(j, i)`) and then reverse each row.

### Code
```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        vector<vector<int>> temp(matrix.size(), vector<int>(matrix[0].size()));
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size(); j++){
                temp[j][matrix.size()-1-i] = matrix[i][j];
            }
        }
        matrix = temp;
    }
};
```

### Complexity
- **Time Complexity:** $O(n^2)$.
- **Space Complexity:** $O(n^2)$ (as implemented above).

---

## 2. Flipping an Image

### Problem Title
Horizontal Flip and Inversion.
**Problem Link:** [LeetCode 832 - Flipping an Image](https://leetcode.com/problems/flipping-an-image/)

### Problem Statement
Given an $n \times n$ binary matrix, first flip it horizontally, then invert it (change 0s to 1s and vice versa).

### Approach
1. **Flip:** For each row, swap elements from both ends.
2. **Invert:** Iterate through all bits and toggle them.

### Code
```cpp
class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
       for(int i = 0; i < image.size(); i++){
           for(int j = 0; j < image[i].size() / 2; j++){
               swap(image[i][j], image[i][image[i].size() - 1 - j]);
           }
       }

       for(int i = 0; i < image.size(); i++){
           for(int j = 0; j < image[i].size(); j++){
               image[i][j] = image[i][j] == 0 ? 1 : 0;
           }
       }
       return image;
    }
};
```

### Complexity
- **Time Complexity:** $O(n \times m)$.
- **Space Complexity:** $O(1)$ (in-place modification).

---

## 3. Spiral Matrix

### Problem Title
Spiral Order Traversal.
**Problem Link:** [LeetCode 54 - Spiral Matrix](https://leetcode.com/problems/spiral-matrix/)

### Problem Statement
Given an $m \times n$ matrix, return all elements of the matrix in spiral order (right, down, left, up).

### Approach
1. Maintain four boundaries: `row_start`, `row_last`, `col_start`, `col_last`.
2. Loop until boundaries cross.
3. Traverse right, increment `row_start`.
4. Traverse down, decrement `col_last`.
5. Traverse left (if row remains), decrement `row_last`.
6. Traverse up (if column remains), increment `col_start`.

### Code
```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int row_start = 0, row_last = matrix.size()-1;
        int col_start = 0, col_last = matrix[0].size()-1;
        vector<int> ans;

        while(row_start <= row_last && col_start <= col_last){
            for(int i = col_start; i <= col_last; i++) ans.push_back(matrix[row_start][i]);
            row_start++;

            for(int i = row_start; i <= row_last; i++) ans.push_back(matrix[i][col_last]);
            col_last--;

            if(row_start <= row_last){
                for(int i = col_last; i >= col_start; i--) ans.push_back(matrix[row_last][i]);
                row_last--;
            }

            if(col_start <= col_last){
                for(int i = row_last; i >= row_start; i--) ans.push_back(matrix[i][col_start]);
                col_start++;
            }
        }
        return ans;
    }
};
```

### Complexity
- **Time Complexity:** $O(n \times m)$.
- **Space Complexity:** $O(1)$ (excluding output storage).
