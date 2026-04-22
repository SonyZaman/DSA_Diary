# Array Operations

This directory contains fundamental operations on arrays, such as insertion, deletion, reversing, and merging.

---

## Table of Contents
1. [Insert at Any Index](#1-insert-at-any-index)
2. [Delete from Any Index](#2-delete-from-any-index)
3. [Reverse an Array](#3-reverse-an-array)
4. [Reverse an Array using Two Pointers](#4-reverse-an-array-using-two-pointers)
5. [Merge Two Sorted Arrays](#5-merge-two-sorted-arrays)
6. [Check if an Array is Sorted](#6-check-if-an-array-is-sorted)

---

## 1. Insert at Any Index

### Problem Title
Insert an element at a specific index in an array.

### Problem Statement
Given an array of size `n` and an element `val`, insert `val` at a given index `indx`. The array size effectively increases by one, and all elements from `indx` onwards must be shifted one position to the right.

### Approach
1.  **Shift Right:** Starting from the last element (index `n-1`), move each element to the next position (`i+1 = i`) until the target index `indx` is reached.
2.  **Insert:** Place the new value at `indx`.
3.  **Complexity:** This approach is optimized for static arrays by performing an in-place shift.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int arr[n+1];

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

   int indx, val;
   cin >> indx >> val;

   for(int i = n - 1; i >= indx; i--){
       arr[i+1] = arr[i];
   }
   arr[indx] = val;

   for(int i = 0; i <= n; i++){
       cout << arr[i] << " ";
   }
}
```

### Explanation
-   We declare an array of size `n+1` to accommodate the new element.
-   The loop `for(int i = n - 1; i >= indx; i--)` shifts elements to the right to make a "hole" at the target index.
-   Accessing the array beyond its original bounds (index `n+1`) is safe here because the array was declared with size `n+1`.

### Time Complexity
$O(n)$ - In the worst case (inserting at index 0), we shift all $n$ elements.

### Space Complexity
$O(1)$ - (Excluding the input array) No auxiliary data structures are used.

---

## 2. Delete from Any Index

### Problem Title
Delete an element from a specific index in an array.

### Problem Statement
Given an array and an index `indx`, remove the element at that index. The subsequent elements must be shifted one position to the left to fill the gap.

### Approach
1.  **Shift Left:** Starting from the target index `indx`, move each subsequent element to the left (`i = i+1`).
2.  **Logic:** The size of the active array decreases by 1.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int arr[n];

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

   int indx;
   cin >> indx;

   for(int i = indx; i < n-1; i++){
       arr[i] = arr[i+1];
   }
   arr[n-1] = -1; // Optional: mark the last slot as empty

   for(int i = 0; i < n-1; i++){
       cout << arr[i] << " ";
   }
}
```

### Explanation
-   The loop starts at `indx` and pulls elements from the right to the current position.
-   We print only up to `n-1` as the last element's value is now duplicated or redundant.

### Time Complexity
$O(n)$ - In the worst case (deleting from index 0), we shift $n-1$ elements.

### Space Complexity
$O(1)$

---

## 3. Reverse an Array

### Problem Title
Reverse the elements of an array.

### Problem Statement
Given an array, rearrange the elements such that the first element becomes the last, the second become the second to last, and so on.

### Approach
1.  **Iterate to Middle:** Loop through the first half of the array ($n/2$).
2.  **Swap:** Swap the element at index `i` with the element at index `n-1-i`.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int arr[n];

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    for(int i = 0; i < n/2; i++){
        swap(arr[i], arr[n-1-i]);
    }

    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}
```

### Explanation
-   `swap(arr[i], arr[n-1-i])` is a built-in utility that efficiently exchanges values.
-   We only loop until `n/2` because swapping past the middle would just reverse the array back to its original state.

### Time Complexity
$O(n)$ - Specifically $n/2$ swaps.

### Space Complexity
$O(1)$

---

## 4. Reverse an Array using Two Pointers

### Problem Title
Reverse an array using the Two-Pointer technique.

### Problem Statement
Reverse the elements of an array by moving two indices (start and end) towards each other.

### Approach
1.  **Initialize Pointers:** Set `i = 0` and `j = n - 1`.
2.  **While Loop:** While `i < j`, swap elements at `i` and `j`, then increment `i` and decrement `j`.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    int arr[n];

    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    int i = 0, j = n - 1;
    while(i < j){
        swap(arr[i], arr[j]);
        i++;
        j--;
    }

    for(int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}
```

### Explanation
-   This is the preferred approach for readability and is widely used for string and array manipulation.
-   The logic is the same as the $n/2$ approach but explicitly uses two markers.

### Time Complexity
$O(n)$

### Space Complexity
$O(1)$

---

## 5. Merge Two Sorted Arrays

### Problem Title
Merge two sorted arrays into a third sorted array.

### Problem Statement
Given two arrays `arr1` and `arr2` that are already sorted, merge them into a single sorted array `merged`.

### Approach
1.  **Two Pointers:** Maintain two pointers `i` and `j` for `arr1` and `arr2`.
2.  **Compare:** Compare `arr1[i]` and `arr2[j]`. Add the smaller one to the `merged` array and increment its pointer.
3.  **Residual Elements:** After one array is exhausted, copy the remaining elements of the other array into `merged`.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10, 12, 20};

    int n1 = sizeof(arr1)/sizeof(arr1[0]);
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    int i = 0, j = 0;
    int merged[n1+n2];
    int k = 0;

    while(i < n1 && j < n2){
        if(arr1[i] < arr2[j]){
            merged[k++] = arr1[i++];
        }
        else{
            merged[k++] = arr2[j++];
        }
    }

    while(i < n1){
        merged[k++] = arr1[i++];
    }   
    
    while(j < n2){
        merged[k++] = arr2[j++];
    }

    for(auto x : merged) cout << x << " ";
    return 0;
}
```

### Explanation
-   The core logic relies on the fact that both input arrays are already sorted.
-   The time complexity is linear because each element is visited and placed exactly once.

### Time Complexity
$O(n1 + n2)$ - Linear time relative to the total number of elements.

### Space Complexity
$O(n1 + n2)$ - Space for the new merged array.

---

## 6. Check if an Array is Sorted

### Problem Title
Check if an array is sorted in ascending order.

### Problem Statement
Determine if an array is sorted such that each element is less than or equal to the next element ($arr[i] \le arr[i+1]$).

### Approach
1.  **Iterate and Compare:** Loop from the second element to the last.
2.  **Violation Check:** If `arr[i] < arr[i-1]`, the array is not sorted. Set a flag to `false` and break.

### Code
```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    bool isSorted = true;
    for(int i = 1; i < n; i++){
        if(arr[i] < arr[i-1]){
            isSorted = false;
            break;
        }
    }
    if(isSorted){
        cout << "Array is sorted";
    }
    else{
        cout << "Array is not sorted";
    }
    return 0;
}
```

### Explanation
-   The loop compares the current element with the previous one.
-   The search terminates early if a violation is found, making it efficient.

### Time Complexity
$O(n)$

### Space Complexity
$O(1)$
