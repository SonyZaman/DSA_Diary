# Pointers 



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
   arr   arr+1   arr+2   arr+3   arr+4
    |      |      |       |       |
    v      v      v       v       v
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



---


