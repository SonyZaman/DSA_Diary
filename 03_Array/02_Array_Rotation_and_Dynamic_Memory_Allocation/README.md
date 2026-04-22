# Array Rotation and Dynamic Memory Allocation

This directory covers advanced array manipulation techniques including rotations and the fundamentals of dynamic memory management in C++.

---

## Table of Contents

### Part 1: Array Rotation
1. [Left Rotation (by 1)](#1-left-rotation-by-1)
2. [Right Rotation (by 1)](#2-right-rotation-by-1)
3. [Left Rotation by K Times](#3-left-rotation-by-k-times)
4. [Right Rotation by K Times](#4-right-rotation-by-k-times)

### Part 2: Dynamic Memory Allocation
1. [Basic Allocation & Deletion](#1-basic-allocation--deletion)
2. [Dynamic Array](#2-dynamic-array)
3. [Resizing a Dynamic Array](#3-resizing-a-dynamic-array-manual)
4. [Dynamic Objects](#4-dynamic-objects)
5. [Best Practices](#summary-of-best-practices)

---

## Part 1: Array Rotation

Array rotation involves shifting elements in a circular fashion.

### 1. Left Rotation (by 1)

#### Problem Title
Rotate an array left by one position.

#### Problem Statement
Given an array, move the first element to the last position and shift all other elements one position to the left.

#### Approach
1.  **Store First:** Save the first element in a temporary variable.
2.  **Shift:** Move elements at `i` to `i-1`.
3.  **Replace Last:** Place the saved first element at the last index.

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) cin >> a[i];

    int val = a[0];
    for(int i = 1; i < n; i++){
        a[i-1] = a[i];
    }
    a[n-1] = val;

    for(int i = 0; i < n; i++) cout << a[i] << " ";
}
```

#### Complexity
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(1)$

---

### 2. Right Rotation (by 1)

#### Problem Title
Rotate an array right by one position.

#### Problem Statement
Move the last element to the first position and shift all other elements one position to the right.

#### Approach
1.  **Store Last:** Save the last element in a variable.
2.  **Shift:** Move elements from the end towards the beginning (`i = i-1`).
3.  **Replace First:** Place the saved last element at index 0.

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int a[n];
    for(int i = 0; i < n; i++) cin >> a[i];

    int val = a[n-1];
    for(int i = n - 1; i > 0; i--){
        a[i] = a[i-1];
    }
    a[0] = val;

    for(int i = 0; i < n; i++) cout << a[i] << " ";
}
```

#### Complexity
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(1)$

---

### 3. Left Rotation by K Times

#### Problem Title
Rotate an array left by $K$ positions.

#### Approach 3.1: Using Modulo (New Array)
Calculate the new index for each element using the formula: `(i + n - k) % n`.

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
   int n = 5;
   int a[] = {1, 2, 3, 4, 5};
   int k = 33;
   int temp[n];

   for(int i = 0; i < n; i++){
       k = k % n;
       int idx = (i + n - k) % n;
       temp[idx] = a[i]; // Corrected index mapping logic
   }

   for(int i : temp) cout << i << " ";
}
```

#### Approach 3.2: Using Reverse (In-place)
1. Reverse the first $K$ elements.
2. Reverse the remaining $n-K$ elements.
3. Reverse the whole array.

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

void reverse(int a[], int l, int r) {
    while (l < r) {
        swap(a[l], a[r]);
        l++; r--;
    }
}

int main() {
    int n = 5;
    int a[] = {1, 2, 3, 4, 5};
    int k = 3; k = k % n;

    reverse(a, 0, k - 1);
    reverse(a, k, n - 1);
    reverse(a, 0, n - 1);

    for (int i : a) cout << i << " ";
}
```

#### Complexity
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(1)$ for Reverse, $O(n)$ for Modulo approach.

---

### 4. Right Rotation by K Times

#### Problem Title
Rotate an array right by $K$ positions.
**Online Judge Link:** [LeetCode 189 - Rotate Array](https://leetcode.com/problems/rotate-array/)

#### Approach 4.1: Using Modulo (New Array)
New index formula: `(i + k) % n`.

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
   int n = 5;
   int a[] = {1, 2, 3, 4, 5};
   int k = 33;
   int temp[n];

   for(int i = 0; i < n; i++){
       k = k % n;
       int idx = (i + k) % n;
       temp[idx] = a[i];
   }

   for(int i : temp) cout << i << " ";
}
```

#### Approach 4.2: Using Reverse (In-place)
1. Reverse the whole array.
2. Reverse the first $K$ elements.
3. Reverse the remaining elements.

#### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

void reverse(int a[], int l, int r) {
    while (l < r) {
        swap(a[l], a[r]);
        l++; r--;
    }
}

int main() {
    int n = 5;
    int a[] = {1, 2, 3, 4, 5};
    int k = 3; k = k % n;

    reverse(a, 0, n - 1);
    reverse(a, 0, k - 1);
    reverse(a, k, n - 1);

    for (int i : a) cout << i << " ";
}
```

---

## Part 2: Dynamic Memory Allocation

Dynamic memory allows you to control memory lifespan and size at runtime using the `new` and `delete` keywords.

### 1. Basic Allocation & Deletion

#### Code
```cpp
int *p = new int;   // Heap allocation
*p = 10;
delete p;           // Freeing memory
```

### 2. Dynamic Array
Useful when the size of the array is only known at runtime.

#### Code
```cpp
int n = 5;
int *arr = new int[n];
for(int i = 0; i < n; i++) arr[i] = i + 1;
delete[] arr; // Note the [] for arrays
```

### 3. Resizing a Dynamic Array (Manual)
Since raw arrays cannot be resized directly, we must manually copy the data to a larger block.

#### Approach
1. Create a `newArr` with the larger size.
2. Copy elements from `oldArr` to `newArr`.
3. `delete[] oldArr`.
4. Point the old pointer to the new array.

#### Code
```cpp
int oldSize = 5;
int *oldArr = new int[oldSize];

int newSize = 8;
int *newArr = new int[newSize];

// Copy
for(int i = 0; i < oldSize; i++) newArr[i] = oldArr[i];

delete[] oldArr; // Old memory freed
```

### 4. Dynamic Objects
Creating objects on the heap using `new`.

#### Code
```cpp
class Student {
public:
    string name;
    Student(string n) : name(n) {}
    void show() { cout << "Name: " << name << endl; }
};

Student *s = new Student("Rahat");
s->show();
delete s;
```

### Summary of Best Practices
- **Always pair `new` with `delete`.**
- **Always pair `new[]` with `delete[]`.**
- Set pointers to `nullptr` after deleting to avoid dangling pointers.
