#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__
#include "cChess.h"
#include <vector>

#define SIM 1000
#define C 1.4
#define MAXSTEP 10

Move *calculateStepMC(int **board, int curPlayer);

typedef struct movesMC_t {
	struct movesMC_t *parent;
    Move *mv;
    int n;
    int wins;
    int player;
    int nextIndex;
    std::vector<Move*> possibleMoves;
    std::vector<struct movesMC_t *> children;
} movesMC;

class MovesMC {
public:
	MovesMC *parent;
    Move *mv;
    int n;
    int wins;
    int player;
    int nextIndex;
    std::vector<Move*> possibleMoves;
    std::vector<MovesMC *> children;

    MovesMC(MovesMC *pa,Move *m, int p, std::vector<Move*> moves){
    	parent = pa;
    	mv = m;
    	player = p;
    	nextIndex = 0;
    	wins = 0;
    	n = 0;
    	possibleMoves = moves;
    }
};

#endif