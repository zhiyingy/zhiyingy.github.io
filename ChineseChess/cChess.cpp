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

void ChessPiece::setVal(int t, int r, int c, int p) {
    type = t;
    row = r;
    col = c;
    player = p;
}

int ChessPiece::getRow()
{
    return row;
} 

int ChessPiece::getCol()
{
    return col;
}

int ChessPiece::getType() {
    return type;
}

int ChessPiece::getPlayer() {
    return player;
}

void ChessPiece::setPosition(int r, int c)
{
    row = r;
    col = c;
}

bool ChessPiece::isdead() {
    return dead;
} 

void ChessPiece::setDead() {
    dead = true;
}

// int board[10][9] = { 2, 3, 6, 5, 1, 5, 6, 3, 2,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 4, 0, 0, 0, 0, 0, 4, 0,
//                      7, 0, 7, 0, 7, 0, 7, 0, 7,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                     -7, 0,-7, 0,-7, 0,-7, 0,-7,
//                      0,-4, 0, 0, 0, 0, 0,-4, 0,
//                      0, 0, 0, 0, 0, 0, 0, 0, 0,
//                     -2,-3,-6,-5,-1,-5,-6,-3,-2};

ChessPiece chess_pieces[32];
ChessPiece board [10][9];
int move[4];
int curPlayer;
bool gameOver = false;

void printBoard(){
    for (int r = 0; r < 10; r++) {
        for (int j = 0; j < 9; j++) {
            if (board[r][j].getType()*board[r][j].getPlayer() >= 0){
                cout << " ";
            }
            cout << board[r][j].getType()*board[r][j].getPlayer() << " ";
        }
        cout << "\n";
    }
}

void initGame() {
    chess_pieces[0].setVal(SHUAI, 9, 4, RED);
    chess_pieces[1].setVal(SHI, 9, 3, RED);
    chess_pieces[2].setVal(SHI, 9, 5,RED);
    chess_pieces[3].setVal(XIANG, 9, 2,RED);
    chess_pieces[4].setVal(XIANG, 9, 6,RED);
    chess_pieces[5].setVal(MA, 9, 1, RED);
    chess_pieces[6].setVal(MA, 9, 7, RED);
    chess_pieces[7].setVal(JU, 9, 0, RED);
    chess_pieces[8].setVal(JU, 9, 8, RED);
    chess_pieces[9].setVal(PAO, 7, 1, RED);
    chess_pieces[10].setVal(PAO, 7, 7, RED);
    chess_pieces[11].setVal(ZU, 6, 0, RED);
    chess_pieces[12].setVal(ZU, 6, 2, RED);
    chess_pieces[13].setVal(ZU, 6, 4, RED);
    chess_pieces[14].setVal(ZU, 6, 6, RED);
    chess_pieces[15].setVal(ZU, 6, 8, RED);

    chess_pieces[16].setVal(SHUAI, 0, 4, BLACK);
    chess_pieces[17].setVal(SHI, 0, 3, BLACK);
    chess_pieces[18].setVal(SHI, 0, 5,BLACK);
    chess_pieces[19].setVal(XIANG, 0, 2,BLACK);
    chess_pieces[20].setVal(XIANG, 0, 6,BLACK);
    chess_pieces[21].setVal(MA, 0, 1, BLACK);
    chess_pieces[22].setVal(MA, 0, 7, BLACK);
    chess_pieces[23].setVal(JU, 0, 0, BLACK);
    chess_pieces[24].setVal(JU, 0, 8, BLACK);
    chess_pieces[25].setVal(PAO, 2, 1, BLACK);
    chess_pieces[26].setVal(PAO, 2, 7, BLACK);
    chess_pieces[27].setVal(ZU, 3, 0, BLACK);
    chess_pieces[28].setVal(ZU, 3, 2, BLACK);
    chess_pieces[29].setVal(ZU, 3, 4, BLACK);
    chess_pieces[30].setVal(ZU, 3, 6, BLACK);
    chess_pieces[31].setVal(ZU, 3, 8, BLACK);
    for (int i = 0; i < 32; i++) {
        ChessPiece piece = chess_pieces[i];
        board[piece.getRow()][piece.getCol()] = piece;
    }
    printBoard();
}

bool isValidMove(){
    int sr = move[0];
    int sc = move[1];
    int er = move[2];
    int ec = move[3];
    ChessPiece piece = board[sr][sc];
    if (piece.getPlayer() != curPlayer){
        cout << "Does not have a piece there \n";
        return false;
    }
    if (board[er][ec].getPlayer() == curPlayer) {
        cout << "Can not place piece on top of your piece\n";
        return false;
    }
    switch (piece.getType()) {
        case SHUAI: {
            //Shuai
            //checkmate condition
            if (board[er][ec].getType() == 1 && ec == sc) {
                for (int r = 1; r < 9; r++) {
                    if (board[r][ec].getType() != 0){
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
        }case SHI :{
            //SHI
            if (sr == 8 && sc == 4) {
                //in the center position
                if (abs(er-sr)!=1 || abs(sc-ec)!=1){    
                    cout << "Invalid Shi move, can only move diagonally with step size 1\n";
                    return false;
                }
            }
            if ((sr == 7 || sr == 9) && (sc == 3 || sc == 5)) {
                if (ec != 8 || ec != 4) {
                    cout << "Invalid Shi move, can only move 8 4 at this position.\n";
                    return false;
                }
            }
            break;
        }case XIANG * RED: {
            //xiang
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
            if (board[midr][midc].getType() != 0){
                cout << "Xiang cannot move cross occupied points\n";
                return false;
            }
            break;
        }case MA * RED: {
            //MA
            if (abs(ec-sc) + abs(er-sr) != 3 || abs(ec-sc) < 1 || abs(er-sr) < 1) {
                cout << "Ma moves one space vertically or horizontally, followed by one space outward-diagonally.\n";
                return false;
            }
            if (abs(ec-sc) == 1){
                //move vertically first
                int midr = sr < er ? sr + 1 : er + 1;
                if (board[midr][sc].getType() != 0) {
                    return false;
                }
            } else {
                int midc = sc < ec ? sc + 1 : ec + 1;
                if (board[sr][midc].getType() != 0){
                    return false;
                }
            }
            break;
        } case JU * RED: {
            //Ju
            if (er != sr && ec != sc) {
                cout << "Ju can only move vertically or horizontally.\n";
                return false;
            }
            if (er == sr) {
                int minc = sc < ec ? sc : ec;
                int maxc = sc < ec ? ec : sc;
                for (int c = minc+1; c < maxc; c++) {
                    if (board[sr][c].getType() != 0){
                        cout << "Ju cannot move cross pieces.\n";
                        return false;
                    }
                }
            } else {
                int minr = sr < er ? sr : er;
                int maxr = sr < er ? er : sr;
                for (int r = minr +1; r < maxr; r++) {
                    if (board[r][sc].getType() != 0){
                        cout << "Ju cannot move cross pieces.\n";
                        return false;
                    }
                }
            }
            break;
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
                    if (board[sr][c].getType() != 0){
                        count++;
                    }
                }
            } else{
                //move vertically
                int minr = sr < er ? sr : er;
                int maxr = sr < er ? er : sr;
                for (int r = minr +1; r < maxr; r++) {
                    if (board[r][sc].getType() != 0){
                        count++;
                    }
                }
            }
            if (board[er][ec].getType() == 0 && count!=0){
                cout << "Pao cannot move cross pieces if it's not eating one.\n";
                return false;
            } else if (board[er][ec].getType()!=0 && count != 1){
                cout << "Pao cannot eat piece without crossing exactly one other piece.\n";
                return false;
            }
            break;
        } case ZU * RED: {
            //bin
            if (sr > 4){
                //has not pass the river yet
                if (er != sr-1 || abs(ec-sc) != 0){
                    cout << "Invalid bin Move, can only move up before passing the river\n";
                    return false;
                }
            }
            if (abs(ec-sc) + abs(er-sr) != 1 || er > sr) {
                cout << "Invalid bin Move, can only move up, left or right by one\n";
                return false;
            }
            break;
        }
    }
    if (board[er][ec].getType() == SHUAI){
        gameOver = true;
    }
    if (board[er][ec].getType() != 0) {
        //is eaten
        board[er][ec].setDead();
    }
    piece.setPosition(er,ec);
    board[er][ec] = piece;
    board[sr][sc].setVal(sr,sc,0,0);
    printBoard();
    return true;
}

int main() {
    // #ifdef OMP
    //     omp_set_num_threads(OMPNUMTHREADS);
    // #endif
    initGame();
    curPlayer = RED; //red, bottom half with negative values
    while (!gameOver) {
        while (true) {
            cout << "enter your move of 4 numbers, space separated: ";
            // user inputs values space separated in one line.  Inputs more than the count are discarded.
            cin >> move[0] >> move[1] >> move[2] >> move[3];
            if (isValidMove()) {
                break;
            }
        }
        // startTime = CycleTimer::currentSeconds();
        // calculateStep();
        // min = (endTime - startTime) * 1000.f;
        // cout << "AI (B) decided to move with time = " << min << "ms\n";
    }
    
    
    return 1;
}