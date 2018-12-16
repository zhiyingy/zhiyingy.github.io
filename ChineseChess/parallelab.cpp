#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <pthread.h>
#include <omp.h>
#include <chrono>
#include <limits.h>
#include "cChess.h"
#include "generateMove.h"
#include "evaluate.h"
#include "alphabeta.h"

abResult *seqABP(int curDepth, int alpha, int beta,
    int **board, int curPlayer) {
    Move *bestMove;
    int score, endPiece;
    abResult *res = (abResult *)malloc(sizeof(abResult));


    if (curDepth == MAX_DEPTH|| gameOver(board) != 0) {
        res->bestRes = evaluate(board, curPlayer);
        return res;
    }

    std::vector<Move *> possibleMoves = generateAllMoves(board, curPlayer);

    for (std::vector<Move *>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        Move *curMove = *it;
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
    using namespace std::chrono;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> dsec;

    Move *bestMove;
    volatile bool flag = false;
    abResult *res = (abResult *)malloc(sizeof(abResult));

    if (curDepth == MAX_DEPTH || gameOver(board) != 0) {
        res->bestRes = evaluate(board, curPlayer);
        return res;
    }

    std::vector<Move *> possibleMoves = generateAllMoves(board, curPlayer);

    // if (curDepth == 0) {
    //     std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    // }

    Move *firstMove = possibleMoves.at(0);
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
        auto startTime = Clock::now();
        #pragma omp parallel for default(shared) shared(flag, alpha, bestMove) private(i) schedule(dynamic)
        for (i = 1; i < possibleMoves.size(); i++) {
            if (flag) {
                continue;
            }
            else {
                int **boardCopy = makeCopy(board);
                Move *curMove = possibleMoves.at(i);
                auto st = Clock::now();
                makeMove(boardCopy, curMove->sr, curMove->sc, curMove->er, curMove->ec);
                abResult *curRes = seqABP(curDepth + 1, -beta, -alpha, boardCopy, flipPlayer(curPlayer));
                freeBoard(boardCopy);

                int resScore = -curRes->bestRes;
                if (curDepth == 0) {
                    std::cout << duration_cast<dsec>(Clock::now() - st).count() << " for thread "<<omp_get_thread_num()<<"\n";
                }
                if (resScore >= beta) {
                    res->bestRes = beta;
                    res->mv = bestMove;
                    flag = true;
                }
                // #pragma omp critical
                if (alpha < resScore) {
                    bestMove = curMove;
                    alpha = resScore;
                }
                free(curRes);
            }
        }
        std::cout << duration_cast<dsec>(Clock::now() - startTime).count() <<" used at level" << curDepth << "\n";
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
    Move *m = res->mv;
    free(res);
    return m;
}
