# Knight's Tour

Trevor Kling

CPSC 406: Algorithm Analysis

## Introduction

Implements a solution to the Knight's Tour problem in C++.  Two implementations are presented; one with
a brute-force style solution, and another using heuristics like Warnsdorff's Rule to improve runtime.
The two are run sequentially, timing each to demonstrate improvements.

## Implementation

Implements a custom tree in C++.  Each node contains a vector of integers as data, a pointer to a parent node,
and a vector of pointers to child nodes.  The program takes three arguments in its constructor; an x-y coordinate
pair, and an n dimension for the board.  The program then generates the tree of potential paths across the board, ensuring
no node is visited twice.  The brute solution simply traverses in order, and the heuristic solution uses Warnsdorff's rule
to decide which path to check first.

## Known Issues

Crashes for N > 5.  Could be due to hardware constraints not allowing for full tree to be loaded in RAM.

## Sources
