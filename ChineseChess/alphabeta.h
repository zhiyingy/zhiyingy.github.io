#ifndef _ALPHABETA_H_
#define _ALPHABETA_H_

#include "cChess.h"

#define MAX_DEPTH 6

typedef struct abResult_t {
  int bestRes;
  Move *mv;
} abResult;

typedef struct movesWithPiece_t {
    Move *mv;
    int endPiece;
} movesWithPiece;

Move *calculateStepAB(int **board, int curPlayer);

#endif