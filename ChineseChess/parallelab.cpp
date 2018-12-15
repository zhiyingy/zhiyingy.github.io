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

int **makeCopy (int **board) {
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

void freeBoard (int **board) {
    int i;
    for (i=0; i < 10; i++) {
        free(board[i]);
    }
    free(board);
}

abResult *seqABP(int curDepth, int alpha, int beta,
    int **board, int curPlayer) {
    move *bestMove;
    int score, endPiece;
    abResult *res = (abResult *)malloc(sizeof(abResult));


    if (curDepth == MAX_DEPTH|| gameOver(board) != 0) {
        res->bestRes = evaluate(board, curPlayer);
        return res;
    }

    std::vector<move *> possibleMoves = generateAllMoves(board, curPlayer);

    for (std::vector<move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        move *curMove = *it;
        endPiece = makeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec);
        abResult *curRes = seqABP(curDepth + 1, -beta, -alpha, board, flipPlayer(curPlayer));
        unmakeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec, endPiece);
        score = -curRes->bestRes;
        if (score >= beta) {
            res->bestRes = beta;
            res->mv = bestMove;
            free(curRes);
            return res;
        }

        if (score > alpha) {
            bestMove = curMove;
            alpha = score;
        }
        free(curRes);
    }

    res->bestRes = alpha;
    res->mv = bestMove;
    return res;
}


abResult *firstMoveSearch(int curDepth, int alpha, int beta,
    int **board, int curPlayer) {
    move *bestMove;
    volatile bool flag = false;
    abResult *res = (abResult *)malloc(sizeof(abResult));

    if (curDepth == MAX_DEPTH || gameOver(board) != 0) {
        res->bestRes = evaluate(board, curPlayer);
        return res;
    }

    std::vector<move *> possibleMoves = generateAllMoves(board, curPlayer);

    // if (curDepth == 0) {
    //     std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    // }

    move *firstMove = possibleMoves.at(0);
    int endPiece = makeMove(board, firstMove->sr, firstMove->sc, firstMove->er, firstMove->ec);
    abResult *firstRes = firstMoveSearch(curDepth + 1, -beta, -alpha, board, flipPlayer(curPlayer));
    unmakeMove(board, firstMove->sr, firstMove->sc, firstMove->er, firstMove->ec, endPiece);
    
    int score = -firstRes->bestRes;
    if (score >= beta) {
        free(firstRes);
        abResult *res = (abResult *)malloc(sizeof(abResult));
        res->bestRes = beta;
        res->mv = bestMove;
        return res;
    }
    if (alpha < score) {
        bestMove = firstMove;
        alpha = score;
    }

    if (possibleMoves.size() > 1)  {
        int i;
        #pragma omp parallel for default(shared) shared(flag, alpha, bestMove) private(i) schedule(dynamic)
        for (i = 1; i < possibleMoves.size(); i++) {
            if (flag) {
                continue;
            }
            else {
                int **boardCopy = makeCopy(board);
                move *curMove = possibleMoves.at(i);
                makeMove(boardCopy, curMove->sr, curMove->sc, curMove->er, curMove->ec);
                abResult *curRes = seqABP(curDepth + 1, -beta, -alpha, boardCopy, flipPlayer(curPlayer));
                freeBoard(boardCopy);

                int resScore = -curRes->bestRes;
                if (resScore >= beta) {
                    res->bestRes = beta;
                    res->mv = bestMove;
                    flag = true;
                }
            #pragma omp critical
                if (alpha < resScore) {
                    bestMove = curMove;
                    alpha = resScore;
                }
                free(curRes);
            }
        }
    }
    if (flag){
        return res;
    }
    res->bestRes = alpha;
    res->mv = bestMove;
    return res;
}

move *calculateStepAB(int **board, int curPlayer) {
    std::srand ( unsigned ( std::time(0) ) );
    abResult *res;
    res = firstMoveSearch(0, NEGINF, POSINF, board, curPlayer);
    move *m = res->mv;
    free(res);
    return m;
}
