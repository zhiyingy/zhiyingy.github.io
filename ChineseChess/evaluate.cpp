#include "evaluate.h"
#include "cChess.h"
#include "alphabeta.h"
#include <limits.h>

int evaluate(int **board, int curPlayer){
    int redTo = 0;
    int blackTo = 0;
    bool blackAlive = false;
    bool redAlive = false;
    int i, j, piece;
    for (i=0; i<10; i++){
        for (j=0; j<9; j++){
            if (board[i][j]==0){
                piece = board[i][j];
                switch(piece){
                    case SHUAI * RED:{
                        redAlive = true;
                        break;
                    }case SHUAI * BLACK:{
                        blackAlive = true;
                        break;
                    }case SHI * RED:{
                        redTo = redTo + B_SHI;
                        break;
                    }case SHI * BLACK:{
                        blackTo = blackTo + B_SHI;
                        break;
                    }case XIANG * RED:{
                        redTo = redTo + B_XIANG;
                        break;
                    }case XIANG * BLACK:{
                        blackTo = blackTo + B_XIANG;
                        break;
                    }case MA * RED:{
                        redTo = redTo + B_MA + RMAPLUS[i][j];
                        break;
                    }case MA * BLACK:{
                        blackTo = blackTo + B_MA + BMAPLUS[i][j];
                        break;
                    }case JU * RED:{
                        redTo = redTo + B_JU + RJUPLUS[i][j];
                        break;
                    }case JU * BLACK:{
                        blackTo = blackTo + B_JU + BJUPLUS[i][j];
                        break;
                    }case PAO * RED:{
                        redTo = redTo + B_PAO + RPAOPLUS[i][j];
                        break;
                    }case PAO * BLACK:{
                        blackTo = blackTo + B_PAO + BPAOPLUS[i][j];
                        break;
                    }case ZU * RED:{
                        redTo = redTo + B_ZU + RZUPLUS[i][j];
                        break;
                    }case ZU * BLACK:{
                        blackTo = blackTo + B_ZU + BZUPLUS[i][j];
                        break;
                    }
                }
            }
        }
    }
    if (curPlayer == RED){
        if (!blackAlive){
            return POSINF;
        }
        if (!redAlive){
            return NEGINF;
        }
        return redTo - blackTo;
    }

    if (!blackAlive){
        return NEGINF;
    }
    if (!redAlive){
        return POSINF;
    }
    return blackTo - redTo;
}