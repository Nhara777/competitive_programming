# Competitive Programming Library - API Documentation

## Table of Contents

1. [Data Structures](#data-structures)
   - [Union-Find (Disjoint Set Union)](#union-find-disjoint-set-union)
   - [Segment Tree (Range Minimum Query)](#segment-tree-range-minimum-query)
   - [Lazy Segment Tree (RMQ & RSQ)](#lazy-segment-tree-rmq--rsq)
   - [Binary Indexed Tree (Fenwick Tree)](#binary-indexed-tree-fenwick-tree)
   - [Cartesian Tree](#cartesian-tree)

2. [Graph Algorithms](#graph-algorithms)
   - [Strongly Connected Components (SCC)](#strongly-connected-components-scc)
   - [Topological Sort](#topological-sort)
   - [2-SAT](#2-sat)

3. [Flow Algorithms](#flow-algorithms)
   - [Dinic's Algorithm (Maximum Flow)](#dinics-algorithm-maximum-flow)
   - [Minimum Cost Flow](#minimum-cost-flow)

4. [String Algorithms](#string-algorithms)
   - [KMP (Knuth-Morris-Pratt)](#kmp-knuth-morris-pratt)
   - [Z-Algorithm](#z-algorithm)
   - [Run-Length Encoding](#run-length-encoding)

5. [Number Theory](#number-theory)
   - [Extended Euclidean Algorithm](#extended-euclidean-algorithm)
   - [Chinese Remainder Theorem](#chinese-remainder-theorem)
   - [Modular Inverse](#modular-inverse)
   - [Factorial Inverse](#factorial-inverse)
   - [Linear Prime Sieve](#linear-prime-sieve)

6. [Convolution & Transform](#convolution--transform)
   - [Fast Fourier Transform (FFT)](#fast-fourier-transform-fft)
   - [Number Theoretic Transform (NTT)](#number-theoretic-transform-ntt)

7. [Geometric & Other Algorithms](#geometric--other-algorithms)
   - [Maximum Rectangle in Histogram](#maximum-rectangle-in-histogram)

---

## Data Structures

### Union-Find (Disjoint Set Union)

**File:** `union_find.cpp`

A data structure that efficiently handles queries about connected components in an undirected graph.

#### Public API

```cpp
class UnionFind {
public:
    UnionFind(int m);           // Constructor
    int find(int x);            // Find root of element x
    void unite(int x, int y);   // Union sets containing x and y
    int sizing(int x);          // Get size of set containing x
    bool same(int x, int y);    // Check if x and y are in same set
};
```

#### Usage Example

```cpp
UnionFind uf(5);  // Create union-find for 5 elements (0-4)

// Union operations
uf.unite(0, 1);
uf.unite(2, 3);

// Query operations
bool connected = uf.same(0, 1);    // true
bool connected2 = uf.same(0, 2);   // false
int size = uf.sizing(0);           // 2 (elements 0 and 1)
```

#### Time Complexity
- `find()`, `unite()`, `same()`: O(α(n)) amortized, where α is the inverse Ackermann function
- `sizing()`: O(α(n)) amortized

---

### Segment Tree (Range Minimum Query)

**File:** `segtree_rmq.cpp`

A tree data structure for efficient range minimum queries and point updates.

#### Public API

```cpp
class SegTree {
public:
    SegTree(int m);                    // Constructor
    void update(int k, int a);         // Update element at index k to value a
    int get(int a, int b);            // Get minimum in range [a, b)
};
```

#### Usage Example

```cpp
SegTree st(8);  // Create segment tree for 8 elements

// Update operations
st.update(0, 5);
st.update(1, 3);
st.update(2, 7);
st.update(3, 1);

// Range minimum queries
int min_val = st.get(0, 4);  // Returns 1 (minimum in range [0, 4))
int min_val2 = st.get(1, 3); // Returns 3 (minimum in range [1, 3))
```

#### Time Complexity
- `update()`: O(log n)
- `get()`: O(log n)

---

### Lazy Segment Tree (RMQ & RSQ)

**Files:** `lazysegtree_rmq.cpp`, `lazysegtree_rsq.cpp`

Segment trees with lazy propagation for efficient range updates and range queries.

#### Public API

```cpp
class LazySegTree {
public:
    LazySegTree(int m);                // Constructor
    void put(int a, int b, int v);     // Update range [a, b) to value v
    int get(int a, int b);             // Get min/sum in range [a, b)
};
```

#### Usage Example

```cpp
// For Range Minimum Query
LazySegTree lst_rmq(8);
lst_rmq.put(0, 4, 10);  // Set range [0, 4) to 10
lst_rmq.put(2, 6, 5);   // Set range [2, 6) to 5
int min_val = lst_rmq.get(1, 5);  // Get minimum in [1, 5)

// For Range Sum Query  
LazySegTree lst_rsq(8);
lst_rsq.put(0, 4, 3);   // Add 3 to range [0, 4)
lst_rsq.put(2, 6, 2);   // Add 2 to range [2, 6)
int sum = lst_rsq.get(1, 5);  // Get sum in [1, 5)
```

#### Time Complexity
- `put()`: O(log n)
- `get()`: O(log n)

---

### Binary Indexed Tree (Fenwick Tree)

**File:** `BIT.cpp`

A data structure for efficient prefix sum queries and point updates.

#### Public API

```cpp
class BIT {
public:
    BIT(int m);              // Constructor
    void add(int k, int a);  // Add value a to element at 1-indexed position k
    int sum(int k);          // Get prefix sum up to 1-indexed position k
};
```

#### Usage Example

```cpp
BIT bit(10);  // Create BIT for 10 elements

// Add operations (1-indexed)
bit.add(1, 5);
bit.add(3, 7);
bit.add(5, 3);

// Prefix sum queries (1-indexed)
int prefix_sum = bit.sum(5);  // Sum of elements 1 to 5
int range_sum = bit.sum(5) - bit.sum(2);  // Sum of elements 3 to 5
```

#### Time Complexity
- `add()`: O(log n)
- `sum()`: O(log n)

---

### Cartesian Tree

**File:** `cartesian_tree.cpp`

Constructs a cartesian tree from an array, useful for range minimum/maximum queries.

#### Public API

```cpp
template<typename T>
pair<vector<vector<int>>, vector<int>> cartesian_tree(vector<T> &a);
// Returns: (adjacency list, parent array)
```

#### Usage Example

```cpp
vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
auto [graph, parent] = cartesian_tree(arr);

// graph[i] contains children of node i
// parent[i] contains parent of node i (-1 if root)
```

#### Time Complexity
- Construction: O(n)

---

## Graph Algorithms

### Strongly Connected Components (SCC)

**File:** `SCC.cpp`

Finds strongly connected components in a directed graph using Kosaraju's algorithm.

#### Public API

```cpp
class SCC {
public:
    SCC(int m);                           // Constructor
    void add_edge(int from, int to);      // Add directed edge
    vector<vector<int>> scc();            // Find SCCs
};
```

#### Usage Example

```cpp
SCC scc(5);  // Graph with 5 vertices

// Add edges
scc.add_edge(0, 1);
scc.add_edge(1, 2);
scc.add_edge(2, 0);  // Cycle: 0->1->2->0
scc.add_edge(2, 3);
scc.add_edge(3, 4);

// Find SCCs
vector<vector<int>> components = scc.scc();
// components[i] contains vertices in i-th SCC
```

#### Time Complexity
- Adding edges: O(1) per edge
- Finding SCCs: O(V + E)

---

### Topological Sort

**Files:** `topological_sort_kahn_ver.cpp`, `topological_sort_tarjan_ver.cpp`

Two implementations of topological sorting for directed acyclic graphs.

#### Public API

```cpp
// Kahn's algorithm (BFS-based)
vector<int> topological_sort(vector<vector<int>> e);

// Tarjan's algorithm (DFS-based)  
vector<int> topological_sort(vector<vector<int>> e);
```

#### Usage Example

```cpp
// Adjacency list representation
vector<vector<int>> graph = {
    {1, 2},    // 0 -> 1, 2
    {3},       // 1 -> 3
    {3},       // 2 -> 3
    {}         // 3 (no outgoing edges)
};

vector<int> topo_order = topological_sort(graph);
// Returns a valid topological ordering: [0, 1, 2, 3] or [0, 2, 1, 3]
```

#### Time Complexity
- Both implementations: O(V + E)

---

### 2-SAT

**File:** `2sat_sample.cpp`

Solves 2-SAT (Boolean satisfiability) problems using SCC.

#### Usage
The implementation reads from standard input in DIMACS CNF format and outputs whether the formula is satisfiable.

#### Input Format
```
p cnf n m
x1 x2 0
x3 -x1 0
...
```

Where:
- `n` = number of variables
- `m` = number of clauses
- Each line contains two literals and ends with 0

#### Time Complexity
- O(V + E) where V = 2n, E = 2m

---

## Flow Algorithms

### Dinic's Algorithm (Maximum Flow)

**File:** `Dinic.cpp`

Efficient algorithm for finding maximum flow in a flow network.

#### Public API

```cpp
class Dinic {
public:
    Dinic(int m);                           // Constructor
    void add_edge(int from, int to, int cap); // Add edge with capacity
    int max_flow(int s, int t);             // Find maximum flow from s to t
};
```

#### Usage Example

```cpp
Dinic dinic(6);  // Graph with 6 vertices

// Add edges (from, to, capacity)
dinic.add_edge(0, 1, 10);
dinic.add_edge(0, 2, 8);
dinic.add_edge(1, 3, 5);
dinic.add_edge(2, 3, 10);
dinic.add_edge(1, 4, 8);
dinic.add_edge(3, 5, 10);
dinic.add_edge(4, 5, 10);

int max_flow_value = dinic.max_flow(0, 5);  // Source=0, Sink=5
```

#### Time Complexity
- O(V²E) general case
- O(min(V^(2/3), E^(1/2)) × E) for unit capacities

---

### Minimum Cost Flow

**File:** `min_cost_flow.cpp`

Finds minimum cost flow using successive shortest paths with Dijkstra.

#### Public API

```cpp
class MinCostFlow {
public:
    MinCostFlow(int m);                              // Constructor
    void add_edge(int from, int to, int cap, int cost); // Add edge
    int flow(int s, int t, int f);                   // Min cost for flow f
};
```

#### Usage Example

```cpp
MinCostFlow mcf(4);

// Add edges (from, to, capacity, cost)
mcf.add_edge(0, 1, 10, 2);
mcf.add_edge(0, 2, 10, 4);
mcf.add_edge(1, 3, 10, 3);
mcf.add_edge(2, 3, 10, 1);

int min_cost = mcf.flow(0, 3, 5);  // Min cost for flow=5 from 0 to 3
```

#### Time Complexity
- O(FE log V) where F is the flow amount

---

## String Algorithms

### KMP (Knuth-Morris-Pratt)

**File:** `KMP.cpp`

Efficient string pattern matching algorithm.

#### Public API

```cpp
vector<int> kmp_table(string w);              // Build failure function
vector<int> kmp_search(string s, string w);   // Find all occurrences
```

#### Usage Example

```cpp
string text = "ababcababa";
string pattern = "ababa";

// Find all occurrences
vector<int> positions = kmp_search(text, pattern);
// Returns positions where pattern starts: [5]

// Build failure function
vector<int> failure = kmp_table(pattern);
```

#### Time Complexity
- `kmp_table()`: O(m) where m is pattern length
- `kmp_search()`: O(n + m) where n is text length

---

### Z-Algorithm

**File:** `Z_algorithm.cpp`

Computes Z-array for string matching and analysis.

#### Public API

```cpp
vector<int> z(string s);  // Compute Z-array
```

#### Usage Example

```cpp
string s = "abacaba";
vector<int> z_array = z(s);
// z_array[i] = length of longest substring starting at i that matches prefix
// Result: [7, 0, 1, 0, 3, 0, 1]
```

#### Time Complexity
- O(n) where n is string length

---

### Run-Length Encoding

**File:** `run_length.cpp`

Compresses strings by encoding consecutive identical characters.

#### Public API

```cpp
vector<pair<char,int>> runLength(string s);  // Encode string
```

#### Usage Example

```cpp
string s = "aaabbcccc";
vector<pair<char,int>> encoded = runLength(s);
// Result: [('a', 3), ('b', 2), ('c', 4)]
```

#### Time Complexity
- O(n) where n is string length

---

## Number Theory

### Extended Euclidean Algorithm

**File:** `gcd_extension.cpp`

Finds integers x, y such that ax + by = gcd(a, b).

#### Public API

```cpp
long long extgcd(long long a, long long b, long long &x, long long &y);
// Returns gcd(a, b) and sets x, y such that ax + by = gcd(a, b)
```

#### Usage Example

```cpp
long long x, y;
long long g = extgcd(35, 15, x, y);
// g = 5, and 35*x + 15*y = 5
// x = 1, y = -2 (since 35*1 + 15*(-2) = 5)
```

#### Time Complexity
- O(log(min(a, b)))

---

### Chinese Remainder Theorem

**File:** `CRT.cpp`

Solves system of congruences x ≡ b₁ (mod m₁), x ≡ b₂ (mod m₂).

#### Public API

```cpp
pair<long long,long long> CRT(long long b1, long long m1, long long b2, long long m2);
// Returns (solution, modulus) or (0, -1) if no solution exists
```

#### Usage Example

```cpp
// Solve: x ≡ 2 (mod 3), x ≡ 3 (mod 5)
auto [solution, modulus] = CRT(2, 3, 3, 5);
// solution = 8, modulus = 15
// Verification: 8 ≡ 2 (mod 3) and 8 ≡ 3 (mod 5)
```

#### Time Complexity
- O(log(min(m₁, m₂)))

---

### Modular Inverse

**File:** `mod_inverse.cpp`

Computes modular multiplicative inverse using Fermat's little theorem.

#### Public API

```cpp
long long mod_inv(long long n);  // Returns n⁻¹ mod MOD
```

#### Usage Example

```cpp
const long long MOD = 1000000007;
long long inv = mod_inv(3);  // 3⁻¹ mod MOD
// Verification: (3 * inv) % MOD == 1
```

#### Time Complexity
- O(log MOD)

---

### Factorial Inverse

**File:** `fact_inv.cpp`

Precomputes modular inverses of factorials.

#### Public API

```cpp
vector<long long> fact_inv(int t, long long MOD);  // Returns inverse factorials 0! to t!
```

#### Usage Example

```cpp
const long long MOD = 1000000007;
vector<long long> inv_fact = fact_inv(100, MOD);
// inv_fact[i] = (i!)⁻¹ mod MOD for i = 0 to 100
```

#### Time Complexity
- O(t) preprocessing

---

### Linear Prime Sieve

**File:** `linear_prime_sieve.cpp`

Efficiently finds all prime numbers up to n and their smallest prime factors.

#### Public API

```cpp
vector<int> linear_prime(int n);  // Returns smallest prime factor array
```

#### Usage Example

```cpp
vector<int> spf = linear_prime(20);
// spf[i] = smallest prime factor of i
// spf = [0, 0, 2, 3, 2, 5, 2, 7, 2, 3, 2, 11, 2, 13, 2, 3, 2, 17, 2, 19, 2]

// Extract primes
vector<int> primes;
for (int i = 2; i <= 20; i++) {
    if (spf[i] == i) primes.push_back(i);
}
// primes = [2, 3, 5, 7, 11, 13, 17, 19]
```

#### Time Complexity
- O(n) time and space

---

## Convolution & Transform

### Fast Fourier Transform (FFT)

**File:** `FFT.cpp`

Performs convolution of two sequences using FFT.

#### Public API

```cpp
vector<int> fft(vector<int> a, vector<int> b);  // Convolution of a and b
```

#### Usage Example

```cpp
vector<int> a = {1, 2, 3};     // Polynomial: 1 + 2x + 3x²
vector<int> b = {4, 5};        // Polynomial: 4 + 5x

vector<int> result = fft(a, b);  // Convolution result
// result represents: (1 + 2x + 3x²)(4 + 5x) = 4 + 13x + 22x² + 15x³
```

#### Time Complexity
- O(n log n) where n is the size of input arrays

---

### Number Theoretic Transform (NTT)

**File:** `NTT.cpp`

Integer convolution using Number Theoretic Transform with Chinese Remainder Theorem.

#### Public API

```cpp
vector<long long> NTT(vector<long long> a, vector<long long> b);  // Integer convolution
```

#### Usage Example

```cpp
vector<long long> a = {1, 2, 3};
vector<long long> b = {4, 5};

vector<long long> result = NTT(a, b);
// Exact integer convolution without floating-point errors
```

#### Time Complexity
- O(n log n) where n is the size of input arrays

---

## Geometric & Other Algorithms

### Maximum Rectangle in Histogram

**File:** `max_hist.cpp`

Finds the largest rectangular area in a histogram.

#### Public API

```cpp
long long max_hist(vector<long long> h);  // Returns maximum rectangular area
```

#### Usage Example

```cpp
vector<long long> heights = {2, 1, 5, 6, 2, 3};
long long max_area = max_hist(heights);
// Returns 10 (rectangle with height 5 and width 2, from indices 2-3)
```

#### Time Complexity
- O(n) using stack-based approach

---

## Environment Requirements

- **Compiler:** GCC 9.3.0 or compatible
- **C++ Standard:** C++17 or later
- **Dependencies:** Standard Template Library (STL)

## Usage Notes

1. Most data structures use 0-indexed arrays unless otherwise specified
2. Binary Indexed Tree uses 1-indexed operations
3. Include necessary headers (`#include <bits/stdc++.h>` for competitive programming)
4. Define `MOD` constant where required for modular arithmetic functions
5. Some functions may require additional utility functions (e.g., `extgcd` for `CRT.cpp`)

## Contributing

When adding new algorithms:
1. Follow the existing code style
2. Include time/space complexity in comments
3. Add usage examples
4. Test with sample inputs
5. Update this documentation