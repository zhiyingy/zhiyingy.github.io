#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <omp.h>
#include <limits.h>
#include <chrono>
#include "cChess.h"
#include "generateMove.h"
#include "evaluate.h"
#include "alphabeta.h"

abResult *seqABP(int curDepth, int alpha, int beta, int **board, int curPlayer) {
    if (curDepth == MAX_DEPTH|| gameOver(board) != 0) {
        int curScore = evaluate(board, curPlayer);
        abResult *res = (abResult *)malloc(sizeof(abResult));
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }

    std::vector<Move *> possibleMoves = generateAllMoves(board, curPlayer);
  
    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }

    Move *bestMove = NULL;

    for (std::vector<Move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        Move *curMove = *it;
        int startPiece = board[curMove->sr][curMove->sc];
        int endPiece = endPiece = board[curMove->er][curMove->ec];

        makeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec);

        abResult *curRes = seqABP(curDepth + 1, -beta, -alpha, board,
            flipPlayer(curPlayer));
        int resS = -(curRes->bestRes);

        unmakeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec, endPiece);

        if (beta <= resS) {
            free(curRes);
            abResult *res = (abResult *)malloc(sizeof(abResult));
            res->bestRes = beta;
            res->mv = bestMove;
            return res;
            }

        if (alpha < resS) {
            bestMove = curMove;
            alpha = resS;
        }
        free(curRes);
    }

    abResult *res = (abResult *)malloc(sizeof(abResult));
    res->bestRes = alpha;
    res->mv = bestMove;
    return res;
}


abResult *firstMoveSearch(int curDepth, int alpha, int beta, int **board, int curPlayer) {
    using namespace std::chrono;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> dsec;

    abResult *res = (abResult *)malloc(sizeof(abResult));

    if (curDepth == MAX_DEPTH|| gameOver(board) != 0) {
        int curScore = evaluate(board, curPlayer);
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }

    std::vector<Move *> possibleMoves = generateAllMoves(board, curPlayer);

    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }

    Move *bestMove = NULL;
    volatile bool flag = false;

    if (int(possibleMoves.size()) > 0)  {
        int i;
        double totalTime = 0.0;
        auto init_start = Clock::now();
        #pragma omp parallel for default(shared) shared(flag, alpha, bestMove, totalTime) private(i) schedule(dynamic)
        for (i = 0; i < possibleMoves.size(); i++) {
            if (flag) {
                continue;
            }
            else {
                Move *curMove = possibleMoves[i];
                int startPiece = board[curMove->sr][curMove->sc];
                int endPiece = board[curMove->er][curMove->ec];
                int **boardCopy = makeCopy(board);
                makeMove(boardCopy, curMove->sr, curMove->sc, curMove->er, curMove->ec);
                abResult *curRes = seqABP(curDepth + 1, -beta, -alpha, boardCopy, flipPlayer(curPlayer));
                int resScore = -(curRes->bestRes);
                freeBoard(boardCopy);
                if (resScore >= beta) {
                    res->bestRes = beta;
                    res->mv = bestMove;
                    flag = true;
                }
            #pragma omp critical
                if (alpha < resScore) {
                    bestMove = curMove;
                    alpha = curRes->bestRes;
                }
                free(curRes);
            }
        }
        totalTime += duration_cast<dsec>(Clock::now() - init_start).count();
        std::cout << totalTime << "\n";

    }
    if (flag){
        return res;
    }
    res->bestRes = alpha;
    res->mv = bestMove;
    return res;
}

Move *calculateStepAB(int **board, int curPlayer) {
    std::srand ( unsigned ( std::time(0) ) );
    abResult *res;
    res = firstMoveSearch(0, NEGINF, POSINF, board, curPlayer);
    Move *m = new Move(0,0,0,0);
    // Move *m = res->mv;
    free(res);
    return m;
}
