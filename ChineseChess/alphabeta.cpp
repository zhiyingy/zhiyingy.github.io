#include "alphabeta.h"
#include "cChess.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <limits.h>

//return the eaten piece
int makeMove (int board[10][9], int sr, int sc, int er, int ec){
    int piece = board[er][ec];
    board[er][ec] = board[sr][sc];
    board[sr][sc] = 0;
    return piece;
}

void unmakeMove (int board[10][9], int sr, int sc, int er, int ec, int piece){
    board[sr][sc] = board[er][ec];
    board[er][ec] = piece;
}

int gameOver(int board[10][9], int depth){
    int aiType;
    int i = 0;
    int j = 0;
    bool red = false;
    bool black = false;
    for (i = 0; i < 3; i++){
        for (j = 3; j<6; j++){
            if (board[i][j] == SHUAI * BLACK){
                black = true;
            }
            if (board[i][j] == SHUAI * RED) {
                red = true;
            }
        }
    }
    for (i=7; i<10; i++){
        for (j=3; j<6; j++){
            if (board[i][j] == SHUAI * BLACK){
                black = true;
            }
            if (board[i][j] == SHUAI * RED) {
                red = true;
            }
        }
    }

    aiType = (MAX_DEPTH - depth + 1) % 2;

    if (!red){
        if (aiType == 1){
            return 19990 + depth; //return max
        }else{
            return -19990 - depth; //return min
        }
    }
    if (!black){
        if (aiType == 1){
            return -19990 - depth; //return min
        }else{
            return 19990 + depth; //return max
        }
    }
    return 0;
}

void addMove(int r, int c, int x, int y, std::vector<move>* possibleMoves){
    move *curMove = (move *)calloc(1, sizeof(move));
    curMove->sr = r;
    curMove->sc = c;
    curMove->er = x;
    curMove->ec = y;
    (*possibleMoves).push_back(*curMove);
}

void gen_shuaimove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move>* possibleMoves) {
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
            for (y=3; y<6; y++) {
                if (isValidMove(board, r, c, x, y)){
                    addMove(r,c,x,y,possibleMoves);
                }
            }
        }
    }
}

void gen_shimove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move>* possibleMoves){
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
    std::vector<move>* possibleMoves){
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
    std::vector<move>* possibleMoves){
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
    std::vector<move>* possibleMoves){
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
    while (y < 10){
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
    std::vector<move>* possibleMoves){
    int x, y;
    if (curPlayer == RED) {
        x = r - 1;
        y = c;
        if (x >= 0 && board[x][y] * RED <= 0){
            addMove(r,c,x,y,possibleMoves);
        }
        x = r;
        y = c - 1;
        if (y >= 0 && board[x][y] * RED <= 0){
            addMove(r,c,x,y,possibleMoves);
        }
        y = c + 1;
        if (y < 9 && board[x][y] * RED <= 0){
            addMove(r,c,x,y,possibleMoves);
        }
    } else {
        x = r + 1;
        y = c;
        if (x < 10 && board[x][y] * BLACK <= 0){
            addMove(r,c,x,y,possibleMoves);
        }
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

void gen_paomove (int board[10][9], int r, int c, int curPlayer, 
    std::vector<move>* possibleMoves) {
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
    while (x >= 0){
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

std::vector<move> generateAllMoves(int board[10][9], int curPlayer){
    std::vector<move> possibleMoves;
    int i,j,piece;
    for (i = 0; i < 10; i++){
        for (j = 0; j < 9; j++) {
            piece = board[i][j];
            if (piece * curPlayer > 0) {
                switch(piece) {
                    case SHUAI: {
                        //red shuai or black shuai
                        gen_shuaimove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case SHI :{
                        gen_shimove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case XIANG: {
                        gen_xiangmove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case MA: {
                        gen_mamove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case JU: {
                        gen_jumove(board, i, j, curPlayer, &possibleMoves);
                        break;
                    }case ZU: {
                        gen_zumove(board, i, j, curPlayer, &possibleMoves);
                        break;
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

int negaMax(board[10][9], int depth) {
    int current = -20000;
    int score;
    int count, i;
    int piece;
    i = gameOver(board)
    if (i != 0){
        return i;
    }
    if (depth <= 0){
        return evaluate(board, (MAX_DEPTH-depth)%2);
    }
    std::vector<move> possibleMoves = generateAllMoves(board, curPlayer);
    if (curDepth == 0) {
        std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
    }
    for (std::vector<move_t>::iterator it = possibleMoves.begin(); it != possibleMoves.end(); it++){
        piece = makeMove(board, it);
    }
}

int minMaxSearch(int board[10][9], int depth, int aiType, int curPlayer) {
    // int best;
    // if (aiType == MAX) {
    //     best = NEGINF;
    // } else {
    //     best = POSINF;
    // }
    // if (depth <= 0) {
    //     evaluate();
    // }
    std::vector<move> possibleMoves = generateAllMoves(board, curPlayer);
    return 1;
}

// int evaluate() {
//     return 1;
// }

move calculateStep(int board[10][9], int aiType, int curPlayer) {
    // if (aiType == MAX) {

    // }
    move *curMove = (move *)calloc(1, sizeof(move));
    curMove->sr = 0;
    curMove->sc = 0;
    curMove->er = 0;
    curMove->ec = 0;
    return *curMove;
}