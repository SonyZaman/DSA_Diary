# Array Practice Problems

This directory contains solutions to common array-based interview problems.

---

## Table of Contents
1. [Second Largest Element](#1-second-largest-element)
2. [Kth Largest Element](#2-kth-largest-element)
3. [Rotate Array (Brute Force)](#3-rotate-array-brute-force--extra-space)
4. [Rotate Array (Optimized)](#4-rotate-array-optimized--triple-reverse)

---

## 1. Second Largest Element

### Problem Title
Find the second largest element in an array.

### Problem Statement
Given an array, find the element that is strictly smaller than the maximum but larger than all other elements.

### Approach
1.  **Single Pass:** Use two variables, `first` and `second`.
2.  **Logic:** 
    - If current element > `first`: update `second = first`, then `first = current`.
    - Else if current element > `second` AND current element != `first`: update `second = current`.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[] = {30, 21, 45, 22, 73, 45};
    int n = sizeof(arr)/sizeof(arr[0]);
    int first = -1, second = -1;

    for(int i = 0; i < n; i++){
        if(arr[i] > first){
            second = first;
            first = arr[i];
        }
        else if(arr[i] > second && arr[i] != first){
            second = arr[i];
        }
    }
    cout << "Second largest element is: " << second << endl;
}
```

### Complexity
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(1)$

---

## 2. Kth Largest Element

### Problem Title
Find the $K^{th}$ largest element in an array.
**Online Judge Link:** [LeetCode 215 - Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)

### Problem Statement
Find the element that would appear at the $K^{th}$ position if the array were sorted in descending order.

### Approach
- **Counting Sort Logic:** This specific solution uses a frequency array (`cnt`) to count occurrences of each number (handling offsets for mapping negative values). It then iterates backwards through the frequency array to find the $K^{th}$ number.

### Code
```cpp
class Solution {
public:
    int kthLargest(vector<int>& arr, int k) {
        vector<int> cnt(20001, 0); // Assuming range -10000 to 10000

        for(int i = 0; i < arr.size(); i++){
            cnt[arr[i] + 10000]++;
        }

        for(int i = 20000; i >= 0; i--){
            k -= cnt[i];  
            if(k <= 0) return i - 10000;
        }
        return -1;
    }
};
```

### Complexity
- **Time Complexity:** $O(n + \text{range})$
- **Space Complexity:** $O(\text{range})$

---

## 3. Rotate Array (Brute Force / Extra Space)

### Problem Title
Rotate an array to the right by $K$ steps.

### Approach
- **Extra Space:** Create a temporary vector. Copy the last $K$ elements into it, then copy the remaining elements. Finally, replace the original array with the temporary one.

### Code
```cpp
void rotateArray(vector<int>& arr, int k) {
    k = k % arr.size();
    vector<int> temp;
    for(int j = arr.size() - k; j < arr.size(); j++){
        temp.push_back(arr[j]);
    }
    for(int j = 0; j < arr.size() - k; j++){
        temp.push_back(arr[j]);
    }
    arr = temp;
}
```

### Complexity
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(n)$

---

## 4. Rotate Array (Optimized / Triple Reverse)

### Problem Title
Rotate an array to the right by $K$ steps (In-place).
**Online Judge Link:** [LeetCode 189 - Rotate Array](https://leetcode.com/problems/rotate-array/)

### Approach
- **Triple Reverse:** 
    1. Reverse the entire array.
    2. Reverse the first $K$ elements.
    3. Reverse the remaining $n-K$ elements.

### Code
```cpp
class Solution {
public:
    void rotate(vector<int>& arr, int k) {
        k = k % arr.size();
        reverse(arr.begin(), arr.end());
        reverse(arr.begin(), arr.begin() + k);
        reverse(arr.begin() + k, arr.end());
    }
};
```

### Complexity
- **Time Complexity:** $O(n)$
- **Space Complexity:** $O(1)$
