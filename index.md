# Lock Implementations and Lock Free AVL Tree
### Team Members: Zhiying Yao (zhiyingy), Hongyi Ding (hongyid)

## Final Report
[final report](https://github.com/zhiyingy/zhiyingy.github.io/blob/zhiyingy-proposal/final.md)

## Proposal:
### Summary

For this project, we will implement different types of locks to test the performance of different synchronization startegies. Specifically, we will be implementing test-and-set lock, test-and-test-and-set lock, ticket locks, queue-based locks, and test it on AVL tree for search, insert, delete operations. We will also implement a lock free AVL tree and compare the performance.

### Background

Synchronization is an important topic in parallelism to ensure the correctness of the program. In class, we learned about different implementations of synchronization such as locks and lock free data structures. Here, we want to compare the performance of different lock implementations and a lock free data structure. We chose AVL tree here because self-balancing binary search trees are an important data structure that are used in many algorithms.

### Challenges


### Goals and Deliverables

plan to achieve: <\br>
plan to implement different locks. <\br>
plan to implement a lock free AVL tree data structure. <\br>

This is an analysis project, and we plan to answer the question of which lock implementation has the best performance on which machines. At the poster session, we want to show the performace of each lock implementation of different machines. 


### Platform Choice
We will choose C++ for its high-performance and completeness and various existing C++ based parallel libraries. We will test our lock implementations on differnt machines (latedays, latedays phi, mac os, ghc machines) to see which lock has the best performance on which machines, and compare it with c mutex lock. 

### Resources
[Test-and-set wiki page](https://en.wikipedia.org/wiki/Test-and-set)<br />

[Fetch-and-add wiki page](https://en.wikipedia.org/wiki/Fetch-and-add)<br />

[Compare-and-swap wiki page](https://en.wikipedia.org/wiki/Compare-and-swap)<br />

[Concurrent Search and Insertion in AVL Trees](https://www.computer.org/csdl/trans/tc/1980/09/01675680.pdf)

### Schedule
week 1 (Oct 28th - Nov 3rd): proposal, working environment setup, installation of required packages.
week 2 (Nov 4th - Nov 10th): implementation of four locks (test and set, test-and-test-and-set, ticket lock, array-based lock).
week 3 (Nov 11th - Nov 17th): implementation of three locks (queue-based lock, fetch-and-add lock, compare and swap).
week 4 (Nov 18th - Nov 24th): implementation of lock-free AVL trees.
week 5 (Nov 25th - Dec 1st): continued implementation of lock-free AVL trees.
week 6 (Dec 2nd - Dec 8th): test different locks on different machines.
week 7 (Dec 9th - Dec 15th): final report and presentation.

