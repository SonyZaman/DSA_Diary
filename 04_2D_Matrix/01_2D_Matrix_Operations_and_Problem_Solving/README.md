# 2D Matrix Operations and Problem Solving

A 2D matrix is a collection of data arranged in rows and columns. In C++, it is typically represented using a 2D array or a `vector<vector<int>>`.

---

## Table of Contents
1. [2D Matrix Basics](#2d-matrix-basics)
2. [Primary Diagonal](#1-primary-diagonal)
3. [Secondary Diagonal](#2-secondary-diagonal)
4. [Matrix Summation](#3-matrix-summation)
5. [Matrix Multiplication](#4-matrix-multiplication)
6. [Search in Matrix](#5-search-in-matrix)
7. [Diagonal Difference](#6-diagonal-difference)
8. [Mirror Array](#7-mirror-array)
9. [8 Neighbors](#8-8-neighbors)

---

## 2D Matrix Basics

### 1. Declaring a 2D Matrix
```cpp
int rows = 3, cols = 3;
int matrix[rows][cols];
```

### 2. Initializing a 2D Matrix
```cpp
int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
```

### 3. Taking Input
```cpp
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        cin >> matrix[i][j];
    }
}
```

### 4. Printing the Matrix
```cpp
for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
        cout << matrix[i][j] << " ";
    }
    cout << endl;
}
```

### 5. Accessing Rows & Columns
```cpp
// Accessing 2nd row
for (int j = 0; j < cols; ++j) cout << matrix[1][j] << " ";

// Accessing 3rd column
for (int i = 0; i < rows; ++i) cout << matrix[i][2] << " ";
```

---

## 1. Primary Diagonal

### Problem Title
Extract and Print Primary Diagonal Elements.

### Problem Statement
In a square matrix, print the elements where the row index equals the column index ($i == j$). This path goes from the top-left to the bottom-right.

### Approach
- **Standard:** Nested loops checking `if (i == j)`.
- **Optimized:** Single loop `matrix[i][i]`.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < matrix.size(); i++) {
        cout << matrix[i][i] << " ";
    }
    cout << endl;
    return 0;
}
```

### Complexity
- **Time Complexity:** $O(n)$ where $n$ is the number of rows.
- **Space Complexity:** $O(1)$.

---

## 2. Secondary Diagonal

### Problem Title
Extract and Print Secondary Diagonal Elements.

### Problem Statement
Print elements from the top-right to the bottom-left corner. The condition for the secondary diagonal is $i + j == n - 1$.

### Approach
- **Standard:** Nested loops `if (i + j == n - 1)`.
- **Optimized:** Single loop `matrix[i][n - 1 - i]`.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (int i = 0; i < matrix.size(); i++) {
        cout << matrix[i][matrix.size() - 1 - i] << " ";
    }
    cout << endl;
    return 0;
}
```

### Complexity
- **Time Complexity:** $O(n)$ 
- **Space Complexity:** $O(1)$.

---

## 3. Matrix Summation

### Problem Title
Add Two Matrices ($A + B$).

### Problem Statement
Given two matrices of identical dimensions, calculate their sum by adding corresponding elements.

### Approach
Iterate through the rows and columns and set $C[i][j] = A[i][j] + B[i][j]$.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> matrix2 = {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}};

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
}
```

### Complexity
- **Time Complexity:** $O(n \times m)$
- **Space Complexity:** $O(n \times m)$ for the result matrix.

---

## 4. Matrix Multiplication

### Problem Title
Multiply Two Matrices ($A \times B$).

### Problem Statement
Multiply matrix $A[m][n]$ with $B[n][p]$ to get a resulting matrix $C[m][p]$.

### Approach
1. For each cell $C[i][j]$, take the dot product of the $i^{th}$ row of $A$ and the $j^{th}$ column of $B$.
2. Use a triple loop: $i$ (rows of $A$), $j$ (columns of $B$), and $k$ (common dimension $n$).

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    vector<vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    vector<vector<int>> B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    vector<vector<int>> result(A.size(), vector<int>(B[0].size(), 0));

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < B[0].size(); j++) {
            for (int k = 0; k < A[0].size(); k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    for (const auto& row : result) {
        for (const auto& elem : row) cout << elem << " ";
        cout << endl;
    }
}
```

### Complexity
- **Time Complexity:** $O(m \times n \times p)$
- **Space Complexity:** $O(m \times p)$.

---

## 5. Search in Matrix

### Problem Title
Find Value in Matrix.
**Problem Link:** [Codeforces - Search in Matrix](https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/S)

### Problem Statement
Given an $n \times m$ matrix and a value $x$, determine if $x$ exists in the matrix.

### Approach
Simple brute force search by iterating through all $n \times m$ elements.

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n, m; cin >> n >> m;
    int a[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];
    
    int x; cin >> x;
    bool found = false;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            if (a[i][j] == x) { found = true; break; }
        }
    }
    if (found) cout << "will not take number" << endl;
    else cout << "will take number" << endl;
}
```

### Complexity
- **Time Complexity:** $O(n \times m)$.
- **Space Complexity:** $O(1)$.

---

## 6. Diagonal Difference

### Problem Title
Absolute Difference of Matrix Diagonals.
**Problem Link:** [Codeforces - Matrix](https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/T)

### Problem Statement
Calculate the absolute difference between the sum of the primary diagonal and the sum of the secondary diagonal.

### Approach
1. Primary sum: Add elements where `i == j`.
2. Secondary sum: Add elements where `i + j == n - 1`.
3. Optimized using a single loop for the square matrix.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int a[n][n];
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++) cin >> a[i][j];

    int primary = 0, secondary = 0;
    for(int i=0; i<n; i++){
        primary += a[i][i];
        secondary += a[i][n-i-1];
    }
    cout << abs(primary - secondary) << endl;
}
```

### Complexity
- **Time Complexity:** $O(n)$.
- **Space Complexity:** $O(1)$.

---

## 7. Mirror Array

### Problem Title
Reflect/Reverse Rows of a Matrix.
**Problem Link:** [Codeforces - Mirror Array](https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/W)

### Problem Statement
Reverse the elements of each row in an $n \times m$ matrix.

### Approach
For each row `i`, use two pointers (`x=0`, `y=m-1`) to swap elements until they meet in the middle.

### Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int n, m; cin >> n >> m;
    int a[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m / 2; j++) swap(a[i][j], a[i][m - j - 1]);
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++) cout << a[i][j] << " ";
        cout << endl;
    }
}
```

### Complexity
- **Time Complexity:** $O(n \times m)$.
- **Space Complexity:** $O(1)$.

---

## 8. 8 Neighbors

### Problem Title
Check Neighbors of a Matrix Cell.
**Problem Link:** [Codeforces - 8 Neighbors](https://codeforces.com/group/MWSDmqGsZm/contest/219774/problem/X)

### Problem Statement
Given a character matrix, determine if a specific cell `(x, y)` is surrounded entirely by 'x' on all 8 sides (horizontal, vertical, diagonal).

### Approach
1. Define direction arrays `dx[]` and `dy[]` for the 8 neighbors.
2. Validate each neighbor using an `isValid` function.
3. If a neighbor exists and is not 'x', the condition fails.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

bool isValid(int x, int y, int n, int m) {
    return (x >= 0 && x < n && y >= 0 && y < m);
}

int main() {
    int n, m; cin >> n >> m;
    char a[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];

    int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    int dy[] = {0, 0, -1, 1, 1, -1, -1, 1};
    int x, y; cin >> x >> y;
    x--; y--; // 1-based to 0-based conversion

    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (!isValid(nx, ny, n, m)) { cnt++; continue; }
        if (a[nx][ny] == 'x') cnt++;
    }

    if(cnt == 8) cout << "yes" << endl;
    else cout << "no" << endl;
}
```

### Complexity
- **Time Complexity:** $O(1)$ (always checks 8 directions).
- **Space Complexity:** $O(1)$.
