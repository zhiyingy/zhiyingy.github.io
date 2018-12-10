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

minimaxResult *mini(int curDepth, int maxDepth, int alpha, int beta,
    int **board, int curPlayer, std::vector<movesWithPlayer*> movesList);

minimaxResult *maxi(int curDepth, int maxDepth, int alpha, int beta,
    int **board, int curPlayer, std::vector<movesWithPlayer*> movesList);


int calcScore(int **board, int curPlayer, std::vector<movesWithPlayer*> movesList){
    for (std::vector<movesWithPlayer*>::iterator it = movesList.begin(); it != movesList.end(); it++){
        movesWithPlayer *mp = *it;
        mp->startPiece = board[mp->mv->sr][mp->mv->sc];
        mp->endPiece = board[mp->mv->er][mp->mv->ec];
        makeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec);
    }
    int curScore = evaluate(board, curPlayer);
    for (std::vector<movesWithPlayer*>::reverse_iterator it = movesList.rbegin(); it != movesList.rend(); it++){
        movesWithPlayer *mp = *it;
        unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
    }
    return curScore;
}

minimaxResult *mini(int curDepth, int maxDepth, int alpha, int beta,
    int **board, int curPlayer, std::vector<movesWithPlayer*> movesList) {
    
    // std :: cout << "mini called with depth " << curDepth <<" and max depth =" << maxDepth << "\n";

    if (maxDepth == curDepth || gameOver(board) != 0) {
        int curScore = calcScore(board, curPlayer, movesList);
        minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }

    for (std::vector<movesWithPlayer*>::iterator it = movesList.begin(); it != movesList.end(); it++){
        movesWithPlayer *mp = *it;
        mp->startPiece = board[mp->mv->sr][mp->mv->sc];
        mp->endPiece = board[mp->mv->er][mp->mv->ec];
        makeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec);
    }

    std::vector<move*> possibleMoves = generateAllMoves(board, curPlayer);

    for (std::vector<movesWithPlayer*>::reverse_iterator it = movesList.rbegin(); it != movesList.rend(); it++){
        movesWithPlayer *mp = *it;
        unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
    }

    move *bestMove = NULL;
    int resS = POSINF;
    int count = 0;
    for (std::vector<move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        count++;
        move *curMove = *it;
        // if (curMove -> ec < 0){
        //     std::cout << "wholy shit\n";
        // }

        std::vector<movesWithPlayer*> curMovesList = movesList;
        movesWithPlayer *mp = (movesWithPlayer *)calloc(1,sizeof(movesWithPlayer));
        mp->mv = curMove;
        mp->player = curPlayer;
        mp->startPiece = board[curMove->sr][curMove->sc];
        mp->endPiece = board[curMove->er][curMove->ec];
        curMovesList.push_back(mp);

        minimaxResult *curRes = maxi(curDepth + 1, maxDepth, alpha, beta, board, flipPlayer(curPlayer), curMovesList);
        if (curRes->bestRes < resS){
            resS = curRes->bestRes;
        }

        if (alpha <= curRes->bestRes && curRes->bestRes <= beta) {
            bestMove = curMove;
        }

        if (resS < beta){
            beta = resS;
        }

        if (beta <= alpha) {
            free(curRes);
            minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
            res->bestRes = beta;
            res->mv = bestMove;
            return res;
        }
        free(curRes);
    }
    minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
    res->bestRes = resS;
    res->mv = bestMove;
    return res;
}

minimaxResult *maxi(int curDepth, int maxDepth, int alpha, int beta,
    int **board, int curPlayer, std::vector<movesWithPlayer*> movesList) {

    // std :: cout << "maxi called with depth " << curDepth <<" and max depth =" << maxDepth << "\n";
    if (maxDepth == curDepth || gameOver(board) != 0) {
        int curScore = calcScore(board, curPlayer, movesList);
        minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
        res->bestRes = curScore;
        res->mv = NULL;
        return res;
    }

    for (std::vector<movesWithPlayer*>::iterator it = movesList.begin(); it != movesList.end(); it++){
        movesWithPlayer *mp = *it;
        mp->startPiece = board[mp->mv->sr][mp->mv->sc];
        mp->endPiece = board[mp->mv->er][mp->mv->ec];
        makeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec);
    }
    
    std::vector<move*> possibleMoves = generateAllMoves(board, curPlayer);

    for (std::vector<movesWithPlayer*>::reverse_iterator it = movesList.rbegin(); it != movesList.rend(); it++){
        movesWithPlayer *mp = *it;
        unmakeMove(board, mp->mv->sr, mp->mv->sc, mp->mv->er, mp->mv->ec, mp->endPiece);
    }

    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }

    move *bestMove = NULL;
    int resS = NEGINF;

    for (std::vector<move*>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++) {
        move *curMove = *it;
        // if (curMove -> ec < 0){
        //     std::cout << "wholy shit\n";
        // }


        std::vector<movesWithPlayer*> curMovesList = movesList;
        movesWithPlayer *mp = (movesWithPlayer *)calloc(1,sizeof(movesWithPlayer));
        mp->mv = curMove;
        mp->player = curPlayer;
        mp->startPiece = board[curMove->sr][curMove->sc];
        mp->endPiece = board[curMove->er][curMove->ec];
        curMovesList.push_back(mp);

        minimaxResult *curRes = mini(curDepth + 1, maxDepth, alpha, beta, board, flipPlayer(curPlayer), curMovesList);

        if (curRes->bestRes > resS){
            resS = curRes->bestRes;
        }

        // now undo this move
        if (alpha <= curRes->bestRes && curRes->bestRes <= beta) {
          bestMove = curMove;
        }

        if (resS > alpha) {
            alpha = resS;
        }

        if (beta <= alpha) {
            free(curRes);
            minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
            res->bestRes = beta;
            res->mv = bestMove;
            return res;
        }
        free(curRes);
    }
    minimaxResult *res = (minimaxResult *)calloc(1,sizeof(minimaxResult));
    res->bestRes = resS;
    res->mv = bestMove;
    return res;
}

move *calculateStepAB(int **board, int curPlayer) {
    std::srand (unsigned ( std::time(0) ) );

    std::vector<movesWithPlayer*> movesList;
    minimaxResult *res = maxi(0, MAX_DEPTH, NEGINF, POSINF, board, curPlayer, movesList);
    move *m = res->mv;
    free(res);
    return m;
    // return NULL;
}