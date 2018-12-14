#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include <omp.h>
#include <limits.h>
#include "lib/CycleTimer.h"
#include "cChess.h"
#include "generateMove.h"
#include "evaluate.h"
#include "alphabeta.h"

int **deepCopyBoard (int **board) {
    int i, j;
    int **result = (int **)malloc(10 * sizeof(int *));
    for (i=0; i < 10; i++) {
        result[i] = (int *)malloc(9 * sizeof(int));
        for (j=0; j<9; j++){
            result[i][j] = board[i][j];
        }
    }
    return result;
}

void deepFreeBoard (int **board) {
    int i;
    for (i=0; i < 10; i++) {
        free(board[i]);
    }
    free(board);
}

minimaxResult *seqABP(int curDepth, int maxDepth, int alpha, int beta,
    int **board, int curPlayer) {
    if (curDepth == maxDepth|| gameOver(board) != 0) {
        int curScore = evaluate(board, curPlayer);
        minimaxResult *res = (minimaxResult *)malloc(sizeof(minimaxResult));
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }

    std::vector<move *> possibleMoves = generateAllMoves(board, curPlayer);
  
    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }

    move *bestMove = NULL;

    for (std::vector<move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        move *curMove = *it;
        int startPiece = board[curMove->sr][curMove->sc];
        int endPiece = board[curMove->er][curMove->ec];

        makeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec);

        minimaxResult *curRes = seqABP(curDepth + 1, maxDepth, -beta, -alpha, board,
            flipPlayer(curPlayer));
        int resS = -(curRes->bestRes);

        unmakeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec, endPiece);

        if (beta <= resS) {
            free(curRes);
            minimaxResult *res = (minimaxResult *)malloc(sizeof(minimaxResult));
            res->bestRes = beta;  // returning alpha bc thats the max value (maxing in maxi and - in upper level is equiv to min'ing in mini)
            res->mv = bestMove;
            return res;
            }

        if (alpha < resS) {
            bestMove = curMove;
            alpha = resS;
        }
        free(curRes);
    }

    minimaxResult *res = (minimaxResult *)malloc(sizeof(minimaxResult));
    res->bestRes = alpha;
    res->mv = bestMove;
    return res;
}


minimaxResult *firstMoveSearch(int curDepth, int maxDepth, int alpha, int beta,
    int **board, int curPlayer) {

    if (curDepth == maxDepth|| gameOver(board) != 0) {
        int curScore = evaluate(board, curPlayer);
        minimaxResult *res = (minimaxResult *)malloc(sizeof(minimaxResult));
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }

    std::vector<move *> possibleMoves = generateAllMoves(board, curPlayer);

    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }

    move *bestMove = NULL;

    move *firstMove = possibleMoves.at(0);
    int startPiece = board[firstMove->sr][firstMove->sc];
    int endPiece = board[firstMove->er][firstMove->ec];
    makeMove(board, firstMove->sr, firstMove->sc, firstMove->er, firstMove->ec);
    minimaxResult *firstRes = firstMoveSearch(curDepth + 1, maxDepth, -beta, -alpha, board, flipPlayer(curPlayer));
    firstRes->bestRes = -(firstRes->bestRes);
    int resS = firstRes->bestRes;
    unmakeMove(board, firstMove->sr, firstMove->sc, firstMove->er, firstMove->ec, endPiece);
    
    if (resS > beta) {
        free(firstRes);
        minimaxResult *res = (minimaxResult *)malloc(sizeof(minimaxResult));
        res->bestRes = beta;
        res->mv = bestMove;
        return res;
    }
    if (alpha < resS) {
        bestMove = firstMove;
        alpha = resS;
    }

    if (int(possibleMoves.size()) > 1)  {
        volatile bool flag = false;
        int i;
        #pragma omp parallel for default(shared) shared(flag, alpha, bestMove) private(i) schedule(dynamic)
        for (i = 1; i < possibleMoves.size(); i++) {

            if (flag) {
                continue;
            }
            else {
                move *curMove = possibleMoves.at(i);
                int startPiece = board[curMove->sr][curMove->sc];
                int endPiece = board[curMove->er][curMove->ec];

                int **boardCopy = deepCopyBoard(board);
                // we know curMove is valid
                makeMove(boardCopy, curMove->sr, curMove->sc, curMove->er, curMove->ec);
                minimaxResult *curRes = seqABP(curDepth + 1, maxDepth, -beta, -alpha, boardCopy, flipPlayer(curPlayer));
                int resS = -(curRes->bestRes);
                deepFreeBoard(boardCopy);

                if (resS >= beta) {
                    free(curRes);
                    minimaxResult *res = (minimaxResult*)malloc(sizeof(minimaxResult));
                    res->bestRes = beta;
                    res->mv = bestMove;
                    flag = true;
                }
            #pragma omp critical
                if (alpha < resS) {
                    bestMove = curMove;
                    alpha = curRes->bestRes;
                }
                free(curRes);
            }
        }
    }
    minimaxResult *res = (minimaxResult *)malloc(sizeof(minimaxResult));
    res->bestRes = alpha;
    res->mv = bestMove;
    return res;
}

move *calculateStepAB(int **board, int curPlayer) {
    std::srand ( unsigned ( std::time(0) ) );
    // AI is called to help les goooooo!!!
    minimaxResult *res;
    res = firstMoveSearch(0, MAX_DEPTH, NEGINF, POSINF, board, curPlayer);
    move *m = res->mv;
    free(res);
    return m;
  // return NULL;
}
