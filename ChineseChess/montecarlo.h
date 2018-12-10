#ifndef __MONTECARLO_H__
#define __MONTECARLO_H__
#include "cChess.h"

move *calculateStepMC(int **board, int curPlayer);

typedef struct mcResult_t {
  int bestRes;
  move *mv;
} mcResult;

typedef struct movesMC_t {
    move *mv;
    int player;
    int startPiece;
    int endPiece;
    bool visited;
} movesMC;

#endif