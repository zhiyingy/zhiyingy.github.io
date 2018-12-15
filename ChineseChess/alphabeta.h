#ifndef _ALPHABETA_H_
#define _ALPHABETA_H_

#include "cChess.h"

#define MAX_DEPTH 6

typedef struct abResult_t {
  int bestRes;
  Move *mv;
} abResult;

typedef struct movesWithPlayer_t {
    Move *mv;
    int player;
    int startPiece;
} movesWithPlayer;

Move *calculateStepAB(int **board, int curPlayer);

#endif