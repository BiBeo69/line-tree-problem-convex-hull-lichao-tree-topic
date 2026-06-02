# Line Tree

A selected competitive programming solution from my preparation for the Vietnamese National Informatics Olympiad selection process.

* **Platform:** MarisaOJ
* **Difficulty:** 2100
* **Main topics:** Tree Queries, Dynamic Root, Convex Hull Trick, LineContainer, DFS Small-to-Large

## Problem Summary

Each node of a tree stores a line:

$$
f_i(x) = a_i x + b_i
$$

The tree root can change dynamically. For each query, we need to find the maximum line value among all nodes in the subtree of a given node under the current root.

The constraints are large:

$$
n, q \le 2 \cdot 10^5
$$

so a brute-force approach is not feasible.

## Solution Idea

My solution combines:

* **Euler Tour + ancestor checks** to handle subtree relationships.
* **Binary Lifting** to process queries after changing the root.
* **LineContainer / Convex Hull Trick** to query the maximum value of a set of lines efficiently.
* **DFS Small-to-Large merging** to build subtree line containers efficiently.

For a dynamic-root query, the requested subtree can be reduced to either:

* the whole tree,
* a normal subtree in the original rooting,
* or the complement of one child subtree.

## Complexity

The solution is designed to handle the full constraints efficiently with approximately logarithmic query time after preprocessing.

## Files

```text
line tree CHT.cpp      # Optimized solution
tests/            # Generated tests for verification
```

This repository contains my implementation and generated tests for reference.
