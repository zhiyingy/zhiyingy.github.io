#include "evaluate.h"
#include "cChess.h"
#include "alphabeta.h"
#include <limits.h>

int evaluate(int **board, int curPlayer){
    int redTo = 0;
    int blackTo = 0;
    int i, j, piece;
    for (i=0; i<10; i++){
        for (j=0; j<9; j++){
            if (board[i][j]!=0){
                piece = board[i][j];
                switch(piece){
                    case SHUAI * RED:{
                        redTo += B_SHUAI;
                        break;
                    }case SHUAI * BLACK:{
                        blackTo += B_SHUAI;
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
                        redTo = redTo + B_MA;
                        break;
                    }case MA * BLACK:{
                        blackTo = blackTo + B_MA;
                        break;
                    }case JU * RED:{
                        redTo = redTo + B_JU;
                        break;
                    }case JU * BLACK:{
                        blackTo = blackTo + B_JU;
                        break;
                    }case PAO * RED:{
                        redTo = redTo + B_PAO;
                        break;
                    }case PAO * BLACK:{
                        blackTo = blackTo + B_PAO;
                        break;
                    }case ZU * RED:{
                        redTo = redTo + B_ZU;
                        break;
                    }case ZU * BLACK:{
                        blackTo = blackTo + B_ZU;
                        break;
                    }
                }
            }
        }
    }
    if (curPlayer == RED){
        return redTo - blackTo;
    }
    return blackTo - redTo;
}