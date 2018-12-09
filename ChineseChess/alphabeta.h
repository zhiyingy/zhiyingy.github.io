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

move *calculateStep(int board[10][9], int curPlayer);
void makeMove (int board[10][9], int sr, int sc, int er, int ec);
// int gameOver(int board[10][9], int depth);

#endif