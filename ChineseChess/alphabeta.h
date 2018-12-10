#ifndef _ALPHABETA_H_
#define _ALPHABETA_H_

#include "cChess.h"

#define MAX 1
#define MIN -1

#define MAX_DEPTH 7

typedef struct minimaxResult_t {
  int bestRes;
  move *mv;
} minimaxResult;

typedef struct movesWithPlayer_t {
    move *mv;
    int player;
    int startPiece;
    int endPiece;
} movesWithPlayer;

move *calculateStepAB(int **board, int curPlayer);

#endif