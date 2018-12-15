#ifndef _ALPHABETA_H_
#define _ALPHABETA_H_

#include "cChess.h"

#define MAX_DEPTH 6

typedef struct abResult_t {
  int bestRes;
  move *mv;
} abResult;

typedef struct movesWithPlayer_t {
    move *mv;
    int player;
    int startPiece;
} movesWithPlayer;

move *calculateStepAB(int **board, int curPlayer);

#endif