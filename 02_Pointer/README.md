# Pointers — Complete Interview Reference

> **How to use this file:** Read once to build intuition. Re-read the night before an interview. Everything — concepts, code, memory diagrams, and common mistakes — is here in one place.

---

## Table of Contents

1. [What is a Pointer?](#1-what-is-a-pointer)
2. [Memory Layout — How Variables Live in RAM](#2-memory-layout--how-variables-live-in-ram)
3. [Declaring and Initializing Pointers](#3-declaring-and-initializing-pointers)
4. [Address-of (&) and Dereference (*) Operators](#4-address-of--and-dereference--operators)
5. [Pointer Arithmetic](#5-pointer-arithmetic)
6. [Pointers and Arrays](#6-pointers-and-arrays)
7. [Pointer to a Pointer (Double Pointer)](#7-pointer-to-a-pointer-double-pointer)
8. [Function Argument Passing — Value, Pointer, Reference](#8-function-argument-passing--value-pointer-reference)
9. [Arrow Operator (->)](#9-arrow-operator)
10. [Function Pointers](#10-function-pointers)
11. [Static Keyword and Memory Sections](#11-static-keyword-and-memory-sections)
12. [Dynamic Memory Allocation](#12-dynamic-memory-allocation)
13. [Pointers and Strings](#13-pointers-and-strings)
14. [Pointers and Structures](#14-pointers-and-structures)
15. [Self-Referential Structure — Linked List Intro](#15-self-referential-structure--linked-list-intro)
16. [Common Mistakes and Debugging Tips](#16-common-mistakes-and-debugging-tips)
17. [Best Practices Checklist](#17-best-practices-checklist)

---

## 1. What is a Pointer?

A pointer is a special variable that stores the **memory address** of another variable. Instead of holding a value directly, it "points to" the location in memory where the value is stored.

```
int x = 42;
```

When you write this, C/C++ goes to RAM and reserves **4 bytes** (size of int). It stores `42` there. That location has an address, e.g., `0x7FF3A`.

```
    Variable: x
    +-----------------------------+
    |            42               |   <- Value
    +-----------------------------+
    Address: 0x7FF3A                  <- Location in RAM
    Size: 4 bytes (int)
```

You have been using addresses since day one with `scanf`:

```cpp
int x;
scanf("%d", &x);   // &x = "the address of x" — send user input there directly
```

`&x` means "where is x in memory?" — scanf needs the address so it can write directly to that location.

```
printf("%d", x)   ->  "what is inside the box?"   -> 42
printf("%p", &x)  ->  "where is the box?"         -> 0x7FF3A
scanf("%d", &x)   ->  "go to this address, put value there"
```

> **In simple terms:** A pointer is a variable that stores another variable's address. That's it.

---

## 2. Memory Layout — How Variables Live in RAM

When your program runs, the OS gives it a chunk of memory divided into sections:

```
+-----------------------------+  <- high address
|           Stack             |
|  - local variables          |
|  - function parameters      |
|  - created on function call |
|  - DESTROYED on return      |
|         (grows down)        |
+-----------------------------+
|       (empty space)         |
+-----------------------------+
|         (grows up)          |
|           Heap              |
|  - malloc/calloc/new        |
|  - YOU manage it            |
|  - stays until free()       |
+-----------------------------+
|      Static / Global        |
|  - static variables         |
|  - global variables         |
|  - alive the whole program  |
+-----------------------------+
|           Code              |
|  - your compiled code       |
|  - read-only                |
+-----------------------------+  <- low address
```

| Section | What lives here | Lifetime |
|---------|----------------|----------|
| Stack | Local variables, parameters | Until function returns |
| Heap | malloc/calloc/new memory | Until you call free() |
| Static/Global | static & global variables | Entire program |
| Code | Compiled instructions | Entire program |

> **Why this matters:** This explains why local variable pointers go dangling after a function returns (Stack dies), and why malloc memory persists (Heap stays until freed).

---

## 3. Declaring and Initializing Pointers

Declare a pointer by putting `*` before the pointer name.

**Syntax:**
```cpp
data_type *pointer_name;
```

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int var = 10;
    int *ptr = &var;   // ptr holds the memory address of var

    cout << "Value of var: " << var << endl;
    cout << "Address of var: " << &var << endl;
    cout << "Value of ptr (address it holds): " << ptr << endl;
    return 0;
}
```

**Memory diagram:**

```
    var (regular variable)        ptr (pointer variable)
    +----------------+            +----------------+
    |       10       |            |   0x7FF3A      |   <- stores address of var
    +----------------+            +----------------+
    Address: 0x7FF3A              Address: 0xB4C10
    "I store values"              "I store addresses"
```

> **Always initialize pointers!** An uninitialized pointer holds a garbage address — writing to it crashes or silently corrupts memory.

```cpp
int *p = nullptr;   // safe — explicitly "points nowhere"
int *p = &someVar;  // safe — points to a known variable
// int *p;          // DANGEROUS — garbage address!
```

---

## 4. Address-of (&) and Dereference (*) Operators

| Operator | Name | What it does |
|----------|------|-------------|
| `&` | Address-of | Returns the memory address of a variable |
| `*` | Dereference | Returns the value at the address stored in a pointer |

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int var = 25;
    int *ptr = &var;

    cout << "Value of var: " << var << endl;               // 25
    cout << "Address stored in ptr: " << ptr << endl;      // 0x7FF3A
    cout << "Value at that address (*ptr): " << *ptr << endl; // 25

    *ptr = 50;   // go to address in ptr, write 50 there
    cout << "New value of var: " << var << endl;           // 50
    return 0;
}
```

**How dereference (*ptr) works step by step:**

```
Step 1: Look inside ptr         ->  0x7FF3A (the address)
Step 2: Go to that address      ->  arrive at var's location
Step 3: Read what's there       ->  42

Think of it: ptr = "address written on paper"
             *ptr = "go to that address and open the door"
```

**Summary:**
```
p   = 0x7FF3A        <- "the address written on paper"
*p  = 42             <- "the value behind the door at that address"
&x  = 0x7FF3A        <- "what address is x at?"
```

---

## 5. Pointer Arithmetic

You can add and subtract integers from pointers. **Every increment moves by the size of the pointed-to type**, not 1 byte.

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int numbers[] = {10, 20, 30, 40, 50};
    int *ptr = numbers;   // points to first element

    cout << "First: "  << *ptr << endl;    // 10

    ptr++;   // move to next int (4 bytes forward)
    cout << "Second: " << *ptr << endl;   // 20

    ptr--;   // move back
    cout << "First again: " << *ptr << endl;  // 10

    ptr = ptr + 2;   // skip 2 ints forward
    cout << "Third: " << *ptr << endl;    // 30
    return 0;
}
```

**Why does ptr+1 jump 4 bytes (not 1)?**

```
    ptr          ptr+1        ptr+2        ptr+3
     |            |            |            |
     v            v            v            v
  0xA2B00      0xA2B04      0xA2B08      0xA2B0C
  [4 bytes]    [4 bytes]    [4 bytes]    [4 bytes]
```

```
char *cp;    // cp + 1 -> 1 byte forward
int  *ip;    // ip + 1 -> 4 bytes forward
double *dp;  // dp + 1 -> 8 bytes forward
```

**Subtracting two pointers** gives the number of elements between them:

```cpp
int arr[] = {10, 20, 30, 40, 50};
int *p1 = &arr[1];   // points to 20
int *p2 = &arr[4];   // points to 50

cout << p2 - p1;     // 3 (three elements between them)
```

> **Rule:** Pointer arithmetic only makes sense within consecutive memory (e.g., arrays). Never do arithmetic between two unrelated pointers.

---

## 6. Pointers and Arrays

In C++, **arrays and pointers are closely related**. The array name itself is a pointer to the first element.

```cpp
int arr[] = {5, 10, 15, 20, 25};
```

```
printf("%p", arr);      // 0xA2B00
printf("%p", &arr[0]); // 0xA2B00  <- same!
```

`arr` and `&arr[0]` are the same address. So these are all equivalent:

```
arr[i]   ==   *(arr + i)   ==   *(i + arr)   ==   i[arr]  (all same!)
```

**Why? Because `arr[i]` is just shorthand for `*(arr + i)` — the compiler converts it automatically.**

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int arr[5] = {5, 10, 15, 20, 25};
    int *ptr = arr;

    // Method 1: using array name as pointer
    for (int i = 0; i < 5; i++)
        cout << "Element " << i << ": " << *(arr + i) << endl;

    // Method 2: using a separate pointer with increment
    for (int i = 0; i < 5; i++) {
        cout << "Element " << i << ": " << *ptr << endl;
        ptr++;
    }
    return 0;
}
```

**Memory diagram:**

```
    arr      arr+1    arr+2    arr+3    arr+4
     |         |        |        |        |
     v         v        v        v        v
  +------+------+------+------+------+
  |  5   |  10  |  15  |  20  |  25  |
  +------+------+------+------+------+
  0xA2B00 0xA2B04 0xA2B08 0xA2B0C 0xA2B10
```

**Array name vs pointer — key differences:**

| | Array name | Pointer variable |
|-|-----------|-----------------|
| `sizeof` | Full array size (e.g., 20 bytes) | Pointer size (8 bytes on 64-bit) |
| Reassign | Cannot (`arr = p` is illegal) | Can (`p = arr` is fine) |
| Increment | Cannot (`arr++` is illegal) | Can (`p++` is fine) |

---

## 7. Pointer to a Pointer (Double Pointer)

A pointer can store the address of another pointer. This is a **double pointer**, declared with `**`.

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int val = 10;

    int *ptr = &val;    // ptr stores address of val
    int **ptr2 = &ptr;  // ptr2 stores address of ptr

    cout << "ptr  holds: " << ptr  << ", *ptr  = " << *ptr  << endl;
    cout << "ptr2 holds: " << ptr2 << ", *ptr2 = " << *ptr2 << endl;

    **ptr2 = 50;   // modify val through double pointer

    cout << "New val: " << val << endl;   // 50
    return 0;
}
```

**Memory diagram:**

```
    ptr2                  ptr                   val
    +----------+          +----------+          +----------+
    | 0xB4C10  |  ------> | 0x7FF3A  |  ------> |    10    |
    +----------+          +----------+          +----------+
    addr:0xD2E40          addr:0xB4C10          addr:0x7FF3A
```

**Three levels of access:**

```cpp
val          // 10  — direct
*ptr         // 10  — one dereference: follow ptr -> val
**ptr2       // 10  — two dereferences: follow ptr2 -> ptr -> val
```

**Step-by-step for `**ptr2`:**
```
Step 1: *ptr2  ->  ptr2 points to ptr  ->  get ptr
Step 2: *ptr   ->  ptr points to val   ->  get val = 10
```

**When to use double pointers:**
- Modify a pointer itself inside a function (e.g., make caller's pointer NULL)
- Allocate memory inside a function and give it back to the caller
- Dynamic 2D arrays (array of arrays)

---

## 8. Function Argument Passing — Value, Pointer, Reference

### 8.1 Pass by Value

Function gets a **copy** of the argument. Changes inside the function do NOT affect the original.

```cpp
#include <bits/stdc++.h>
using namespace std;
void modify(int val)
{
    val = 50;   // only the copy changes
}
int main()
{
    int val = 10;
    modify(val);
    cout << val << endl;   // still 10
    return 0;
}
```

```
    main:          modify():
    +------+       +------+
    |  10  |  -->  |  10  |  -> 50 (copy)
    +------+       +------+
      val            val (copy)

    main's val? Still 10 — untouched!
```

**Use when:** You don't need to modify the original, or for small types (int, char, double).

---

### 8.2 Pass by Pointer

Function receives the **address**. By dereferencing it, the function can modify the original variable.

```cpp
#include <bits/stdc++.h>
using namespace std;
void modify(int *ptr)
{
    *ptr = 50;   // go to the original address and write 50
}
int main()
{
    int val = 10;
    modify(&val);   // pass the address
    cout << val << endl;   // 50 — changed!
    return 0;
}
```

```
    main:                   modify(int *ptr):
    +------+                ptr = 0x7FF3A
    |  10  |  <--- ptr --->  *ptr = 50
    +------+
    0x7FF3A
    
    After: val = 50
```

**Use when:** Need to modify the original, pass large objects/arrays, or indicate optional arguments (nullptr).

---

### 8.3 Pass by Reference

Function receives an **alias** (another name) for the original variable. Same effect as pointer, but cleaner syntax — no `&` at call site, no `*` inside function.

```cpp
#include <bits/stdc++.h>
using namespace std;
void modify(int &val)
{
    val = 50;
    cout << &val << endl;   // same address as main's val
}
int main()
{
    int val = 10;
    cout << &val << endl;   // same address
    modify(val);            // no & needed at call site
    cout << val << endl;    // 50 — changed!
    return 0;
}
```

**Use when:** Need to modify the original with cleaner syntax, pass large objects without copying, and the argument is guaranteed non-null.

---

### Comparison Table

| Method | Syntax (function) | Syntax (call) | Modifies original? | Can be null? |
|--------|------------------|---------------|-------------------|-------------|
| By Value | `void f(int x)` | `f(val)` | No | N/A |
| By Pointer | `void f(int *x)` | `f(&val)` | Yes | Yes (nullptr) |
| By Reference | `void f(int &x)` | `f(val)` | Yes | No |

---

### Classic Example: Swap

```cpp
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int main() {
    int x = 10, y = 20;
    swap(&x, &y);
    cout << x << " " << y;   // 20 10
}
```

```
Before: x = 10, y = 20
temp = *a = 10
*a   = *b = 20    ->  x is now 20
*b   = temp = 10  ->  y is now 10
After:  x = 20, y = 10
```

---

## 9. Arrow Operator (->)

When a pointer points to an object/struct, use `->` to access its members. It is shorthand for `(*ptr).member`.

```cpp
#include <bits/stdc++.h>
using namespace std;
class Student
{
public:
    int a, b;
    Student(int a, int b)
    {
        this->a = a;
        this->b = b;
    }
};
int main()
{
    Student obj(10, 20);
    Student *ptr = &obj;

    cout << obj.a  << " " << obj.b  << endl;   // dot — direct object
    cout << ptr->a << " " << ptr->b << endl;   // arrow — through pointer
    //  ptr->a  is exactly the same as  (*ptr).a
    return 0;
}
```

**Why not `*ptr.a`?**
```
*ptr.a    ->  *(ptr.a)   <- dot has higher priority than * !
              ptr has no member 'a' -> ERROR

(*ptr).a  ->  correct (dereference first, then access member)
ptr->a    ->  same thing, cleaner syntax
```

> **Rule:** Use `.` for direct objects, `->` for pointers to objects. Always prefer `->` over `(*ptr).` for pointer access.

---

## 10. Function Pointers

Functions, like variables, live at a memory address. You can store that address in a **function pointer** and call the function through it.

### Declaring a Function Pointer

```
int (*func_ptr)(int, int);
|    |          |
|    |          +--- parameters the function takes
|    +--- name of the pointer (must have * and parens)
+--- return type
```

```cpp
int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }

int (*operation)(int, int);   // declare

operation = add;                // point to add
cout << operation(3, 4);       // 7

operation = mul;                // point to mul — same pointer, different function!
cout << operation(3, 4);       // 12
```

> **Warning:** `int *f(int, int)` is NOT a function pointer — it's a function that returns `int*`. The parentheses around `*func_ptr` are mandatory!

---

### Passing Function Pointers as Arguments (Callbacks)

```cpp
int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }

// takes a function pointer as parameter
int calculate(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}

int main() {
    cout << calculate(10, 5, add) << endl;   // 15
    cout << calculate(10, 5, sub) << endl;   // 5
    cout << calculate(10, 5, mul) << endl;   // 50
    return 0;
}
```

This pattern is called a **callback** — you pass a function to another function to call later. Adding a new operation requires only a new function, not modifying `calculate`.

C's built-in `qsort` works the same way — you pass a comparison function:

```cpp
int ascending(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}
qsort(arr, n, sizeof(int), ascending);
```

---

### Returning a Pointer from a Function — DANGER!

```cpp
// WRONG! x is a local variable (Stack). It dies when function ends.
int* badFunction() {
    int x = 42;
    return &x;   // Stack memory address returned -> goes invalid!
}
```

```
badFunction() running:    badFunction() returned:
+------+                  address 0x7FF3A is now garbage
|  42  | x                (Stack frame destroyed)
+------+
```

This creates a **Dangling Pointer** — a pointer pointing at freed/invalid memory. Solution: use `static` or `malloc` (see next sections).

---

## 11. Static Keyword and Memory Sections

### static Variables — Live in Static Memory

A `static` local variable lives in the Static section (not Stack), so it persists across function calls.

```cpp
void counter() {
    int normal = 0;        // Stack — reset every call
    static int count = 0;  // Static section — remembers value!

    normal++;
    count++;

    cout << "normal = " << normal << ", count = " << count << endl;
}
int main() {
    counter();   // normal = 1, count = 1
    counter();   // normal = 1, count = 2
    counter();   // normal = 1, count = 3
}
```

```
1st call: normal created (Stack) = 0 -> 1 | count created (Static) = 0 -> 1
          function ends -> normal DELETED, count STAYS!
2nd call: normal created again = 0 -> 1   | count = 1 (remembered!) -> 2
3rd call: normal = 0 -> 1                 | count = 2 -> 3
```

**Fix for dangling pointer — use static:**
```cpp
int* safeFunction() {
    static int x = 42;   // Static memory — NOT destroyed on return
    return &x;            // safe!
}
```

---

## 12. Dynamic Memory Allocation

### Why Dynamic Memory?

```cpp
int n;
cin >> n;
int arr[n];   // risky — Stack-based, size can't change later
```

Instead, borrow memory from the **Heap** at runtime:

```cpp
#include <cstdlib>   // malloc, calloc, realloc, free
```

---

### malloc() — Allocate Memory

```
void* malloc(size_t bytes);
```

Returns the starting address of a new block (or NULL on failure). **Does NOT initialize** the memory — contains garbage.

```cpp
// Single int
int *p = (int *)malloc(sizeof(int));

// Array of 5 ints
int *arr = (int *)malloc(5 * sizeof(int));
```

```
arr
 |
 v
+------+------+------+------+------+
| ???? | ???? | ???? | ???? | ???? |   <- Heap (garbage values!)
+------+------+------+------+------+
arr[0]  arr[1]  arr[2]  arr[3]  arr[4]
```

**Always check for NULL:**

```cpp
int *arr = (int *)malloc(5 * sizeof(int));
if (arr == NULL) {
    cout << "Memory allocation failed!" << endl;
    return 1;
}
// safe to use arr here
```

---

### calloc() — Clear Allocate

Like malloc, but **initializes all bytes to zero**. Two arguments: count and element size.

```cpp
int *arr = (int *)calloc(5, sizeof(int));
// calloc(num_elements, size_per_element)
```

```
malloc:  +------+------+------+------+------+
         | -456 |  0   |  789 |  -12 |  987 |   <- garbage!
         +------+------+------+------+------+

calloc:  +------+------+------+------+------+
         |  0   |  0   |  0   |  0   |  0   |   <- clean zeros!
         +------+------+------+------+------+
```

**malloc vs calloc:**

| | malloc | calloc |
|-|--------|--------|
| Arguments | `malloc(total_bytes)` | `calloc(count, size)` |
| Initialization | No (garbage) | Yes (all zeros) |
| Speed | Slightly faster | Slightly slower (has to zero-fill) |
| Use when | You'll fill all values yourself | You want a clean starting state |

---

### realloc() — Resize Existing Allocation

```
void* realloc(void *ptr, size_t new_total_bytes);
```

Resizes a previously allocated block. Copies existing data. Returns new address (may change!).

```cpp
int *arr = (int *)malloc(5 * sizeof(int));
// ... fill arr ...

// SAFE pattern with temp pointer:
int *temp = (int *)realloc(arr, 10 * sizeof(int));
if (temp != NULL) {
    arr = temp;   // update only if successful
} else {
    // arr still valid! old data safe.
    cout << "Resize failed!" << endl;
}
```

**Why use a temp pointer?**
```
// WITHOUT temp:
arr = (int *)realloc(arr, 10 * sizeof(int));
// If realloc fails -> arr = NULL -> old address LOST forever -> memory leak!

// WITH temp:
int *temp = realloc(arr, 10 * sizeof(int));
if (temp) arr = temp;   // only update if success
// If fail -> arr still has old data!
```

**What realloc does internally:**
```
Case 1 — space available after block: extend in place (same address)
Case 2 — no adjacent space: allocate new block, copy old data, free old block, return new address
Case 3 — fail: return NULL, old block untouched
```

---

### free() — Return Memory to the Heap

```cpp
free(arr);     // return Heap memory
arr = nullptr; // ALWAYS set to null after freeing!
```

**Memory Leak — forgetting free():**
```cpp
void leaky() {
    int *p = (int *)malloc(1000 * sizeof(int));
    // ... work ...
    return;   // forgot free! 4000 bytes lost forever!
}
// Call this 1000 times -> 4 MB permanently consumed!
```

**Rules for free():**

```cpp
// OK: free what malloc/calloc/realloc gave you
int *p = (int *)malloc(sizeof(int));
free(p);

// WRONG: don't free stack variables!
int x = 42;
free(&x);    // CRASH!

// WRONG: don't free twice!
free(p);
free(p);     // double free — undefined behavior!

// OK: free(nullptr) is safe (does nothing)
free(nullptr);
```

**Always pair free with nullptr assignment:**
```cpp
free(p);
p = nullptr;   // prevents dangling pointer bugs
```

---

### Complete Dynamic Array Example

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "How many numbers? ";
    cin >> n;

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == nullptr) { cout << "Failed!\n"; return 1; }

    for (int i = 0; i < n; i++) {
        cout << "Number " << i+1 << ": ";
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    free(arr);
    arr = nullptr;
    return 0;
}
```

---

### Summary: The Four Heap Functions

| Function | What it does | Initializes? |
|----------|-------------|-------------|
| `malloc(bytes)` | Allocate `bytes` bytes | No (garbage) |
| `calloc(n, size)` | Allocate `n * size` bytes | Yes (zeros) |
| `realloc(ptr, new_bytes)` | Resize existing block | Preserves old data |
| `free(ptr)` | Release memory back to heap | — |

**Three rules you must never forget:**
1. After `malloc/calloc` -> always check for `NULL`
2. After every allocation -> always call `free()` when done
3. After `free()` -> always set pointer to `nullptr`

---

## 13. Pointers and Strings

In C/C++, a string is a `char` array ending with `\0` (null terminator).

```cpp
char name[] = "Hello";
```

```
name
 |
 v
+-----+-----+-----+-----+-----+------+
| 'H' | 'e' | 'l' | 'l' | 'o' | '\0' |
+-----+-----+-----+-----+-----+------+
 [0]   [1]   [2]   [3]   [4]    [5]
 
Total: 6 bytes (5 chars + 1 null terminator)
```

---

### char[] vs char* — Important Difference

```cpp
char str1[] = "Hello";   // Stack — copies the string — MODIFIABLE
char *str2 = "Hello";    // Points to read-only memory — DO NOT MODIFY
```

```
char str1[] = "Hello":
+-----+-----+-----+-----+-----+------+
| 'H' | 'e' | 'l' | 'l' | 'o' | '\0' |   <- Stack (can modify)
+-----+-----+-----+-----+-----+------+

char *str2 = "Hello":
str2 --> +-----+-----+-----+-----+-----+------+
         | 'H' | 'e' | 'l' | 'l' | 'o' | '\0' |   <- Read-Only segment
         +-----+-----+-----+-----+-----+------+
```

```cpp
str1[0] = 'J';   // OK! -> "Jello"
str2[0] = 'J';   // CRASH! Segmentation fault — read-only memory!
```

**sizeof difference:**
```cpp
sizeof(str1)  // 6  — full array size (5 chars + null)
sizeof(str2)  // 8  — just the pointer size (64-bit system)
```

---

### Traversing a String with Pointers

```cpp
// Method 1: index-based
void print1(const char *str) {
    int i = 0;
    while (str[i] != '\0') { cout << str[i]; i++; }
}

// Method 2: pointer-based
void print2(const char *str) {
    while (*str != '\0') { cout << *str; str++; }
}

// Method 3: concise
void print3(const char *str) {
    while (*str) putchar(*str++);  // *str++ reads current, then advances
}
```

**How `*str++` works:**
```
str = "Hi"
Iter 1: *str = 'H' (read), str++ (advance) -> str points to 'i'
Iter 2: *str = 'i' (read), str++ (advance) -> str points to '\0'
Iter 3: *str = '\0' = 0 = false -> loop ends
```

---

### Implement strlen with Pointer Arithmetic

```cpp
int myStrLen(const char *str) {
    const char *start = str;   // remember start
    while (*str) str++;         // walk to the end
    return str - start;         // pointer subtraction = number of elements
}
```

---

### Array of Strings

```cpp
const char *days[] = {
    "Saturday", "Sunday", "Monday", "Tuesday",
    "Wednesday", "Thursday", "Friday"
};

for (int i = 0; i < 7; i++)
    cout << days[i] << endl;
```

```
days (array of char pointers):
+----------+
| days[0]  | --> "Saturday\0"
| days[1]  | --> "Sunday\0"
| days[2]  | --> "Monday\0"
| ...      |
+----------+
```

---

## 14. Pointers and Structures

### Pointer to a Struct

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Student {
    string name;
    int age;
    float gpa;
};
int main()
{
    Student s1 = {"Rafiq", 21, 3.85};
    Student *ptr = &s1;

    // Two equivalent ways to access members:
    cout << (*ptr).name << endl;   // dereference then dot
    cout << ptr->name  << endl;   // arrow operator (preferred)
    cout << ptr->age   << endl;
    cout << ptr->gpa   << endl;
    return 0;
}
```

**Why `->` instead of `(*ptr).`?**
```
*ptr.name    -> *(ptr.name)  ERROR: ptr has no member 'name'
(*ptr).name  -> correct (dereference first)
ptr->name    -> same thing, cleaner
```

---

### Pass Structure by Pointer (avoid copying)

```cpp
// SLOW: copies entire struct into function
void print1(Student s) {
    cout << s.name << endl;
}

// FAST: only passes 8-byte address
void print2(const Student *s) {
    cout << s->name << endl;
}

// Can also modify original:
void birthday(Student *s) {
    s->age++;    // changes the original struct
}

int main() {
    Student s = {"Rafiq", 21, 3.85};
    print2(&s);    // Rafiq
    birthday(&s);  // age -> 22
    print2(&s);    // Rafiq (age now 22)
}
```

---

### Dynamic Struct (malloc)

```cpp
Student *s2 = (Student *)malloc(sizeof(Student));
if (s2) {
    s2->name = "Karim";
    s2->age  = 22;
    s2->gpa  = 3.92;
    cout << s2->name << " " << s2->age << endl;
    free(s2);
    s2 = nullptr;
}
```

### Dynamic Array of Structs

```cpp
int n = 3;
Student *students = (Student *)malloc(n * sizeof(Student));
// access: students[0].name, students[1].age, etc.
free(students);
students = nullptr;
```

---

## 15. Self-Referential Structure — Linked List Intro

A struct can contain a pointer to its **own type**. This is the foundation of Linked Lists, Trees, and Graphs.

```cpp
struct Node {
    int data;
    Node *next;   // pointer to the same type!
};
```

**Why pointer, not a direct Node member?**
```
struct Node { int data; Node next; }   // IMPOSSIBLE — infinite size!
struct Node { int data; Node *next; }  // OK — pointer is always 8 bytes
```

---

### Create and Traverse a Linked List

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Node {
    int data;
    Node *next;
};
int main()
{
    Node *n1 = (Node *)malloc(sizeof(Node));
    Node *n2 = (Node *)malloc(sizeof(Node));
    Node *n3 = (Node *)malloc(sizeof(Node));

    n1->data = 10;  n1->next = n2;
    n2->data = 20;  n2->next = n3;
    n3->data = 30;  n3->next = nullptr;

    Node *head = n1;   // keep track of the start
```

```
head
 |
 v
+----+----+    +----+----+    +----+------+
| 10 | *--+--> | 20 | *--+--> | 30 | NULL |
+----+----+    +----+----+    +----+------+
  n1              n2              n3
```

```cpp
    // Traverse
    Node *cur = head;
    while (cur != nullptr) {
        cout << cur->data;
        if (cur->next) cout << " -> ";
        cur = cur->next;
    }
    cout << " -> NULL" << endl;
    // Output: 10 -> 20 -> 30 -> NULL

    // Free — must traverse, save next before freeing!
    cur = head;
    while (cur != nullptr) {
        Node *temp = cur->next;  // save next BEFORE freeing current
        free(cur);
        cur = temp;
    }
    head = nullptr;
    return 0;
}
```

**Why save next before freeing?**
```
Without temp:
free(n1) -> n1 gone -> n1->next? can't access! LOST!

With temp:
temp = n1->next  (save n2)
free(n1)         (n1 gone, but we have temp=n2)
cur = temp       (we're at n2, safe!)
```

---

## 16. Common Mistakes and Debugging Tips

### Mistake 1 — Uninitialized (Wild) Pointer

```cpp
int *p;          // garbage address — points anywhere
*p = 42;         // CRASH or silent corruption!

// Fix:
int *p = nullptr;    // intentionally "points nowhere"
int *p = &someVar;   // points to known valid address
```

---

### Mistake 2 — Dangling Pointer (3 types)

**Type 1: Using pointer after free()**
```cpp
int *p = (int *)malloc(sizeof(int));
free(p);
cout << *p;   // DANGER — freed memory!

// Fix:
free(p);
p = nullptr;  // now *p crashes immediately -> easier to debug
```

**Type 2: Returning pointer to local variable**
```cpp
int* bad() {
    int x = 42;
    return &x;   // x destroyed after return!
}
// Fix: use static int x or malloc
```

**Type 3: Pointer outlives its scope**
```cpp
int *p;
{
    int x = 42;
    p = &x;
}   // x destroyed here
cout << *p;   // dangling! x is gone
```

---

### Mistake 3 — NULL Pointer Dereference

```cpp
int *p = nullptr;
*p = 42;   // Segmentation Fault!

// Fix: always check before dereferencing
if (p != nullptr) {
    *p = 42;
}
```

---

### Mistake 4 — Memory Leak

```cpp
// LEAK: malloc without free
for (int i = 0; i < 10000; i++) {
    int *p = (int *)malloc(4000);
    // ... no free!
}
// 40 MB permanently consumed!

// Fix: free inside the loop
for (int i = 0; i < 10000; i++) {
    int *p = (int *)malloc(4000);
    // ... use p ...
    free(p);
}
```

**Sneaky leak — re-assigning before freeing:**
```cpp
int *p = (int *)malloc(sizeof(int));
p = (int *)malloc(sizeof(int));   // LEAK! first block's address is gone!

// Fix:
free(p);       // free first
p = (int *)malloc(sizeof(int));   // then reallocate
```

---

### Mistake 5 — Double Free

```cpp
free(p);
free(p);   // double free -> undefined behavior!

// Fix:
free(p);
p = nullptr;
free(p);   // free(nullptr) is safe -> does nothing
```

---

### Mistake 6 — Freeing a Stack Variable

```cpp
int x = 42;
free(&x);   // CRASH! x is on the Stack, not the Heap!

// Rule: only free() pointers returned by malloc/calloc/realloc
```

---

### Mistake 7 — Array Out of Bounds

```cpp
int *arr = (int *)malloc(5 * sizeof(int));
arr[5]    = 100;   // DANGER! valid indices: 0-4
arr[-1]   = 200;   // DANGER!
arr[1000] = 42;    // random memory corruption!

// C/C++ has no bounds checking — YOU are responsible!
```

---

### Segfault Causes Quick Reference

| Cause | Example |
|-------|---------|
| NULL pointer dereference | `int *p = nullptr; *p = 42;` |
| Freed memory access | `free(p); *p = 42;` |
| Uninitialized pointer | `int *p; *p = 42;` |
| Array out of bounds | `arr[1000] = 42;` |
| Modifying string literal | `char *s = "Hi"; s[0] = 'B';` |
| Stack overflow | Infinite/deep recursion |

---

### Debugging Tips

- Print pointer values before a crash: `printf("p = %p\n", p);`
- If you get a segfault, first ask: "Is any pointer NULL or uninitialized?"
- Use Valgrind (Linux): `valgrind ./program` — catches leaks and invalid accesses
- Count your malloc/free pairs — every malloc must have exactly one free
- Draw memory diagrams when logic gets complex

---

## 17. Best Practices Checklist

| Rule | Why |
|------|-----|
| Initialize every pointer (NULL or valid address) | Prevents wild pointer crashes |
| Check for NULL after malloc/calloc | malloc can fail |
| Call free() when done with Heap memory | Prevents memory leaks |
| Set pointer to nullptr after free() | Prevents dangling pointer bugs |
| Use temp pointer with realloc() | Prevents losing data on failure |
| Never return pointer to local variable | Local var dies with function |
| Free inner allocations before outer ones (2D arrays) | Prevents losing inner addresses |
| Use `const char *` for strings you won't modify | Prevents accidental modification |
| Use `->` for struct/class pointer member access | Cleaner than `(*ptr).member` |
| Never free a Stack variable | Stack is managed automatically |

---

## Quick Symbol Reference

| Symbol | Context | Meaning |
|--------|---------|---------|
| `&x` | On a variable | Address of x |
| `*` in declaration (`int *p`) | Type declaration | "p is a pointer" |
| `*p` | In expression | Dereference p (value at p's address) |
| `**p` | In expression | Dereference twice |
| `p->member` | Struct pointer | Same as `(*p).member` |
| `p + 1` | Pointer arithmetic | Next element (moves by sizeof type) |
| `p2 - p1` | Two pointers | Number of elements between them |
| `nullptr` / `NULL` | Initialization | "Points to nothing" (safe state) |

---

*Happy coding, and good luck with your interviews!*
