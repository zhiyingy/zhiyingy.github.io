#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <omp.h>
#include <cstring>
#include <iostream>
#include "lib/CycleTimer.h"
#include "alphabeta.h"
#include "montecarlo.h"
using namespace std;

#include "cChess.h"
#include "alphabeta.h"

static int _argc;
static const char **_argv;

const char *get_option_string(const char *option_name,
            const char *default_value)
{
    for (int i = _argc - 2; i >= 0; i -= 2)
        if (strcmp(_argv[i], option_name) == 0)
            return _argv[i + 1];
    return default_value;
}

int get_option_int(const char *option_name, int default_value)
{
    for (int i = _argc - 2; i >= 0; i -= 2)
        if (strcmp(_argv[i], option_name) == 0)
            return atoi(_argv[i + 1]);
    return default_value;
}

int flipPlayer(int curPlayer){
    if (curPlayer == RED){
        return BLACK;
    }
    return RED;
}

//return the eaten piece
int makeMove (int **board, int sr, int sc, int er, int ec){
    int piece = board[er][ec];
    board[er][ec] = board[sr][sc];
    board[sr][sc] = 0;
    return piece;
}

void unmakeMove (int **board, int sr, int sc, int er, int ec, int piece){
    board[sr][sc] = board[er][ec];
    board[er][ec] = piece;
}

//return the winner
int gameOver(int **board) {
    bool redAlive = false;
    bool blackAlive = false;
    int i, j;
    for (i = 0; i < 3; i++){
        for (j = 3; j<6; j++){
            if (board[i][j] == SHUAI * BLACK){
                blackAlive = true;
            }
            if (board[i][j] == SHUAI * RED) {
                redAlive = true;
            }
        }
    }
    for (i=7; i<10; i++){
        for (j=3; j<6; j++){
            if (board[i][j] == SHUAI * BLACK){
                blackAlive = true;
            }
            if (board[i][j] == SHUAI * RED) {
                redAlive = true;
            }
        }
    }
    if (!blackAlive){
        return RED;
    }
    if (!redAlive){
        return BLACK;
    }
    return 0;
}

void printBoard(int **board){
    for (int r = 0; r < 10; r++) {
        for (int j = 0; j < 9; j++) {
            if (board[r][j] >= 0){
                cout << " ";
            }
            cout << board[r][j] << " ";
        }
        cout << "\n";
    }
}

bool isValidMove(int **board,int sr, int sc, int er, int ec){
    if (er == sr && ec == sc) {
        //cannot donnot move
        return false;
    }
    if (er < 0 || er >= 10 || ec < 0 || ec >= 9){
        return false;
    }
    int piece = board[sr][sc];
    int endPiece = board[er][ec];
    if (piece * endPiece > 0){
        // cout << "Cannot eat your own side\n";
        return false;
    }

    switch (piece) {
        case SHUAI * RED: {
            //Shuai
            //checkmate condition
            if (board[er][ec] == SHUAI * BLACK){
                if (ec != sc) {
                    // cout << "Two Jiang must be at the same col\n";
                    return false;
                }
                for (int r = er+1; r < sr; r++) {
                    if (board[r][ec] != 0){
                        // cout << "Cannot checkmate with pieces in between\n";
                        return false;
                    }
                }
            } else if (ec < 3 || ec >5 || er < 7) {
                // cout << "Can not move Shuai outside the bound\n";
                return false;
            } else if (abs(ec-sc) + abs(er-sr) != 1) {
                // cout << "Invalid Shuai Move, can only move up, down, left, right by one\n";
                return false;
            }
            break;
        }case SHUAI * BLACK: {
            if (board[er][ec] == RED * SHUAI){
                if (ec != sc){
                    return false;
                }

                for (int r = sr+1; r < er; r++) {
                    if (board[r][ec] != 0){
                        // cout << "Cannot checkmate with pieces in between\n";
                        return false;
                    }
                }
            } else if (ec < 3 || ec >5 || er > 2) {
                // cout << "Can not move Shuai outside the bound\n";
                return false;
            } else if (abs(ec-sc) + abs(er-sr) != 1) {
                // cout << "Invalid Shuai Move, can only move up, down, left, right by one\n";
                return false;
            }
            break;
        }case SHI * RED:{
            //SHI
            if (er < 7 || ec > 5 || ec < 3){
                return false;
            }
            if (abs(er-sr) !=1 || abs(ec-sc) != 1){
                return false;
            }
            break;
        }case SHI * BLACK: {
            if (er > 2 || ec > 5 || ec < 3) {
                return false;
            }
            if (abs(sr - er) != 1 || abs(ec-sc) != 1){
                return false;
            }
            break;
        }case XIANG * RED: {
            //XIANG
            if (er < 5){
                // cout << "Xiang cannot pass the bound\n";
                return false;
            }
            if (abs(ec-sc) != 2 || abs(er-sr) != 2){
                // cout << "Xiang can move exactly two spaces diagonally\n";
                return false;
            }
            int midr = sr < er ? sr + 1 : er + 1;
            int midc = sc < ec ? sc + 1 : ec + 1;
            if (board[midr][midc] != 0){
                // cout << "Xiang cannot move cross occupied points\n";
                return false;
            }
            break;
        }case XIANG * BLACK: {
            if (er > 4) {
                return false;
            }
            if (abs(ec-sc) != 2 || abs(er-sr) != 2){
                // cout << "Xiang can move exactly two spaces diagonally\n";
                return false;
            }
            int midr = sr < er ? sr + 1 : er + 1;
            int midc = sc < ec ? sc + 1 : ec + 1;
            if (board[midr][midc] != 0){
                // cout << "Xiang cannot move cross occupied points\n";
                return false;
            }
            break;
        }case MA * BLACK:{

        }case MA * RED: {
            //MA
            if (abs(ec-sc) + abs(er-sr) != 3 || abs(ec-sc) < 1 || abs(er-sr) < 1) {
                // cout << "Ma moves one space vertically or horizontally, followed by one space outward-diagonally.\n";
                return false;
            }
            if (abs(ec-sc) == 1){
                //move vertically first
                int midr = sr < er ? sr + 1 : er + 1;
                if (board[midr][sc] != 0) {
                    return false;
                }
            } else {
                int midc = sc < ec ? sc + 1 : ec + 1;
                if (board[sr][midc] != 0){
                    return false;
                }
            }
            break;
        } case JU * BLACK: {

        } case JU * RED: {
            //JU
            if (er != sr && ec != sc) {
                // cout << "Ju can only move vertically or horizontally.\n";
                return false;
            }
            if (er == sr) {
                int minc = sc < ec ? sc : ec;
                int maxc = sc < ec ? ec : sc;
                for (int c = minc+1; c < maxc; c++) {
                    if (board[sr][c] != 0){
                        // cout << "Ju cannot move cross pieces.\n";
                        return false;
                    }
                }
            } else {
                int minr = sr < er ? sr : er;
                int maxr = sr < er ? er : sr;
                for (int r = minr +1; r < maxr; r++) {
                    if (board[r][sc] != 0){
                        // cout << "Ju cannot move cross pieces.\n";
                        return false;
                    }
                }
            }
            break;
        } case PAO * BLACK : {

        } case PAO * RED: {
            //Pao
            if (er != sr && ec != sc) {
                // cout << "Pao can only move vertically or horizontally.\n";
                return false;
            }
            int count = 0;
            if (er == sr) {
                //move horizonally
                int minc = sc < ec ? sc : ec;
                int maxc = sc < ec ? ec : sc;
                for (int c = minc+1; c < maxc; c++) {
                    if (board[sr][c] != 0){
                        count++;
                    }
                }
            } else{
                //move vertically
                int minr = sr < er ? sr : er;
                int maxr = sr < er ? er : sr;
                for (int r = minr +1; r < maxr; r++) {
                    if (board[r][sc] != 0){
                        count++;
                    }
                }
            }
            if (board[er][ec] == 0 && count!=0){
                // cout << "Pao cannot move cross pieces if it's not eating one.\n";
                return false;
            } else if (board[er][ec]!=0 && count != 1){
                // cout << "Pao cannot eat piece without crossing exactly one other piece.\n";
                return false;
            }
            break;
        } case ZU * BLACK:{
            if (er < sr){
                return false;
            }
            if (sr < 5 && sr == er) {
                return false;
            }
            if (er - sr + abs(ec-sc) > 1) {
                return false;
            }
            break;
        } case ZU * RED: {
            //bin
            if (er > sr){
                return false;
            }
            if (sr > 4 && er == sr) {
                return false;
            }
            if (sr - er + abs(ec-sc) > 1){
                return false;
            }
            break;
        }
    }
    return true;
}

void initializeBoard(int **board){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 9; j++){
            board[i][j] = 0;
        }
    }
    board[0][0]=2;
    board[0][1]=3;
    board[0][2]=6;
    board[0][3]=5;
    board[0][4]=1;
    board[0][5]=5;
    board[0][6]=6;
    board[0][7]=3;
    board[0][8]=2;

    board[2][1]=4;
    board[2][7]=4;

    board[3][0]=7;
    board[3][2]=7;
    board[3][4]=7;
    board[3][6]=7;
    board[3][8]=7;

    board[6][0]=-7;
    board[6][2]=-7;
    board[6][4]=-7;
    board[6][6]=-7;
    board[6][8]=-7;

    board[7][1]=-4;
    board[7][7]=-4;

    board[9][0]=-2;
    board[9][1]=-3;
    board[9][2]=-6;
    board[9][3]=-5;
    board[9][4]=-1;
    board[9][5]=-5;
    board[9][6]=-6;
    board[9][7]=-3;
    board[9][8]=-2;
}


int main(int argc, const char *argv[]) {
    double startTime, endTime, timeUsed;
    int piece;
    int aiType;
    move *mB;
    _argc = argc - 1;
    _argv = argv + 1;

    const char *algo_type = get_option_string("-m", NULL);
    int num_of_threads = get_option_int("-n", 1);

    if (algo_type[0] == 'm'){
        aiType = MCST;
    } else{
        aiType = AB;
    }

    cout << omp_get_max_threads() << "\n";
    omp_set_num_threads(num_of_threads);
    
    int **board = (int **)malloc(10 * sizeof(int *));
    for (int i=0; i<10; i++) {
        board[i] = (int *)malloc(9 * sizeof(int));
    }
    initializeBoard(board);

    int user_move[4];

    printBoard(board);
    int curPlayer = RED; //red, bottom half with negative values
    while (gameOver(board)==0) {
        startTime = CycleTimer::currentSeconds();
        if (aiType == AB){
            mB = calculateStepAB(board, curPlayer);
        }else{
            mB = calculateStepMC(board, curPlayer);
        }
        endTime = CycleTimer::currentSeconds();

        timeUsed = (endTime - startTime)*1000.f;
        cout << "AI (R) decided to move from " << mB->sr << "," << mB->sc;
        cout << " to "<<mB->er << "," << mB->ec <<" with time = " << timeUsed << "ms\n";
        makeMove(board, mB->sr, mB->sc, mB->er, mB->ec);
        free(mB);
        printBoard(board);
        if (gameOver(board) == RED){
            cout << "Red Wins!\n";
            return 1;
        }
        curPlayer = BLACK;
        while (true) {
            cout << "enter your move of 4 numbers, space separated: ";
            // user inputs values space separated in one line.  Inputs more than the count are discarded.
            cin >> user_move[0] >> user_move[1] >> user_move[2] >> user_move[3];
            
            piece = board[user_move[0]][user_move[1]];
            if (piece * curPlayer <= 0){
                cout << "Does not have a piece there \n";
            }else if (isValidMove(board, user_move[0], user_move[1],user_move[2],user_move[3])) {
                makeMove(board, user_move[0], user_move[1],user_move[2],user_move[3]);
                break;
            }
        }
        printBoard(board);
        curPlayer = RED;
    }
    cout << "BLACK Wins!\n";
    
    return 1;
}