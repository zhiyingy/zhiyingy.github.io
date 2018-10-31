## Chinese Chess Solver
### Summary
For this project, we will implement a Chinese Chess Solver using Minimax, Alpha-beta Pruning. When implemented, this solver can be used to play against human players. Chinese chess has more complex rules and larger branching factor than Chess, thus it is more challenging to implement. If we have time, we would implement an parallel MonteCarlo Tree Search for the solver.

### Background
Chinese chess (Xiangqi) is a popular game in China that requires strategies and learnings. It contains seven types of pieces, and each type has different moving rules. 

[Xiangqi Rules](https://en.wikipedia.org/wiki/Xiangqi)

### Challenges
Chinese Chess are complicated, with each type of pieces having their own moving rules. Thus, the workload is nontrivial.

Each move is dependent on the previous move. Therefore, speedup might not be much.

### Goals and Deliverables

plan to achieve: <br />
· a UI that the player can click on the board to play Xiangqi with our solver. <br />
· a solver that are trained using minmax to beat an amateur 50%. <br />

Hope to achieve: <br />
Come up with a hybrid model to deal with the tradeoffs of each lock type. <br />

This is an analysis project, and we plan to answer the question of which lock implementation has the best performance on which machines. At the poster session, we want to show the performace of each lock implementation of different machines. 

### Platform Choice
We will choose C++ for its high-performance and completeness and various existing C++ based parallel libraries. 

We will be using CUDA when exploiting paralleism. We will train our solver on ghc machines.

### Resources
[Minimax on Xiangqi](http://stanford.edu/~dengl11/resource/doc/221-Report.pdf)

### Schedule

