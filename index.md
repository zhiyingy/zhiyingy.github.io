# LOCK-FREE AVL TREES
### Team Members: 
Zhiying Yao (zhiyingy), Hongyi Ding (hongyid)

## Final Report
[final report](https://github.com/zhiyingy/zhiyingy.github.io/blob/zhiyingy-proposal/final.md)

### Summary

For this project, we will first implement lock-free AVL trees, which support search, insert, and delete operations. We will also implement AVL trees with different locking mechanisms, and do comparative analysis of these implementations. 

### Background

Synchronization is an important topic in parallelism to ensure the correctness of the program. In class, we learned about different implementations of synchronization, lock free data structures, and transactional memory. Here, we want to compare the performance of lock-free AVL trees and AVL trees with different locking mechanisms. We chose AVL tree here because self-balancing binary search trees are an important data structure that are used in many algorithms.

### Challenges
1. Lock free algorithms for self-balancing trees are not easy to come up with.<br />
2. Different locks are suitable for different situations, thus we need to design multiple situations to show the tradeoff between locks. (like frequent insertion, infrequent deletes).

### Goals and Deliverables

plan to achieve: <br />
· plan to implement lock-free AVL trees. <br />
· plan to implement AVL trees with different locking mechanisms. <br />
· plan to do comparative analysis of these implementations of AVL trees.

Hope to achieve: <br />
· hope to implement AVL trees using transactional memeory.

This is an analysis project, and we plan to answer the question of which lock implementation of AVL trees has the best performance on which machines/thread counts. At the poster session, we want to show the performace of each lock implementation on different machines with different thread counts. 

### Platform Choice
We will choose C++ for its high-performance and completeness and various existing C++ based parallel libraries. We will test our lock implementations on differnt machines (latedays, latedays phi, mac os, ghc machines) to see which locking mechanism has the best performance on which machines.

### Resources
[Fast Concurrent AVL trees](https://spcl.inf.ethz.ch/Teaching/2013-dphpc/final/8.pdf)

### Schedule
week 1 (Oct 28th - Nov 3rd): proposal, working environment setup, installation of required packages. <br />
week 2 (Nov 4th - Nov 10th): implementation of lock-free AVL trees
week 3 (Nov 11th - Nov 17th): continued implementation of lock-free AVL trees.<br />
week 4 (Nov 18th - Nov 24th): implementation of AVL trees using different locking mechanisms.<br />
week 5 (Nov 25th - Dec 1st): continued implementation of AVL trees using different locking mechanisms.<br />
week 6 (Dec 2nd - Dec 8th): comparative analysis of different implementations of AVL trees. <br />
week 7 (Dec 9th - Dec 15th): final report and presentation.<br />



