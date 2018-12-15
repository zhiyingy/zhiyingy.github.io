#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__
#include "cChess.h"
#include <vector>

#define SIM 1000
#define C 1.4
#define MAXSTEP 1

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

#endif