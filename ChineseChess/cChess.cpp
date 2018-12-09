#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <omp.h>
#include <cstring>
#include <iostream>
#include "lib/CycleTimer.h"
#include "alphabeta.h"
using namespace std;

#include "cChess.h"
#include "alphabeta.h"

// void ChessPiece::setVal(int t, int r, int c, int p) {
//     type = t;
//     row = r;
//     col = c;
//     player = p;
// }

// int ChessPiece::getRow()
// {
//     return row;
// } 

// int ChessPiece::getCol()
// {
//     return col;
// }

// int ChessPiece::getType() {
//     return type;
// }

// int ChessPiece::getPlayer() {
//     return player;
// }

// void ChessPiece::setPosition(int r, int c)
// {
//     row = r;
//     col = c;
// }

// bool ChessPiece::isdead() {
//     return dead;
// } 

// void ChessPiece::setDead() {
//     dead = true;
// }

// int Move::getsr() {
//     return sr;
// }

// int Move::getsc() {
//     return sr;
// }

// int Move::geter() {
//     return er;
// }

// int Move::getec() {
//     return ec;
// }

// Move::Move(int startR, int startC, int endR, int endC) {
//     sr = startR;
//     sc = startC;
//     er = endR;
//     ec = endC;
// }

int curPlayer;
bool gameOver = false;

void printBoard(int board[10][9]){
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

bool isValidMove(int board[10][9],int sr, int sc, int er, int ec){
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
        cout << "Cannot eat your own side\n";
    }

    switch (piece) {
        case SHUAI * RED: {
            //Shuai
            //checkmate condition
            if (board[er][ec] == SHUAI * BLACK){
                if (ec != sc) {
                    cout << "Two Jiang must be at the same col\n";
                    return false;
                }
                for (int r = er+1; r < sr; r++) {
                    if (board[r][ec] != 0){
                        cout << "Cannot checkmate with pieces in between\n";
                        return false;
                    }
                }
            } else if (ec < 3 || ec >5 || er < 7) {
                cout << "Can not move Shuai outside the bound\n";
                return false;
            } else if (abs(ec-sc) + abs(er-sr) != 1) {
                cout << "Invalid Shuai Move, can only move up, down, left, right by one\n";
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
                        cout << "Cannot checkmate with pieces in between\n";
                        return false;
                    }
                }
            } else if (ec < 3 || ec >5 || er > 2) {
                cout << "Can not move Shuai outside the bound\n";
                return false;
            } else if (abs(ec-sc) + abs(er-sr) != 1) {
                cout << "Invalid Shuai Move, can only move up, down, left, right by one\n";
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
            if (er >2 || ec > 5 || ec < 3) {
                return false;
            }
            if (abs(sr - er) != 1 || abs(ec-sc) != 1){
                return false;
            }
        }case XIANG * RED: {
            //XIANG
            if (er < 5){
                cout << "Xiang cannot pass the bound\n";
                return false;
            }
            if (abs(ec-sc) != 2 || abs(er-sr) != 2){
                cout << "Xiang can move exactly two spaces diagonally\n";
                return false;
            }
            int midr = sr < er ? sr + 1 : er + 1;
            int midc = sc < ec ? sc + 1 : ec + 1;
            if (board[midr][midc] != 0){
                cout << "Xiang cannot move cross occupied points\n";
                return false;
            }
            break;
        }case XIANG * BLACK: {
            if (er > 4) {
                return false;
            }
            if (abs(ec-sc) != 2 || abs(er-sr) != 2){
                cout << "Xiang can move exactly two spaces diagonally\n";
                return false;
            }
            int midr = sr < er ? sr + 1 : er + 1;
            int midc = sc < ec ? sc + 1 : ec + 1;
            if (board[midr][midc] != 0){
                cout << "Xiang cannot move cross occupied points\n";
                return false;
            }
            break;
        }case MA * BLACK:{

        }case MA * RED: {
            //MA
            if (abs(ec-sc) + abs(er-sr) != 3 || abs(ec-sc) < 1 || abs(er-sr) < 1) {
                cout << "Ma moves one space vertically or horizontally, followed by one space outward-diagonally.\n";
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
                cout << "Ju can only move vertically or horizontally.\n";
                return false;
            }
            if (er == sr) {
                int minc = sc < ec ? sc : ec;
                int maxc = sc < ec ? ec : sc;
                for (int c = minc+1; c < maxc; c++) {
                    if (board[sr][c] != 0){
                        cout << "Ju cannot move cross pieces.\n";
                        return false;
                    }
                }
            } else {
                int minr = sr < er ? sr : er;
                int maxr = sr < er ? er : sr;
                for (int r = minr +1; r < maxr; r++) {
                    if (board[r][sc] != 0){
                        cout << "Ju cannot move cross pieces.\n";
                        return false;
                    }
                }
            }
            break;
        } case PAO * BLACK : {

        } case PAO * RED: {
            //Pao
            if (er != sr && ec != sc) {
                cout << "Pao can only move vertically or horizontally.\n";
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
                cout << "Pao cannot move cross pieces if it's not eating one.\n";
                return false;
            } else if (board[er][ec]!=0 && count != 1){
                cout << "Pao cannot eat piece without crossing exactly one other piece.\n";
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

void makeMove (int board[10][9], int sr, int sc, int er, int ec){
    if (board[er][ec] == SHUAI){
        gameOver = true;
    }

    board[er][ec] = board[sr][sc];
    board[sr][sc] = 0;
    
    printBoard(board);
}

int main() {
    // #ifdef OMP
    //     omp_set_num_threads(OMPNUMTHREADS);
    // #endif
    double startTime, endTime, timeUsed;
    int piece;
    int board[10][9] = { 2, 3, 6, 5, 1, 5, 6, 3, 2,
                         0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 4, 0, 0, 0, 0, 0, 4, 0,
                         7, 0, 7, 0, 7, 0, 7, 0, 7,
                         0, 0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0,
                        -7, 0,-7, 0,-7, 0,-7, 0,-7,
                         0,-4, 0, 0, 0, 0, 0,-4, 0,
                         0, 0, 0, 0, 0, 0, 0, 0, 0,
                        -2,-3,-6,-5,-1,-5,-6,-3,-2};

    int user_move[4];

    printBoard(board);
    curPlayer = RED; //red, bottom half with negative values
    while (!gameOver) {
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
        
        startTime = CycleTimer::currentSeconds();
        move mB = calculateStep(board, MAX, BLACK);
        timeUsed = (endTime - startTime) * 1000.f;
        cout << "AI (B) decided to move from " << mB.sr << "," << mB.sc;
        cout << " to "<<mB.er << "," << mB.ec << " with time = " << timeUsed << "ms\n";
    }
    
    
    return 1;
}