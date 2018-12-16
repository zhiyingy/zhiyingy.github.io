#ifndef _ALPHABETA_H_
#define _ALPHABETA_H_

#include "cChess.h"

#define MAX_DEPTH 6

class abResult{
	public:
		int bestRes;
		Move *mv;
		abResult(int res, Move* m) {
			bestRes = res;
			mv = m;
		}
};

typedef struct movesWithPiece_t {
    Move *mv;
    int endPiece;
} movesWithPiece;

Move *calculateStepAB(int **board, int curPlayer);

#endif