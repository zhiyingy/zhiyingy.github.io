#ifndef _GENERATEMOVE_H_
#define _GENERATEMOVE_H_
#include <vector>
#include "cChess.h"

std::vector<Move*> generateAllMoves(int **board, int curPlayer);

#endif