# C Pointers — Part 2: Pointers and Functions

Let’s learn like a story, without any fear! 

This is **Part 2** — focus on how Pointers work with Functions, Pass by Value/Reference, and the powerful Function Pointer.

---

## 1. Pointers and Functions

You already know how to send arguments to a function, right? Like this:

```c
void printDouble(int num) {
    printf("%d\n", num * 2);
}

int main() {
    int x = 42;
    printDouble(x);   // The value of x (42) is going to the function
    return 0;
}
```

Here, the value `42` from `x` goes into the variable `num` inside the function. But think about it — what is actually moving? Not `x` itself, but a **copy** of `x`. You can think of `num` as a **photocopy** of the original `x`.

Because it's just a photocopy, if you change `num` inside the function, the original `x` remains untouched:

```c
void changeValue(int num) {
    num = 100;  // This only changes the COPY!
}

int main() {
    int x = 42;
    changeValue(x);
    printf("x = %d\n", x);  // Output: 42 (No change!)
    return 0;
}
```

**Memory Visualization:**
```text
    Inside main:           Inside function:
    ┌──────┐               ┌──────┐
    │  42  │ -- Copy ->    │  42  │ -- Turned into 100
    └──────┘               └──────┘
       x                     num (Different storage!)
    
    Original 'x' stays safe and unchanged.
```

This behavior is called **Pass by Value**. The function gets a copy of the value, and the original variable stays isolated.

---

## 2. Pass by Reference — Changing the Original

What if you *want* the function to change the original variable? In that case, don't send the value — **send the address!**

**Analogy:**
- **Pass by Value:** You give your friend a photocopy of your notebook. Whatever they scribble on the photocopy doesn't affect your original notebook.
- **Pass by Reference:** You tell your friend, "My notebook is in the second drawer of my desk; go write in it." Your friend goes directly to the original notebook and writes in it!

In programming, that "drawer" is the **memory address**. If you give the function the address, it can go straight to that memory location and change the value.

### The Syntax of Pass by Reference:

```c
void changeValue(int *ptr) {
    // 'ptr' is a pointer — it will receive an address
    // '*ptr' means go to that address and change the value
    *ptr = 100;
}
```

By using `int *ptr`, the function says, "I am ready to receive the address of an integer."

### Complete Program:

```c
#include <stdio.h>

void changeValue(int *ptr) {
    *ptr = 100;
}

int main() {
    int x = 42;
    changeValue(&x);   // &x = Sending the address of x
    printf("x = %d\n", x);  // Output: 100
    return 0;
}
```

**Step-by-Step Breakdown:**
1.  **`int x = 42;`**: A box named `x` is created containing `42` at address `0x7FF3A`.
2.  **`changeValue(&x);`**: We send the address `0x7FF3A` to the function. Now `ptr` inside the function holds `0x7FF3A`.
3.  **`*ptr = 100;`**: The function goes to address `0x7FF3A` and writes `100` directly into that box.
4.  **Result**: `x` is now `100`.

---

## 3. Swap Function — The Classic Example

The most common use of Pass by Reference is swapping two variables:

```c
void swap(int *a, int *b) {
    int temp = *a;   // Store the value at address 'a' in temp
    *a = *b;         // Put value from address 'b' into address 'a'
    *b = temp;       // Put temp value into address 'b'
}

int main() {
    int x = 10, y = 20;
    swap(&x, &y);    // Send addresses of both
    printf("x = %d, y = %d\n", x, y);  // x = 20, y = 10
    return 0;
}
```

**Trace:**
- **Before**: `x = 10`, `y = 20`.
- **Inside swap**:
    - `temp = *a = 10`
    - `*a = *b = 20` (Original `x` becomes `20`)
    - `*b = temp = 10` (Original `y` becomes `10`)
- **After**: `x = 20`, `y = 10`.

> 💡 **Pro Tip:** If a function only needs to read a value, use a normal variable. If the function needs to modify the original variable, use a pointer to pass the address.

---

## 4. Function Pointer — Functions Have Addresses Too!

You know that variables and arrays have memory addresses. But did you know that **functions** also live at specific addresses in memory?

When you write a function, its compiled code is stored somewhere in RAM. That location has an address, and you can store that address in a **Function Pointer**.

### How to see a Function's Address:

```c
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    printf("Address of 'add' function: %p\n", add);
    // Output: 0x4005B6 (or something similar)
    return 0;
}
```

Just like an array's name represents its starting address, a **function's name** (without parentheses `()`) represents its address!

### Declaring a Function Pointer

The syntax for declaring a function pointer is a bit tricky. You have to tell the pointer what kind of function it is pointing to — what it returns and what it takes.

**Syntax Example:**
```c
int (*func_ptr)(int, int);
```

**Breakdown in 3 parts:**
1.  **`int`**: What does the function return? (Return type)
2.  **`(*func_ptr)`**: What is the name of the pointer? (The `*` indicates it is a pointer).
3.  **`(int, int)`**: What parameters does the target function take?

**Assigning a Function:**
```c
int add(int a, int b) { return a + b; }

int (*func_ptr)(int, int);   // Declaration
func_ptr = add;               // Storing address of 'add'
```

> ⚠️ **Warning:** The parentheses around `(*func_ptr)` are **mandatory**. If you write `int *func_ptr(int, int)`, you are declaring a function that returns an integer pointer, which is completely different!

### Calling a Function via Pointer:

```c
#include <stdio.h>

int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

int main() {
    int (*operation)(int, int);

    operation = add;
    printf("Add: %d\n", operation(3, 4));       // 7

    operation = multiply;
    printf("Multiply: %d\n", operation(3, 4));  // 12

    return 0;
}
```

Same pointer, different functions! This is highly dynamic.

---

## 5. Why do we need Function Pointers? (Callbacks)

You might ask, "Why not just call `add(3, 4)` directly?"
The power comes when you don't know *which* function to call until the program is actually running (runtime).

### The "Calculator" Problem:
Imagine a `calculate` function that takes two numbers and an **operation**. Without function pointers, you'd use a messy `if-else` or `switch` block:

```c
// ❌ Messy approach:
int calculate(int a, int b, char choice) {
    if (choice == '+') return add(a, b);
    else if (choice == '*') return multiply(a, b);
    // Adding new operations means modifying this code every time...
}
```

### The "Clean" Approach with Function Pointers:
```c
// ✅ Elegant: The function is passed as a parameter!
int calculate(int a, int b, int (*op)(int, int)) {
    return op(a, b); // Just call whatever function was passed
}

int main() {
    printf("%d\n", calculate(10, 5, add));      // 15
    printf("%d\n", calculate(10, 5, multiply)); // 50
    return 0;
}
```

This pattern is called a **Callback**. You give a function to another function to call later.
C's built-in `qsort` (quick sort) works exactly like this — you pass it a "comparison" function to decide the sorting order.

---

## 6. Returning a Pointer — Be Careful!

A function can return a pointer, but there is a dangerous trap called the **Dangling Pointer**.

```c
// ❌ TERRIBLE MISTAKE!
int* badFunction() {
    int x = 42;
    return &x;  // Returning address of a local variable!
}
```

**Why is this wrong?**
Think of a function as a temporary office. `x` is a file in that office. When the function ends, the office is closed and the file is shredded! If you return the address of `x`, you are giving someone a key to a room that no longer exists.

- **Stack during function**: `x` exists at `0x7FF3A`.
- **Stack after return**: `0x7FF3A` is now **garbage** or reused by something else.

> ⚠️ **Golden Rule:** Never return a pointer to a local variable. Local variables are destroyed when the function returns. If you need a pointer to survive, you must use the `static` keyword or `malloc` (dynamic memory), which we cover in **Part 3**!

---
