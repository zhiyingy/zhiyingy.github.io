#include "alphabeta.h"
#include "cChess.h"
#include "evaluate.h"

#include "lib/CycleTimer.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <limits.h>

minimaxResult *mini(int curDepth, int maxDepth, int alpha, int beta,
    int board[10][9], int curPlayer, std::vector<movesWithPlayer*> movesList);

minimaxResult *maxi(int curDepth, int maxDepth, int alpha, int beta,
    int board[10][9], int curPlayer, std::vector<movesWithPlayer*> movesList);

//return the eaten piece
void makeMove (int board[10][9], int sr, int sc, int er, int ec){
    int piece = board[er][ec];
    board[er][ec] = board[sr][sc];
    board[sr][sc] = 0;
}

void unmakeMove (int board[10][9], int sr, int sc, int er, int ec, int piece){
    board[sr][sc] = board[er][ec];
    board[er][ec] = piece;
}

void addMove(int r, int c, int x, int y, std::vector<move*>* possibleMoves){
    move *curMove = (move *)calloc(1, sizeof(move));
    if (r < 0 || c < 0 || x < 0 || y < 0 || x > 9 || y > 8){
        std::cout << "why\n";
        return;
    }
    curMove->sr = r;
    curMove->sc = c;
    curMove->er = x;
    curMove->ec = y;
    (*possibleMoves).push_back(curMove);
}

void gen_shuaimove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves) {
    int x, y;
    if (curPlayer == BLACK) {
        for (x = 0; x < 3; x++){
            for (y = 3; y < 6; y++) {
                if (isValidMove(board, r, c, x, y)){
                    addMove(r,c,x,y,possibleMoves);
                }
            }
        }
    } else {
        for (x = 7; x<10; x++){
            for (y = 3; y<6; y++) {
                if (isValidMove(board, r, c, x, y)){
                    addMove(r,c,x,y,possibleMoves);
                }
            }
        }
    }
}

void gen_shimove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves){
    int x, y;
    if (curPlayer == RED){
        for (x = 7; x < 10; x++){
            for(y = 3; y < 6; y++) {
                if (isValidMove(board, r, c, x, y)){
                    addMove(r,c,x,y,possibleMoves);
                }
            }

        }
    }else{
        for (x=0;x<3;x++){
            for (y=3; y<6; y++){
                if (isValidMove(board, r, c, x, y)){
                    addMove(r,c,x,y,possibleMoves);
                }
            }
        }
    }
}

void gen_xiangmove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves){
    int x,y;
    x = r + 2;
    y = c + 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r + 2;
    y = c - 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r - 2;
    y = c - 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r - 2;
    y = c + 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }
}

void gen_mamove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves){
    int x, y;
    x = r + 2;
    y = c + 1;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r + 2;
    y = c - 1;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r - 2;
    y = c + 1;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r - 2;
    y = c - 1;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r + 1;
    y = c + 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r + 1;
    y = c - 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r - 1;
    y = c + 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }

    x = r - 1;
    y = c - 2;
    if (isValidMove(board, r, c, x, y)){
        addMove(r,c,x,y,possibleMoves);
    }
}

void gen_jumove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves){
    int x, y;
    //all down moves
    x = r + 1;
    y = c;
    while (x < 10){
        if (board[x][y] == 0){
            addMove(r,c,x,y,possibleMoves);
        }else {
            if (board[x][y] * curPlayer < 0){
                addMove(r,c,x,y,possibleMoves);
            }
            break;
        }
        x++;
    }
    x = r - 1;
    y = c;
    while (x >= 0){
        if (board[x][y] == 0){
            addMove(r,c,x,y,possibleMoves);
        }else {
            if (board[x][y] * curPlayer < 0){
                addMove(r,c,x,y,possibleMoves);
            }
            break;
        }
        x--;
    }

    x = r;
    y = c + 1;
    while (y < 9){
        if (board[x][y] == 0){
            addMove(r,c,x,y,possibleMoves);
        }else {
            if (board[x][y] * curPlayer < 0){
                addMove(r,c,x,y,possibleMoves);
            }
            break;
        }
        y++;
    }

    x = r;
    y = c - 1;
    while (y >= 0){
        if (board[x][y] == 0){
            addMove(r,c,x,y,possibleMoves);
        }else {
            if (board[x][y] * curPlayer < 0){
                addMove(r,c,x,y,possibleMoves);
            }
            break;
        }
        y--;
    }

}

void gen_zumove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves){
    int x, y;
    if (curPlayer == RED) {
        x = r - 1;
        y = c;
        if (x >= 0 && board[x][y] * RED <= 0){
            addMove(r,c,x,y,possibleMoves);
        }

        if (r<5){
            x = r;
            y = c - 1;
            if (y >= 0 && board[x][y] * RED <= 0){
                addMove(r,c,x,y,possibleMoves);
            }
            y = c + 1;
            if (y < 9 && board[x][y] * RED <= 0){
                addMove(r,c,x,y,possibleMoves);
            }
        }
        
    } else {
        x = r + 1;
        y = c;
        if (x < 10 && board[x][y] * BLACK <= 0){
            addMove(r,c,x,y,possibleMoves);
        }
        if (r > 4){
            x = r;
            y = c - 1;
            if (y >= 0 && board[x][y] * BLACK <= 0){
                addMove(r,c,x,y,possibleMoves);
            }
            y = c + 1;
            if (y < 9 && board[x][y] * BLACK <= 0){
                addMove(r,c,x,y,possibleMoves);
            }
        }

    }
}

void gen_paomove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move*>* possibleMoves) {
    int x, y;
    bool hasEncountered = false;
    x = r;
    y = c + 1;
    while (y < 9) {
        if(board[x][y] == 0){
            if (!hasEncountered){
                addMove(r,c,x,y,possibleMoves);
            }
        }else{
            if (!hasEncountered){
                hasEncountered = true;
            }else{
                if(board[x][y]*curPlayer < 0){
                    addMove(r,c,x,y,possibleMoves);
                }
                break;
            }
        }
        y++;
    }

    y = c - 1;
    hasEncountered = false;
    while (y >= 0){
        if(board[x][y] == 0){
            if (!hasEncountered){
                addMove(r,c,x,y,possibleMoves);
            }
        }else{
            if (!hasEncountered){
                hasEncountered = true;
            }else{
                if(board[x][y]*curPlayer < 0){
                    addMove(r,c,x,y,possibleMoves);
                }
                break;
            }
        }
        y--;
    }

    x = r + 1;
    y = c;
    hasEncountered = false;
    while (x<10){
        if(board[x][y] == 0){
            if (!hasEncountered){
                addMove(r,c,x,y,possibleMoves);
            }
        }else{
            if (!hasEncountered){
                hasEncountered = true;
            }else{
                if(board[x][y]*curPlayer < 0){
                    addMove(r,c,x,y,possibleMoves);
                }
                break;
            }
        }
        x++;
    }

    x = r - 1;
    hasEncountered = false;
    while (x>=0){
        if(board[x][y] == 0){
            if (!hasEncountered){
                addMove(r,c,x,y,possibleMoves);
            }
        }else{
            if (!hasEncountered){
                hasEncountered = true;
            }else{
                if(board[x][y]*curPlayer < 0){
                    addMove(r,c,x,y,possibleMoves);
                }
                break;
            }
        }
        x--;
    }
}

std::vector<move*> generateAllMoves(int board[10][9], int curPlayer){
    std::vector<move*> possibleMoves;
    int i,j,piece;
    for (i = 0; i < 10; i++){
        for (j = 0; j < 9; j++) {
            piece = board[i][j];
            if (piece * curPlayer > 0) {
                switch(piece) {
                    case SHUAI * RED:{

                    }case SHUAI: {
                        //red shuai or black shuai
                        gen_shuaimove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case SHI * RED:{

                    }case SHI :{
                        gen_shimove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case XIANG * RED:{

                    }case XIANG: {
                        gen_xiangmove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case MA * RED:{

                    }case MA: {
                        gen_mamove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case JU * RED:{

                    }case JU: {
                        gen_jumove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case ZU * RED:{

                    }case ZU: {
                        gen_zumove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case PAO * RED:{

                    }case PAO: {
                        gen_paomove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }
                }
            }
        }
    }
    return possibleMoves;
}

int calcScore(int board[10][9], int curPlayer, std::vector<movesWithPlayer*> movesList){
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
    int board[10][9], int curPlayer, std::vector<movesWithPlayer*> movesList) {
    
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
    int board[10][9], int curPlayer, std::vector<movesWithPlayer*> movesList) {

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

        // double startTime, endTime;
        // if (curDepth == 0) {
        //     startTime = CycleTimer::currentSeconds();
        // }
        minimaxResult *curRes = mini(curDepth + 1, maxDepth, alpha, beta, board, flipPlayer(curPlayer), curMovesList);
        // if (curDepth == 0) {
        //     endTime = CycleTimer::currentSeconds();
        // }

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

move *calculateStep(int board[10][9], int curPlayer) {
    std::srand (unsigned ( std::time(0) ) );

    std::vector<movesWithPlayer*> movesList;
    minimaxResult_t *res = maxi(0, MAX_DEPTH, NEGINF, POSINF, board, curPlayer, movesList);
    move *m = res->mv;
    free(res);
    return m;
    // return NULL;
}