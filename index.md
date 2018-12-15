# Chinese Chess AI
### Team Members: 
Zhiying Yao (zhiyingy), Hongyi Ding (hongyid)

## Final Report
[final report](https://github.com/zhiyingy/zhiyingy.github.io/final.pdf)

### Summary

For this project, we will implement a Chinese Chess Solver using Minimax, Alpha-beta Pruning. When implemented, we can have this solver play Chinese chess against a human player or itself. Chinese chess has more complex rules and larger branching factor than Chess, thus it is more challenging to implement. If we have time, we would implement an parallel MonteCarlo Tree Search for the solver

### Background

Chinese chess (Xiangqi) is a popular game in China that requires strategies and learnings.
It is a two-player, zero-sum game. It contains two armies, each with seven different types
of pieces, and each type has different moving rules. More information about the rules can
be found in the link.
[Xiangqi Rules](https://en.wikipedia.org/wiki/Xiangqi)

### Challenges
Chinese Chess are complicated, with each type of pieces having their own moving rules.
Thus, the workload is nontrivial.
Each move is dependent on the previous move. Therefore, speedup might be limited.
Integrate GUI on C++.

### Goals and Deliverables

plan to achieve: <br />
· A UI that the player can click on the board to play Xiangqi with our solver <br />
· A UI that demonstrates how a solver can play against another solver. <br />
· A solver that are trained using minmax to beat an amateur 80% of the time. 

Hope to achieve: <br />
· Implement the solver using MonteCarlo Tree Search algorithm.

At the poster session, we want to show a demo of how to play the game with our solver,
and how our solver can play against itself. We also want to show a runtime comparison for
making a move using different vector size.

### Platform Choice
We will choose C++ for its high-performance and completeness and various existing C++
based parallel libraries. Since the workload is heavy, we want something hat has highperformance.
We will be using openMP when exploiting paralleism. We will train our solver on ghc
machines.

### Resources
[Minimax on Xiangqi](http://stanford.edu/~dengl11/resource/doc/221-Report.pdf)
[Parallelizing a Simple Chess Program](https://pdfs.semanticscholar.org/8e1b/da134a45bd362c61827e99fd1e2cb624079d.pdf)

### Schedule
week 1 (Oct 28th - Nov 3rd): proposal, working environment setup, installation of required packages. <br />
week 2 (Nov 4th - Nov 10th): implementation of lock-free AVL trees
week 3 (Nov 11th - Nov 17th): continued implementation of lock-free AVL trees.<br />
week 4 (Nov 18th - Nov 24th): implementation of AVL trees using different locking mechanisms.<br />
week 5 (Nov 25th - Dec 1st): continued implementation of AVL trees using different locking mechanisms.<br />
week 6 (Dec 2nd - Dec 8th): comparative analysis of different implementations of AVL trees. <br />
week 7 (Dec 9th - Dec 15th): final report and presentation.<br />

### Revised Sechdule
week 1 (Oct 28th - Nov 3rd): proposal, working environment setup, installation of required packages. <br />
week 2 (Nov 4th - Nov 10th): implementation of AVL trees using fine-grained locking mechanisms.<br />
week 3 (Nov 11th - Nov 17th): continued implementation of fine-grained AVL trees.<br />
week 4 (Nov 18th - Nov 24th): implementation insertion in lock free AVL trees.<br />
week 5 (Nov 25th - Dec 1st): switched project, implement rules and generate moves for Chinese Chess, implement minmax search algorithm.<br />
week 6 (Dec 2nd - Dec 8th): Implement alpha beta pruing and its parallel version. <br />
week 7 (Dec 9th - Dec 15th): Implement monte carlo tree search and its parallel version, final report and presentation.<br />

## Checkpoint
[Checkpoint](https://github.com/zhiyingy/zhiyingy.github.io/blob/master/checkpoint.md)
