APP_NAME=cChess

OBJS += cChess.o
OBJS += evaluate.o
OBJS += parallelMcts.o
OBJS += generateMove.o
OBJS += parallelab.o

default: $(APP_NAME)

# Compile for CPU
cpu: CXX = g++ -m64 -std=c++11
cpu: CXXFLAGS = -I. -O3 -fopenmp -Wno-unknown-pragmas

# Compilation Rules
$(APP_NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

cpu: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(APP_NAME) $(OBJS)

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -c -o $@

clean:
	rm -f $(APP_NAME) *.o

# For a given rule:
# $< = first prerequisite
# $@ = target
# $^ = all prerequisite
