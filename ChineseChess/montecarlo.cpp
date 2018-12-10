#include "montecarlo.h"
#include "cChess.h"
#include "evaluate.h"
#include <stdio.h>
#include <stdlib.h>

// void expand(){

// }

// void simulation(){

// }

// void backup(){

// }

// mcResult *mcts(int board[10][9], int curPlayer,
//     int simulation, int maxSimulation, std::vector<movesMC*> movesList){

//     if (simulation == maxSimulation || gameOver(board)!=0){
//         int curScore = calcScore(board, curPlayer, movesList);
//         minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
//         res->bestRes = curScore;
//         res->mv = NULL;
//         return res;
//     }
//     mcts(board, simulation+1, maxSimulation);
// }

move *calculateStepMC(int **board, int curPlayer){
    // std::vector<movesMC*> movesList;
    return NULL;
}