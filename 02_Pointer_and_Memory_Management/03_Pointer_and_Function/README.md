# Pointers and Functions


---

## Table of Contents
1. [Pointers and Functions (The Photocopy Analogy)](#1-pointers-and-functions)
2. [Pass by Reference (Changing the Original)](#2-pass-by-reference--changing-the-original)
3. [The Swap Function](#3-swap-function--classic-example)
4. [Function Pointers (Functions as Addresses)](#4-function-pointer--functions-also-have-addresses)
5. [Why use Function Pointers? (Callbacks)](#5-why-is-a-function-pointer-needed)
6. [The Calculator & QSort Examples](#the-calculator--callback-pattern)
7. [Returning a Pointer (The Dangling Pointer Trap)](#6-returning-a-pointer-from-a-function--be-careful)

---

## 1. Pointers and Functions

You already know how to pass arguments to a function, like this:

```c
void printDouble(int num) {
    printf("%d\n", num * 2);
}

int main() {
    int x = 42;
    printDouble(x);   // The value of x (42) is sent to the function
    return 0;
}
```

Here, the value of `x` (42) goes into the variable `num` in the function. But what is actually happening? `num` is not `x` itself; it is a **photocopy** of `x`.

Because it's a copy, if you change `num` inside the function, the original `x` in `main` remains unchanged:

```c
void changeValue(int num) {
    num = 100;  // This only changes the copy!
}

int main() {
    int x = 42;
    changeValue(x);
    printf("x = %d\n", x);  // Output: 42 (Unchanged!)
    return 0;
}
```

**Memory Logic:**
```text
    In main:           In function:
    ┌──────┐           ┌──────┐
    │  42  │ --Copy--> │  42  │ -- Turned into 100
    └──────┘           └──────┘
       x                 num (Separate memory box!)
```

This behavior is called **Pass by Value**.

---

## 2. Pass by Reference — Changing the Original

If you want the function to change the *original* variable, don't send the value — **send the address!**

**Analogy:**
- **Pass by Value:** You give your friend a photocopy of a page from your notebook. Whatever they scribble on it doesn't affect your original notebook.
- **Pass by Reference:** You tell your friend, "My notebook is in the second drawer; go write in it." Now, any changes they make are directly in your original notebook!

In programming, that "drawer" is the memory address.

```c
void changeValue(int *ptr) {
    // 'ptr' is a pointer — it receives an address
    // '*ptr' means go to that address and change the value
    *ptr = 100;
}

int main() {
    int x = 42;
    changeValue(&x);   // &x = Sending the address of x
    printf("x = %d\n", x);  // Output: 100
    return 0;
}
```

**Line-by-Line Logic:**

- **Step 1: `int x = 42;`**  
  A box named `x` is created in memory, and the value `42` is stored inside.
  ```text
        ┌──────┐
        │  42  │   x (address: 0x7FF3A)
        └──────┘
  ```

- **Step 2: `changeValue(&x);`**  
  We send the address of `x` (`0x7FF3A`) to the function. Inside the function, the pointer `ptr` now holds this address.
  ```text
        ptr = 0x7FF3A  ->  "I know exactly where 'x' is!"
  ```

- **Step 3: `*ptr = 100;`**  
  The function goes to the address pointed to by `ptr` (`0x7FF3A`) and writes `100` there.  
  This directly changes the original value of `x`.
  ```text
        ┌──────┐
        │ 100  │   x (address: 0x7FF3A) ← CHANGED!
        └──────┘
  ```

- **Step 4: `printf("x = %d\n", x);`**  
  `x` now contains `100`.  
  **Output:** `100`

**Key Difference:** In Pass by Value, we sent a copy, so the original was safe. In Pass by Reference, we sent the address, so we went directly to the original "house" and changed the furniture!

---

## 3. Swap Function — Classic Example

Using Pass by Reference is the only way to swap two variables effectively in C:

```c
void swap(int *a, int *b) {
    int temp = *a;   // Store value at 'a' in temp
    *a = *b;         // Put value from 'b' into 'a'
    *b = temp;       // Put temp value into 'b'
}

int main() {
    int x = 10, y = 20;
    swap(&x, &y);    // Passing addresses
    printf("x = %d, y = %d\n", x, y);  // x = 20, y = 10
    return 0;
}
```

**Trace:**
- **Before**: `x = 10, y = 20`
- **Inside Swap**:
    - `temp = *a = 10`
    - `*a = *b = 20` (x becomes 20)
    - `*b = temp = 10` (y becomes 10)
- **After**: `x = 20, y = 10` (Swapped!)

---

## 4. Function Pointer — Functions also have Addresses!

Pointers aren't just for variables and arrays. Even **Functions** have memory addresses! The compiled code of a function is stored in memory, and you can point a pointer to it.

### How to find a Function's Address:
```c
#include <stdio.h>

int add(int a, int b) { return a + b; }

int main() {
    printf("Add function address: %p\n", add); 
    // Output: 0x4005B6 (Function name is the address!)
    return 0;
}
```

### Declaring a Function Pointer
You must specify the **Return Type** and the **Parameters** of the function it points to.

```c
int (*func_ptr)(int, int);
```
**Breakdown:**
- `int`: What the function returns.
- `(*func_ptr)`: The name of our pointer (must have `*` and `()`).
- `(int, int)`: The parameters the function takes.

**Usage:**
```c
int add(int a, int b) { return a + b; }
int (*func_ptr)(int, int);
func_ptr = add; // Signature must match!
```
> ⚠️ **Warning:** Parentheses around `(*func_ptr)` are required. Without them, it becomes a function declaration that returns a pointer!

---

## 5. Why is a Function Pointer needed?

Why use a pointer when you can call `add(3, 4)` directly? The magic happens when you want to decide *which* function to call while the program is already running (Runtime).

### The Calculator & Callback Pattern
Instead of using messy `if-else` blocks inside a calculator, we can pass the operation *as a function pointer*.

```c
// ✅ Clean approach — takes a function pointer as a parameter
int calculate(int a, int b, int (*op)(int, int)) {
    return op(a, b);
}
```
Now `calculate` has no idea whether it is adding, subtracting, or multiplying — it just knows: "I will be given a function, and I will call it." Which function? You will decide!

```c
int main() {
    printf("%d\n", calculate(10, 5, add));   // 15
    printf("%d\n", calculate(10, 5, sub));   // 5
    printf("%d\n", calculate(10, 5, mul));   // 50
    return 0;
}
```

**Step-by-step for `calculate(10, 5, add)`**:
1.  **Step 1**: `calculate` is called with `a=10, b=5, op=add`. The `op` pointer now points to the `add` function.
2.  **Step 2**: `return op(a, b);` is executed. Since `op` points to `add`, it's essentially calling `add(10, 5)`.
3.  **Step 3**: `add(10, 5)` returns `15`.
4.  **Result**: `15` is returned to `main`.

### The Callback Pattern
This pattern is called a **Callback** in programming — you are "giving" one function to another function so it can be called back later.

The biggest advantage? If you want to add a new operation, you only need to write the new function; you **never** have to change the `calculate` function again!

**Adding new features without changing the original code:**
```c
int divide(int a, int b) { return a / b; }
int modulo(int a, int b) { return a % b; }

printf("%d\n", calculate(10, 5, divide));  // 2
printf("%d\n", calculate(10, 5, modulo));  // 0
```
This is dynamic! `calculate` remains exactly the same while its capabilities expand!

### The C `qsort` Function
C's built-in sorting function, `qsort`, uses this same callback pattern:

```c
#include <stdio.h>
#include <stdlib.h>

int ascending(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int descending(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int arr[] = {50, 10, 40, 20, 30};
    int n = 5;

    // Use ascending callback
    qsort(arr, n, sizeof(int), ascending); // {10, 20, 30, 40, 50}

    // Use descending callback
    qsort(arr, n, sizeof(int), descending); // {50, 40, 30, 20, 10}
}
```
The logic for `qsort` stays the same; the sorting behavior changes based on which *comparison function* you pass.

---

## 6. Returning a Pointer from a Function — Be Careful!

Returning a pointer is possible, but beware of the **Dangling Pointer** trap.

```c
// ❌ DANGEROUS!
int* badFunction() {
    int x = 42;
    return &x;  // Returning the address of a local variable
}
```

**Analogy:**
Think of a function as a **Temporary Office**. `x` is a file inside that office. While the function is running, the office is open and the file exists. When the function ends, the office is CLOSED and everything inside is shredded! If you return the address of `x`, you are giving someone a key to a shredded folder.

```text
    badFunction() is running:
    ┌──────┐
    │  42  │   x (address: 0x7FF3A)  ← File exists
    └──────┘

    badFunction() ends:
    ┌──────┐
    │ ???? │   (address: 0x7FF3A)  ← File was shredded! (Garbage)
    └──────┘
```

**The result:**
```c
int *p = badFunction();
printf("%d", *p);   // ❌ Undefined Behavior! Random crash or garbage data.
```

If you need a pointer to survive after the function ends, you must use **`static`** or **Dynamic Memory (malloc)**, which we learn in Part 3.

> ⚠️ **Warning:** Never return a pointer to a local variable. Local variables are destroyed when the function returns. The resulting pointer is a "Dangling Pointer" pointing at invalid memory.

---
