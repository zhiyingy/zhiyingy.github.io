# To compile parallel version

`g++ -o cChess cChess.cpp evaluate.cpp montecarlo.cpp generateMove.cpp parallelab.cpp -fopenmp -O3 -m64`

# To compile sequential version

`g++ -o cChess cChess.cpp evaluate.cpp montecarlo.cpp generateMove.cpp alphabeta.cpp -fopenmp -O3 -m64`

# To run the program:

`./cChess -m m -n 1`

where -m is the attributes for mode, you can choose `-m m` to mark monte-carlo or `-m a` to mark alpha beta pruning

`-n` is number of threads
