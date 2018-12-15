#include <vector>
#include "cChess.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "generateMove.h"

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

void gen_shuaimove (int **board, int r, int c, int curPlayer, 
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

void gen_shimove (int **board, int r, int c, int curPlayer, 
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

void gen_xiangmove (int **board, int r, int c, int curPlayer, 
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

void gen_mamove (int **board, int r, int c, int curPlayer, 
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

void gen_jumove (int **board, int r, int c, int curPlayer, 
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

void gen_zumove (int **board, int r, int c, int curPlayer, 
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

void gen_paomove (int **board, int r, int c, int curPlayer, 
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

std::vector<move*> generateAllMoves(int **board, int curPlayer){
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