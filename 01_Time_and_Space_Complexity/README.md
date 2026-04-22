# Time & Space Complexity 



---

## Table of Contents

1. [What is Time Complexity?](#1-what-is-time-complexity)
2. [Big O and Other Notations](#2-big-o-and-other-notations)
3. [Rules for Big O Notation](#3-rules-for-big-o-notation)
4. [O(1) — Constant Time](#4-o1--constant-time)
5. [O(N) — Linear Time](#5-on--linear-time)
6. [O(N + M) — Two Independent Inputs](#6-on--m--two-independent-inputs)
7. [O(N^2) and O(N^3) — Quadratic & Cubic](#7-on2-and-on3--quadratic--cubic)
8. [O(log N) — Logarithmic Time & Proof](#8-olog-n--logarithmic-time--proof)
9. [O(N) Nested Loop Practice & Proof (Geometric Series)](#9-on-nested-loop-practice--proof-geometric-series)
10. [What is Space Complexity?](#10-what-is-space-complexity)
11. [O(1) Space Complexity](#11-o1-space-complexity)
12. [O(N) Space Complexity](#12-on-space-complexity)
13. [O(N^2) Space Complexity](#13-on2-space-complexity)
14. [Checking Primality — O(N), O(N/2), O(sqrt(N))](#14-checking-primality--on-on2-osqrtn)
15. [O(N log N) Time Complexity](#15-on-log-n-time-complexity)
16. [Recursion — O(N) Time & O(N) Space (Factorial)](#16-recursion--on-time--on-space-factorial)
17. [Recursion — O(2^N) Time & O(N) Space (Fibonacci)](#17-recursion--o2n-time--on-space-fibonacci)
18. [Recursion — O(N^2) Time & O(N^2) Space](#18-recursion--on2-time--on2-space)
19. [O(N log N) — Harmonic Series Proof](#19-on-log-n--harmonic-series-proof)
20. [O(N) — Decreasing Inner Loop Practice & Proof (Geometric Series)](#20-on--decreasing-inner-loop-practice--proof-geometric-series)
21. [Big O, Big Theta, Big Omega — Advanced Notations](#21-big-o-big-theta-big-omega--advanced-notations)
22. [Amortized Complexity](#22-amortized-complexity)
23. [NP-Complete & NP-Hard — Why Some Problems Are "Impossible"](#23-np-complete--np-hard--why-some-problems-are-impossible)
24. [Algorithm & Data Structure Complexity Table](#24-algorithm--data-structure-complexity-table)
25. [The n-to-Complexity Quick Decision Table](#25-the-n-to-complexity-quick-decision-table)

---

## 1. What is Time Complexity?

**Time complexity** represents how the **runtime of an algorithm grows** with the input size `n`.

- It does **not** measure actual clock time (that depends on machine speed, language, etc.).
- It measures **how the number of operations scales** as `n` grows.
- In interviews and competitive programming, knowing time complexity ensures your solution runs within the time limit (usually **1-2 seconds**).

**Why it matters:**
- An O(N^2) solution might pass for `N = 1,000` but fail for `N = 100,000`.
- Understanding complexity helps you choose the right algorithm before writing a single line of code.

---

## 2. Big O and Other Notations

| Notation | Name | Meaning |
|----------|------|---------|
| **O(f(n))** | Big O | **Worst-case** — upper bound on growth |
| **Theta(f(n))** | Big Theta | **Average-case** — tight bound (both upper & lower) |
| **Omega(f(n))** | Big Omega | **Best-case** — lower bound on growth |

> **Interview Rule:** When someone says "time complexity", they almost always mean **Big O (worst-case)**. Always analyze and report Big O unless asked otherwise.

---

## 3. Rules for Big O Notation

### Rule 1 — Ignore Constants
Constant multipliers are dropped because they don't affect the *growth rate*.

```
O(2N)     -> O(N)
O(500)    -> O(1)
O(3N^2)   -> O(N^2)
O(N/2)    -> O(N)
```

### Rule 2 — Drop Non-Dominant Terms
Keep only the fastest-growing term.

```
O(N + N^2)       -> O(N^2)
O(N^2 + log N)   -> O(N^2)
O(N + 1000)      -> O(N)
O(2^N + N^3)     -> O(2^N)
```

### Why These Rules Work
As `n -> infinity`, the dominant term overwhelms all others. For example, when `n = 1,000,000`:
- `N^2 = 10^12`
- `N  = 10^6`

`N` is completely negligible compared to `N^2`.

---

## 4. O(1) — Constant Time

An algorithm is **O(1)** when it performs a **fixed number of operations** regardless of input size.

### Example 1 — Formula-Based Sum
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int sum = (n * (n + 1)) / 2;  // Always 1 operation, no matter how big n is
    cout << sum << endl;
    return 0;
}
```
**Why O(1)?** No loop. The formula always takes exactly 3 operations (multiply, add, divide).

### Example 2 — Fixed-Size Loop
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    for (int i = 0; i < 1000000; i++) {
        // some operation
    }
    return 0;
}
```
**Why O(1)?** The loop runs exactly **1,000,000** times — a **constant** number. It does NOT grow with any input. So ignoring the constant: O(1,000,000) -> **O(1)**.

> **Key Insight:** If the number of iterations is fixed (not dependent on any input variable), it's O(1).

---

## 5. O(N) — Linear Time

An algorithm is **O(N)** when the number of operations **grows linearly** with the input size.

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {  // Runs exactly N times
        sum += i;
    }
    cout << sum << endl;
    return 0;
}
```
**Why O(N)?** The loop runs `n` times. Double `n`, double the work.

---

## 6. O(N + M) — Two Independent Inputs

When you have **two separate loops over two different variables**, the complexity is **O(N + M)**.

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    int a[n], b[m];

    for (int i = 0; i < n; i++) cin >> a[i];         // O(N)
    for (int i = 0; i < m; i++) cin >> b[i];         // O(M)

    int c[n + m];
    for (int i = 0; i < n + m; i++) {                 // O(N + M)
        if (i < n) c[i] = a[i];
        else       c[i] = b[i - n];
    }

    for (int i = 0; i < n + m; i++) cout << c[i] << " ";  // O(N + M)
    return 0;
}
```
**Total:** O(N) + O(M) + O(N+M) + O(N+M) = **O(N + M)**

> **Important:** You **cannot** simplify O(N + M) to O(N) unless you know M <= N. If they are truly independent, keep both.

---

## 7. O(N^2) and O(N^3) — Quadratic & Cubic

### O(N^2) — Two Nested Loops

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {        // Runs N times
        for (int j = 0; j < m; j++) {    // Runs M times per outer iteration
            cout << i << " " << j << endl;
        }
    }
    return 0;
}
```
**Total operations:** N * M = **O(N * M)**  
If `N == M`, this becomes **O(N^2)**.

### O(N^3) — Three Nested Loops

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n, m, o;
    cin >> n >> m >> o;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < o; k++) {
                cout << i << " " << j << " " << k << endl;
            }
        }
    }
    return 0;
}
```
**Total operations:** N * M * O = **O(N * M * O)**  
If all are equal: **O(N^3)**

> **Rule of Thumb:** Each additional **nested loop** over the same variable adds another power of N.

---

## 8. O(log N) — Logarithmic Time & Proof

An algorithm is **O(log N)** when it **halves (or cuts by a fraction) the problem size** each step.

### Binary Search Example
```cpp
int bsearch(int a[], int n, int tar) {
    int l = 0, r = n - 1, mid;
    while (l < r) {
        mid = (l + r) / 2;
        if (a[mid] == tar) return mid;
        if (a[mid] > tar)  r = mid - 1;
        else               l = mid + 1;
    }
    return -1;
}
```

### Mathematical Proof

Each iteration cuts the search space in half:

```
N -> N/2 -> N/4 -> ... -> 1
```

Which equals:
```
N/2^0 -> N/2^1 -> N/2^2 -> ... -> N/2^K
```

We stop when `N/2^K = 1`:
```
2^K = N
log_2(2^K) = log_2(N)
K = log_2(N)        [since log_a(a^x) = x]
```

So after **K = log_2(N)** steps, the search is done -> **O(log N)** ✓

---

## 9. O(N) Nested Loop Practice & Proof (Geometric Series)

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i *= 2) {       // Outer: log_2(N) times
        for (int j = 1; j <= i; j++) {       // Inner: runs i times
            cout << j << endl;
        }
    }
    return 0;
}
```

### Proof

| Outer `i` | Inner loop runs |
|-----------|----------------|
| 1         | 1              |
| 2         | 2              |
| 4         | 4              |
| 8         | 8              |
| ...       | ...            |
| N         | N              |

Total iterations form a **geometric series**:
```
S = 1 + 2 + 4 + 8 + ... + N
```
Where:
- First term `a = 1`
- Common ratio `r = 2`
- Number of terms `k = log_2(N)`

Using the geometric series formula `S = a * (r^k - 1) / (r - 1)`:
```
S = 1 * (2^log_2(N) - 1) / (2 - 1)
  = 2^log_2(N) - 1
  = N - 1          [since 2^log_2(N) = N]
```

Ignoring constants -> **O(N)** ✓

---

## 10. What is Space Complexity?

**Space complexity** = extra memory (auxiliary space) used by an algorithm, **excluding** the input itself.

| Type | Definition |
|------|-----------|
| **Input Space** | Memory for the input data (e.g., array of size N) |
| **Auxiliary Space** | Extra memory used by the algorithm (temp variables, new arrays, recursion stack) |
| **Space Complexity** | = Auxiliary Space only |

> **Why exclude input space?** Because you can't avoid storing the input — it's given to you. We care about how much *extra* memory your algorithm needs beyond that.

---

## 11. O(1) Space Complexity

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int a[n];                          // Input space (NOT counted)
    for (int i = 0; i < n; i++) cin >> a[i];
    int s = 0;                         // 1 variable — O(1) auxiliary space
    for (int i = 0; i < n; i++) s += a[i];
    cout << s << endl;
    return 0;
}
```
**Why O(1) space?** Only uses 1 extra variable `s` regardless of `n`.

---

## 12. O(N) Space Complexity

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    int b[n];                          // Extra array of size N -> O(N) space
    for (int i = 0; i < n; i++) b[i] = a[i];
    for (int i = 0; i < n; i++) cout << b[i] << " ";
    return 0;
}
```
**Why O(N) space?** We create a new array `b` of size `n`. The extra memory grows linearly with `n`.

---

## 13. O(N^2) Space Complexity

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    int a[n][n];                       // N*N 2D array -> O(N^2) space
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cout << a[i][j] << " ";
        cout << endl;
    }
    return 0;
}
```
**Why O(N^2) space?** The 2D array has `n * n = n^2` cells.

---

## 14. Checking Primality — O(N), O(N/2), O(sqrt(N))

### Approach 1 — O(N)
```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i < n; i++) {       // Checks up to n-1
        if (n % i == 0) return false;
    }
    return true;
}
```

### Approach 2 — Still O(N)
```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= n / 2; i++) {   // Checks up to n/2 (half the work, but still linear)
        if (n % i == 0) return false;
    }
    return true;
}
```
> Both are O(N). Cutting to `n/2` drops the constant but not the complexity class.

### Approach 3 — O(sqrt(N)) — Optimal
```cpp
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {   // Only checks up to sqrt(n)
        if (n % i == 0) return false;
    }
    return true;
}
```
**Why O(sqrt(N))?** If `n` has a factor > sqrt(n), then its paired factor must be < sqrt(n) — so we would have already found it. We only need to check up to sqrt(n).

**Space:** O(1) for all three — only a loop variable, no extra memory.

---

## 15. O(N log N) Time Complexity

### Classic Pattern — Linear x Logarithmic
```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {        // O(N) — runs N times
        for (int j = 1; j <= n; j *= 2) { // O(log N) — j doubles each step
            cout << j << endl;
        }
    }
    return 0;
}
```
**Total:** N * log N = **O(N log N)**

> This is the complexity of the best comparison-based sorting algorithms: Merge Sort, Quick Sort (average), Heap Sort.

---

## 16. Recursion — O(N) Time & O(N) Space (Factorial)

```cpp
#include <bits/stdc++.h>
using namespace std;
int fact(int n) {
    if (n == 0) return 1;
    return n * fact(n - 1);
}
int main() {
    int n;
    cin >> n;
    cout << fact(n);
    return 0;
}
```

### Recursion Call Stack for fact(4):
```
fact(4) -> fact(3) -> fact(2) -> fact(1) -> fact(0)
                                                 |
                                            return 1
                                       return 1
                                  return 2
                             return 6
                        return 24
```

- **Time:** N recursive calls -> **O(N)**
- **Space:** N frames on the call stack simultaneously -> **O(N)**

> **Key:** Recursion always uses extra stack space — each active call occupies memory until it returns.

---

## 17. Recursion — O(2^N) Time & O(N) Space (Fibonacci)

```cpp
#include <bits/stdc++.h>
using namespace std;
int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}
int main() {
    int n;
    cin >> n;
    cout << fib(n) << endl;
    return 0;
}
```

### Recursion Tree for fib(4):
```
                    fib(4)
                  /        \
            fib(3)          fib(2)
           /      \         /    \
        fib(2)  fib(1)   fib(1)  fib(0)
        /    \
    fib(1)  fib(0)
```

- **Time:** At each level, calls roughly double -> **O(2^N)**
- **Space:** Maximum depth of the tree = N -> **O(N)** stack space

> **Warning:** Never use naive recursive Fibonacci for large N in production. Use memoization (O(N) time & space) or iterative DP (O(N) time, O(1) space).

---

## 18. Recursion — O(N^2) Time & O(N^2) Space

```cpp
#include <bits/stdc++.h>
using namespace std;
int fun(int n) {
    if (n == 0) return 0;
    int a[n];                            // Creates array of size n at each call
    for (int i = 0; i < n; i++) a[i] = i;
    return a[n - 1] + fun(n - 1);
}
int main() {
    int n;
    cin >> n;
    cout << fun(n) << endl;
    return 0;
}
```

### Analysis:
- `fun(n)` calls `fun(n-1)`, `fun(n-2)`, ..., `fun(0)` — N calls total.
- Each call creates an array: sizes N, N-1, N-2, ..., 1
- **Time:** `N + (N-1) + ... + 1 = N*(N+1)/2` -> **O(N^2)**
- **Space:** All frames on stack simultaneously have arrays: N + (N-1) + ... + 1 -> **O(N^2)**

---

## 19. O(N log N) — Harmonic Series Proof

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {           // Outer: runs N times
        for (int j = 1; j <= n / i; j++) {   // Inner: runs N/i times
            cout << j << endl;
        }
    }
    return 0;
}
```

### Proof

Total inner loop iterations:
```
S = N/1 + N/2 + N/3 + ... + N/N
  = N * (1 + 1/2 + 1/3 + ... + 1/N)
  = N * H(N)          [H(N) is the N-th Harmonic Number]
```

**Proof that H(N) = O(log N):**

When N = 100, group the harmonic series:
```
1                         = 1       < 1  (1 term)
1/2 + 1/3                 < 1       (2 terms)
1/4 + 1/5 + 1/6 + 1/7    < 1       (4 terms)
1/8 to 1/15               < 1       (8 terms)
1/16 to 1/31              < 1       (16 terms)
1/32 to 1/63              < 1       (32 terms)
1/64 to 1/100             < 1       (remaining)
```

Each group contributes < 1, and there are **log_2(N) groups** -> H(N) ≈ log_2(N)

Therefore:
```
S = N * log N  ->  O(N log N)  ✓
```

---

## 20. O(N) — Decreasing Inner Loop Practice & Proof (Geometric Series)

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
    int n;
    cin >> n;
    for (int i = n; i >= 1; i /= 2) {       // Outer: log_2(N) times, i = N, N/2, N/4...
        for (int j = 1; j <= i; j++) {       // Inner: runs i times
            cout << j << endl;
        }
    }
    return 0;
}
```

### Proof

| Outer `i` | Inner loop runs |
|-----------|----------------|
| N         | N              |
| N/2       | N/2            |
| N/4       | N/4            |
| ...       | ...            |
| 1         | 1              |

Total iterations form a **geometric series**:
```
S = N + N/2 + N/4 + N/8 + ... + 1
```
Where:
- First term `a = N`
- Common ratio `r = 1/2`
- Number of terms `k = log_2(N)`

Using the geometric series formula `S = a * (r^k - 1) / (r - 1)`:
```
S = N * ((1/2)^log_2(N) - 1) / ((1/2) - 1)
  = 2N * [1 - (1 / 2^log_2(N))]
```
Recall that `2^log_2(N) = N`, therefore:
```
S = 2N * [1 - (1/N)]
  = 2 * (N - 1)
  = O(N)              ✓
```

---

## 21. Big O, Big Theta, Big Omega — Advanced Notations

### Formal Definitions

| Notation | Mathematical Meaning | In Plain English |
|----------|----------------------|------------------|
| **O(g(n))** | Exists c, n_0 such that f(n) <= c*g(n) for all n >= n_0 | g(n) is an **upper bound** — worst it gets |
| **Omega(g(n))** | Exists c, n_0 such that f(n) >= c*g(n) for all n >= n_0 | g(n) is a **lower bound** — best it gets |
| **Theta(g(n))** | Both O(g(n)) AND Omega(g(n)) | g(n) is a **tight bound** — exact growth rate |

### Example: Merge Sort

| Notation | Value | Meaning |
|----------|-------|---------|
| O(N log N) | N log N | Even in worst case, won't be slower than N log N |
| Omega(N log N) | N log N | Even in best case, won't be faster than N log N |
| Theta(N log N) | N log N | Always exactly N log N — tight bound |

### Example: Bubble Sort

| Notation | Value | Meaning |
|----------|-------|---------|
| O(N^2) | N^2 | Worst case (reverse sorted) |
| Omega(N) | N | Best case (already sorted — just one pass) |
| Theta — | N/A | Not a tight bound since best != worst |

### Quick Memory Aid

```
Omega = Best case  (Omega -> "Optimistic")
O     = Worst case (O     -> "Oh no, worst scenario")
Theta = Tight case (Theta -> "THink of it as the True complexity")
```

---

## 22. Amortized Complexity

**Amortized complexity** is the **average cost per operation over a sequence of operations**, even if individual operations have varying costs.

### Classic Example: Dynamic Array (Vector)

When a `vector` is full and you call `push_back()`, it **doubles** its capacity and copies all elements — that one call costs O(N). But most `push_back()` calls cost O(1).

#### Analysis for N push_back() calls:

| Expansion at size | Copy cost |
|-------------------|-----------|
| 1 -> 2 | 1 |
| 2 -> 4 | 2 |
| 4 -> 8 | 4 |
| 8 -> 16 | 8 |
| ... | ... |
| N/2 -> N | N/2 |

Total copy cost = 1 + 2 + 4 + ... + N/2 = **N - 1** (geometric series)

Total cost for N calls = N (inserts) + N - 1 (copies) = **2N - 1**

**Amortized cost per call = (2N - 1) / N ≈ 2 -> O(1) amortized** ✓

> This is why we say `push_back` is **O(1) amortized**, not O(1) worst-case.

### Other Examples of Amortized Analysis:
- **Stack operations in certain algorithms** — each element is pushed/popped at most once.
- **Union-Find (path compression)** — nearly O(1) amortized per operation.

---

## 23. NP-Complete & NP-Hard — Why Some Problems Are "Impossible"

### Polynomial vs Exponential Time

**Polynomial time** (practical): O(N), O(N^2), O(N log N), O(N^k) for some fixed k.

**Exponential time** (impractical for large N): O(2^N), O(N!), O(N^N)

#### Concrete Impact (computer doing 10^8 ops/sec):

| N | O(N^2) | O(2^N) | O(N!) |
|---|--------|--------|-------|
| 20 | instant | 0.01 sec | **77 crore years!** |
| 50 | instant | **115 days!** | impossible |
| 100 | instant | **longer than age of universe** | impossible |

> **Key insight:** Polynomial = practical. Exponential = impossible for large N.

---

### P — "Easy to Solve"

**P** = Problems solvable in **polynomial time**.

| Problem | Algorithm | Complexity |
|---------|-----------|-----------| 
| Sort an array | Merge Sort | O(N log N) |
| Find shortest path | Dijkstra | O((V+E) log V) |
| Search sorted array | Binary Search | O(log N) |
| Two Sum | HashMap | O(N) |
| GCD | Euclidean | O(log N) |

---

### NP — "Easy to Verify"

**NP** = Problems where a given solution can be **verified in polynomial time**, but finding the solution may be hard.

#### Sudoku Example:
- **Verify** a completed Sudoku: Check all rows, columns, 3x3 boxes = 243 checks -> **O(N^2)** ✓
- **Solve** an empty Sudoku: Up to 9^30 combinations for 30 empty cells -> **exponential** ✗

> **P subset of NP** — Every P problem is also in NP (if you can solve it fast, you can verify it fast too). The open question is whether P = NP or P != NP.

---

### NP-Complete — "Hardest Problems in NP"

A problem is **NP-Complete** if:
1. It's in **NP** (solution verifiable in polynomial time)
2. Every NP problem can be **reduced** to it in polynomial time

If you solve ONE NP-Complete problem in polynomial time -> **you solve ALL NP problems** -> P = NP!

#### Famous NP-Complete Problems:

**1. Travelling Salesman Problem (TSP)**
- Visit N cities exactly once, return to start, minimize total distance.
- Possible routes = (N-1)! -> O(N!) brute force
- `N=20`: 19! ≈ 1.2 * 10^17 routes — impossible brute force!
- **Verify:** Given a route, check its total distance -> O(N) ✓

**2. 0/1 Knapsack**
- Fill a bag of capacity W with items to maximize value. Can't take fractions.
- Possible combinations = 2^N
- `N=50`: 2^50 ≈ 10^15 — impossible!
- **Verify:** Given a selection, check weight <= W and compute value -> O(N) ✓

**3. Graph Coloring**
- Color graph nodes so no two adjacent nodes share a color. What's the minimum number of colors?
- **Real-life:** Exam scheduling (no student has two exams at the same time) = Graph Coloring!
- **Verify:** Given a coloring, check all edges -> O(V + E) ✓
- **Solve (min colors):** Exponential in general ✗

**4. Sudoku**
- As described above — NP-Complete for N x N grids.

---

### NP-Hard — "Even Harder"

**NP-Hard** = At least as hard as NP-Complete problems, but solutions may **not even be verifiable in polynomial time**.

#### Halting Problem (NP-Hard / Undecidable)
> Given a program and input, will the program ever stop?

```cpp
void mystery(int n) {
    while (n != 1) {
        if (n % 2 == 0) n = n / 2;
        else n = 3 * n + 1;
    }
}
```

- `mystery(6)` -> 6, 3, 10, 5, 16, 8, 4, 2, 1 -> Stops ✓
- For arbitrary programs: **Alan Turing (1936) proved no algorithm can decide this in general.** It's mathematically impossible — not just hard!

---

### Complexity Classes at a Glance

```
+--------------------------------------------------+
|                    NP-Hard                       |
|                                                  |
|   +------------------------------------------+  |
|   |                  NP                      |  |
|   |                                          |  |
|   |   +------------------------------+       |  |
|   |   |             P                |       |  |
|   |   |  - Sorting                   |       |  |
|   |   |  - Binary Search             |       |  |
|   |   |  - Dijkstra                  |       |  |
|   |   |  - Two Sum (HashMap)         |       |  |
|   |   +------------------------------+       |  |
|   |                                          |  |
|   |     NP-Complete:                         |  |
|   |     TSP, Knapsack, Graph Coloring        |  |
|   |     Sudoku, Vertex Cover                 |  |
|   |                                          |  |
|   +------------------------------------------+  |
|                                                  |
|     NP-Hard (outside NP):                       |
|     Halting Problem                              |
|                                                  |
+--------------------------------------------------+
```

| Class | Solve | Verify |
|-------|-------|--------|
| P | Fast (polynomial) | Fast (polynomial) |
| NP | Maybe slow | Fast (polynomial) |
| NP-Complete | No polynomial known, verify fast | Fast (polynomial) |
| NP-Hard | No polynomial known | Maybe not polynomial either |

### P = NP? — $1,000,000 Unsolved Problem

- **If P = NP:** All NP problems solvable efficiently -> cryptography (RSA, Bitcoin, your bank) **breaks!** Drug discovery becomes trivial. Logistics is solved optimally.
- **If P != NP:** Some problems are fundamentally hard — NP-Complete problems have no efficient solution by nature.
- **Current belief:** Almost all experts believe P != NP. But **nobody has proved either way** in 50+ years.
- **Prize:** Clay Mathematics Institute Millennium Prize — **$1,000,000 USD** waiting.

---

### Interview Tip: How to Use This Knowledge

When an interviewer gives you a problem and you realize it's exponential:
> *"This looks similar to [TSP / Knapsack / Graph Coloring] — it might be NP-Complete. For small `n` we can use brute force or dynamic programming. For larger inputs, a greedy approximation would give near-optimal results in polynomial time. Want me to implement the approximate approach?"*

This shows you recognize problem classes, know the limits, and can propose practical alternatives.

---

## 24. Algorithm & Data Structure Complexity Table

### Sorting Algorithms

#### What is a Stable Sort?
A sort is **stable** if equal elements maintain their original relative order after sorting.

```
Before: (Ali, 85), (Bina, 90), (Charu, 85), (Dina, 90)

Stable:   (Ali, 85), (Charu, 85), (Bina, 90), (Dina, 90)  <- Ali before Charu ✓
Unstable: (Charu, 85), (Ali, 85), (Bina, 90), (Dina, 90)  <- order changed ✗
```

| Algorithm | Best | Average | Worst | Space | Stable? |
|-----------|------|---------|-------|-------|---------|
| Bubble Sort | O(N) | O(N^2) | O(N^2) | O(1) | Yes |
| Selection Sort | O(N^2) | O(N^2) | O(N^2) | O(1) | No |
| Insertion Sort | O(N) | O(N^2) | O(N^2) | O(1) | Yes |
| Merge Sort | O(N log N) | O(N log N) | O(N log N) | O(N) | Yes |
| Quick Sort | O(N log N) | O(N log N) | O(N^2) | O(log N) | No |
| Heap Sort | O(N log N) | O(N log N) | O(N log N) | O(1) | No |
| Counting Sort | O(N + k) | O(N + k) | O(N + k) | O(k) | Yes |
| Radix Sort | O(N*k) | O(N*k) | O(N*k) | O(N + k) | Yes |

> `k` = range of values (Counting Sort) or number of digits (Radix Sort)

#### Which Sorting Algorithm to Use When?

| Scenario | Use This |
|----------|----------|
| General purpose | `sort()` in C++ — O(N log N) |
| Need stable sort | `stable_sort()` in C++ |
| Nearly sorted array | Insertion Sort — O(N) best case |
| Known small integer range | Counting Sort — O(N + k) |
| Large numbers, many digits | Radix Sort |
| Memory is critical, unstable ok | Heap Sort — O(1) space |

#### Key Sorting Trade-offs for Interviews
- **Merge Sort vs Quick Sort:** Merge Sort = guaranteed O(N log N) + stable, but O(N) space. Quick Sort = O(N log N) average + O(log N) space, but O(N^2) worst case.
- **Bubble/Selection/Insertion:** All O(N^2) average/worst, but Insertion Sort is O(N) best case (nearly sorted).
- **Heap Sort:** O(N log N) guaranteed, O(1) space — but cache-unfriendly and unstable.

---

### Data Structure Operations

| Data Structure | Access | Search | Insert | Delete | Space |
|----------------|--------|--------|--------|--------|-------|
| Array | O(1) | O(N) | O(N) | O(N) | O(N) |
| Linked List | O(N) | O(N) | O(1)* | O(1)* | O(N) |
| Stack | O(N) | O(N) | O(1) | O(1) | O(N) |
| Queue | O(N) | O(N) | O(1) | O(1) | O(N) |
| Hash Map (avg) | — | O(1) | O(1) | O(1) | O(N) |
| BST (balanced) | O(log N) | O(log N) | O(log N) | O(log N) | O(N) |
| Min/Max Heap | O(1) top | O(N) | O(log N) | O(log N) | O(N) |

> \* Linked List insert/delete is O(1) **only if you already have a pointer to that node**. Finding it first takes O(N).

#### Which Data Structure to Use When?

| Need | Use | Complexity |
|------|-----|-----------|
| Fast lookup by key (unsorted) | `unordered_map` | O(1) avg |
| Sorted key + lookup | `map` | O(log N) |
| Get max/min fast | `priority_queue` | O(1) top, O(log N) insert |
| LIFO (undo, DFS, parentheses) | `stack` | O(1) push/pop |
| FIFO (BFS, scheduling) | `queue` | O(1) push/pop |
| Random access by index | `vector` | O(1) access |
| Frequent insert/delete at middle | `list` (linked list) | O(1) insert (with pointer) |

---

### Advanced Data Structures

| Data Structure | Use Case | Key Operations | Time |
|----------------|----------|----------------|------|
| **Trie** | String prefix search, autocomplete | Insert, Search | O(L) — L = string length |
| **Segment Tree** | Range query + point update | Build, Query, Update | Build O(N), Query/Update O(log N) |
| **Fenwick Tree (BIT)** | Range sum + point update | Query, Update | O(log N) |
| **Disjoint Set (Union-Find)** | Group membership, connected components | Find, Union | O(alpha(N)) ≈ O(1) amortized |

---

### Algorithm Paradigms / Techniques

| Technique | Typical Time | Space | When to Use |
|-----------|-------------|-------|-------------|
| Brute Force | O(N^2) or O(2^N) | O(1) | Small N, as a starting point |
| Greedy | O(N log N) | O(1) to O(N) | Locally optimal -> globally optimal |
| Dynamic Programming | O(N^2) or O(N*W) | O(N) to O(N^2) | Overlapping subproblems + optimal substructure |
| Divide & Conquer | O(N log N) | O(log N) to O(N) | Split problem, solve parts independently |
| Backtracking | O(2^N) or O(N!) | O(N) | Explore all possibilities, prune invalid ones |
| Two Pointers | O(N) | O(1) | Sorted array, find pairs/triplets |
| Sliding Window | O(N) | O(1) to O(k) | Subarray/substring problems of fixed/variable size |
| Binary Search on Answer | O(N log X) | O(1) | Answer is monotonic |

#### Common Dynamic Programming Problems

| Problem | Time | Space | What It Asks |
|---------|------|-------|-------------|
| Fibonacci (DP) | O(N) | O(1) | N-th Fibonacci number |
| 0/1 Knapsack | O(N * W) | O(N * W) | Max value in bag (W = capacity) |
| Unbounded Knapsack | O(N * W) | O(W) | Items can be reused |
| LCS | O(N * M) | O(N * M) | Longest Common Subsequence of two strings |
| LIS | O(N log N) | O(N) | Longest Increasing Subsequence |
| Edit Distance | O(N * M) | O(N * M) | Min operations to convert one string to another |
| Coin Change | O(N * amount) | O(amount) | Min coins to make a target amount |
| Longest Palindromic Subsequence | O(N^2) | O(N^2) | Longest palindrome in a string |
| Matrix Chain Multiplication | O(N^3) | O(N^2) | Min cost to multiply matrices |
| Subset Sum | O(N * sum) | O(N * sum) | Can a subset sum to target? |
| Rod Cutting | O(N^2) | O(N) | Max value from cutting a rod |
| House Robber | O(N) | O(1) | Max loot without adjacent houses |
| Climbing Stairs | O(N) | O(1) | Ways to climb N steps (1 or 2 at a time) |

#### DP Recognition Trick
If a problem says: *"minimum cost"*, *"maximum profit"*, *"how many ways"*, *"is it possible"* — it's likely **Dynamic Programming**.

---

### Searching Algorithms

| Algorithm | Best | Average | Worst | Prerequisite |
|-----------|------|---------|-------|-------------|
| Linear Search | O(1) | O(N) | O(N) | None |
| Binary Search | O(1) | O(log N) | O(log N) | Sorted array |
| Hash Lookup | O(1) | O(1) | O(N) | Hash table pre-built |

```cpp
// C++ STL Binary Search
vector<int> arr = {1, 3, 5, 7, 9};
binary_search(arr.begin(), arr.end(), 5);   // true
lower_bound(arr.begin(), arr.end(), 5);     // iterator to 5
upper_bound(arr.begin(), arr.end(), 5);     // iterator to 7
```

---

### Graph Algorithms

| Algorithm | Time | Space | Use Case |
|-----------|------|-------|---------|
| BFS | O(V + E) | O(V) | Shortest path (unweighted) |
| DFS | O(V + E) | O(V) | Traversal, cycle detection, topological sort |
| Dijkstra | O((V + E) log V) | O(V) | Shortest path (weighted, no negative edges) |
| Bellman-Ford | O(V * E) | O(V) | Shortest path (negative edges allowed) |
| Floyd-Warshall | O(V^3) | O(V^2) | All-pairs shortest path |
| Kruskal | O(E log E) | O(V) | Minimum Spanning Tree |
| Prim | O((V + E) log V) | O(V) | Minimum Spanning Tree |
| Topological Sort | O(V + E) | O(V) | DAG ordering (dependencies) |

> V = number of vertices (nodes), E = number of edges

#### Graph Algorithm Quick Reference

| If you need... | Use |
|----------------|-----|
| Shortest path (unweighted) | BFS |
| Shortest path (weighted, no negatives) | Dijkstra |
| Shortest path (negative edges ok) | Bellman-Ford |
| All-pairs shortest path | Floyd-Warshall |
| Cycle detection | DFS |
| Minimum Spanning Tree | Kruskal or Prim |
| Ordered dependencies | Topological Sort (DFS or Kahn's BFS) |
| Connected components | Union-Find or DFS |

---

## 25. The n-to-Complexity Quick Decision Table

> **10^8 Rule:** C++ processes ~10^8 (100 million) operations per second. Use this to map `n` to the required complexity.

| Input Size (n) | Maximum Acceptable Complexity | Why |
|----------------|-------------------------------|-----|
| n <= 10-12 | O(N!) | 12! ≈ 5 crore operations |
| n <= 20-25 | O(2^N) | 2^25 ≈ 3.3 crore operations |
| n <= 500 | O(N^3) | 500^3 = 12.5 crore operations |
| n <= 10,000 | O(N^2) | 10,000^2 = 10 crore operations |
| n <= 1,000,000 | O(N log N) | ~2 crore operations |
| n <= 100,000,000 | O(N) | Exactly 10 crore operations |
| n > 100,000,000 | O(log N) or O(1) | N itself is too large for linear |

### How to Use This in an Interview

1. **Listen to the constraint** — "What's the expected input size?"
2. **Map to complexity** using the table above.
3. **Plan accordingly** — don't write an O(N^2) solution if N = 10^5.

**Example:**
- Problem says `1 <= N <= 10^5` -> O(N^2) = 10^10 = too slow. Need **O(N log N)** or better.
- Problem says `1 <= N <= 20` -> O(2^N) = 10^6 = fine. Use **bitmask DP or backtracking**.
- Problem says `1 <= N <= 10^8` -> Need a **single-pass O(N)** solution. Even O(N log N) may be tight.

---

## Complete Complexity Hierarchy (Slowest -> Fastest Growth)

```
O(1) < O(log N) < O(sqrt(N)) < O(N) < O(N log N) < O(N^2) < O(N^3) < O(2^N) < O(N!) < O(N^N)
```

| Complexity | Name | Example |
|-----------|------|---------|
| O(1) | Constant | Array access, HashMap lookup |
| O(log N) | Logarithmic | Binary Search |
| O(sqrt(N)) | Root | Prime checking (optimized) |
| O(N) | Linear | Single loop, Linear Search |
| O(N log N) | Linearithmic | Merge Sort, Heap Sort |
| O(N^2) | Quadratic | Bubble Sort, nested loops |
| O(N^3) | Cubic | Matrix multiplication (naive) |
| O(2^N) | Exponential | Fibonacci (naive), all subsets |
| O(N!) | Factorial | Permutations, TSP brute force |

---

## Final Quick-Reference Summary

### Time Complexity Cheatsheet

| Code Pattern | Complexity |
|-------------|-----------|
| Single statement / formula | O(1) |
| One loop 1 to N | O(N) |
| Two separate loops 1 to N | O(N) |
| Loop with `i *= 2` or `i /= 2` | O(log N) |
| Nested loops (both 1 to N) | O(N^2) |
| Loop + inner loop with `j *= 2` | O(N log N) |
| Recursion divides by 2 each time | O(log N) |
| Recursion makes 2 calls (no memo) | O(2^N) |
| Recursion makes N calls, each O(N) | O(N^2) |
| Harmonic inner loop `j <= N/i` | O(N log N) |
| Geometric decreasing inner loop | O(N) |

### Space Complexity Cheatsheet

| Pattern | Space |
|---------|-------|
| Fixed variables only | O(1) |
| One extra array of size N | O(N) |
| 2D matrix N x N | O(N^2) |
| Recursion depth N | O(N) stack |
| Recursion depth N, each level O(N) | O(N^2) total |

### Interview One-Liners

- **"Why O(1) even though there's a loop?"** — The loop has a fixed number of iterations, not dependent on input.
- **"What's the space complexity of recursion?"** — O(depth) for the call stack.
- **"Is O(N/2) different from O(N)?"** — No — constants are dropped. O(N/2) = O(N).
- **"Why does binary search work in O(log N)?"** — Each step halves the search space. After log_2(N) halvings, one element remains.
- **"What's amortized O(1)?"** — An operation that's occasionally expensive but cheap on average over many operations (e.g., `push_back` in a vector).

---


