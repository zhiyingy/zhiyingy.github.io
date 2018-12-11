#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__
#include "cChess.h"

#define EXP_RATE = 12000;
#define SIM = 1000;

move *calculateStepMC(int **board, int curPlayer);

typedef struct mcResult_t {
  int bestRes;
  move *mv;
} mcResult;

typedef struct movesMC_t {
	movesMC *parent;
    move *mv;
    int nextIndex;
    float score;
    std::vector<move*> possibleMoves;
    std::vector<movesMC*> children;
} movesMC;

#endif