#ifndef _ALPHABETA_H_
#define _ALPHABETA_H_

#include "cChess.h"

#define POSINF 19990
#define NEGINF -19990

#define MAX 1
#define MIN -1

#define MAX_DEPTH 7


move calculateStep(int board[10][9], int aiType, int curPlayer);
void makeMove (int board[10][9], int sr, int sc, int er, int ec);
bool gameOver(int board[10][9], int depth);

#endif