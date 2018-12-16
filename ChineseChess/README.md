# To compile parallel version
Edit Makefile to include 
` OBJS += parallelMcts.o ` and `OBJS += parallelab.o`

# To compile sequential version
Edit Makefile to include 
` OBJS += montecarlo.o ` and `OBJS += alphabeta.o`

# To compile
run `make clean` first to remove all -o files, and then run `make cpu`

# To run the program:

`./cChess -m m -n 1`

where -m is the attributes for mode, you can choose `-m m` to mark monte-carlo or `-m a` to mark alpha beta pruning

`-n` is number of threads
