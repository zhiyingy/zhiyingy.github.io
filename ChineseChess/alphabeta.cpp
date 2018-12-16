#include "alphabeta.h"
#include "cChess.h"
#include "evaluate.h"
#include "generateMove.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <limits.h>

abResult *minSearch(int curDepth, int alpha, int beta, int **board, int curPlayer, movesWithPiece* mp);

abResult *maxSearch(int curDepth, int alpha, int beta, int **board, int curPlayer, movesWithPiece* mp);

abResult *minSearch(int curDepth, int alpha, int beta, int **board, int curPlayer, movesWithPiece* mp) {
    //base case, has reached max depth or game over
    if (MAX_DEPTH == curDepth || gameOver(board) != 0) {
        int curScore = evaluate(board, curPlayer);
        abResult *res = new abResult(curScore, NULL);
        return res;
    }

    //make the move specified in mp
    makeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec);

    //generate all possible moves in the next round
    std::vector<Move*> possibleMoves = generateAllMoves(board, curPlayer);

    Move *bestMove = NULL;
    int resS = POSINF;

    //traverse possible moves
    for (std::vector<Move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        Move *curMove = *it;
        //construct the next move with player
        movesWithPiece *nextMp = (movesWithPiece *)malloc(sizeof(movesWithPiece));
        nextMp->mv = curMove;
        nextMp->endPiece = board[curMove->er][curMove->ec];
        //call max on counter player
        abResult *curRes = maxSearch(curDepth + 1, alpha, beta, board, flipPlayer(curPlayer), nextMp);
        
        //alpha beta pruning here
        if (curRes->bestRes < resS){
            resS = curRes->bestRes;
        }

        if (alpha <= curRes->bestRes && curRes->bestRes < beta) {
            bestMove = curMove;
        }

        if (resS < beta){
            beta = resS;
        }

        if (beta <= alpha) {
            delete(curRes);
            abResult *res = (abResult *)calloc(1,sizeof(abResult));
            res->bestRes = beta;
            res->mv = bestMove;
            unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
            return res;
        }
        delete(curRes);
    }
    abResult *res = (abResult *)calloc(1,sizeof(abResult));
    res->bestRes = resS;
    res->mv = bestMove;
    unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
    return res;
}

abResult *maxSearch(int curDepth, int alpha, int beta, int **board, int curPlayer, movesWithPiece* mp) {

    //base case
    if (MAX_DEPTH == curDepth || gameOver(board) != 0) {
        int curScore = evaluate(board, curPlayer);
        abResult *res = (abResult *)calloc(1,sizeof(abResult));
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }
    //if has move, make the move
    if (mp != NULL){
        makeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec);
    }
    
    //generate all possible moves
    std::vector<Move*> possibleMoves = generateAllMoves(board, curPlayer);

    //randomly shuffle
    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }

    Move *bestMove = NULL;
    int resS = NEGINF;

    for (std::vector<Move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        Move *curMove = *it;
        //construct next mv
        movesWithPiece *nextMp = (movesWithPiece *)malloc(sizeof(movesWithPiece));
        nextMp->mv = curMove;
        nextMp->endPiece = board[curMove->er][curMove->ec];

        //call min search
        abResult *curRes = minSearch(curDepth + 1, alpha, beta, board, flipPlayer(curPlayer), nextMp);

        //alpha beta pruning
        if (curRes->bestRes > resS){
            resS = curRes->bestRes;
        }

        if (alpha <= curRes->bestRes && curRes->bestRes <= beta) {
          bestMove = curMove;
        }

        if (resS > alpha) {
            alpha = resS;
        }

        if (beta <= alpha) {
            delete (curRes);
            abResult *res = new abResult(beta, bestMove);
            if (mp != NULL){
                unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
            }
            return res;
        }
        delete (curRes);
    }

    abResult *res = new abResult(resS, bestMove);
    if (mp != NULL) {
        unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
    }
    return res;
}

Move *calculateStepAB(int **board, int curPlayer) {
    std::srand (unsigned ( std::time(0) ) );

    abResult *res = maxSearch(0, NEGINF, POSINF, board, curPlayer, NULL);
    Move *m = res->mv;
    delete (res);
    return m;
}
