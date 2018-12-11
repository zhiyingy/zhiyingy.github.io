#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__
#include "cChess.h"
#include <vector>

#define EXP_RATE = 12000;
#define SIM = 1000;

move *calculateStepMC(int **board, int curPlayer);

typedef struct movesMC_t {
	struct movesMC_t *parent;
    move *mv;
    int nextIndex;
    float score;
    std::vector<move*> possibleMoves;
    std::vector<struct movesMC_t *> children;
} movesMC;

#endif