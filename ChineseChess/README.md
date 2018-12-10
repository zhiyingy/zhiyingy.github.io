g++ -o cChess cChess.cpp evaluate.cpp montecarlo.cpp generateMove.cpp parallelab.cpp -fopenmp -O3 -m64


input to run the program:
./cChess -m m -n 1
where -m is the attributes for mode, you can choose -m m or -m a
-n is number of threads
