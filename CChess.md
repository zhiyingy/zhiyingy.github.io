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
· a solver that are trained using minmax to beat an amateur 80% of the time. <br />

Hope to achieve: <br />
Implement the solver using MonteCarlo Tree Search algorithm. <br />

At the poster session, we want to show a demo of how to play the game with our AI, and runtime comparison for making a move using different vector size.

### Platform Choice
We will choose C++ for its high-performance and completeness and various existing C++ based parallel libraries. 

We will be using CUDA when exploiting paralleism. We will train our solver on ghc machines.

### Resources
[Minimax on Xiangqi](http://stanford.edu/~dengl11/resource/doc/221-Report.pdf)

### Schedule
### Schedule
week 1 (Oct 28th - Nov 3rd): proposal, working environment setup, installation of required packages. <br />
week 2 (Nov 4th - Nov 10th): implementation of UI.<br />
week 3 (Nov 11th - Nov 17th): implementation of serial minmax search.<br />
week 4 (Nov 18th - Nov 24th): implementation of paralled minmax search.<br />
week 5 (Nov 25th - Dec 1st): train the model.<br />
week 6 (Dec 2nd - Dec 8th): test the model with different vector size.<br />
week 7 (Dec 9th - Dec 15th): final report and presentation.<br />
