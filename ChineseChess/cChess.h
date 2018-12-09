#ifndef __CCHESS_H__
#define __CCHESS_H__

#include <omp.h>
#include <vector>

#define BOARD_WIDTH 9
#define BOARD_HEIGHT 10
#define RED -1
#define BLACK 1

#define JU 2
#define MA 3
#define XIANG 6
#define SHI 5
#define SHUAI 1
#define PAO 4
#define ZU 7

typedef struct move_t {
  // x cols, y rows
  int sr;
  int sc;
  int er;
  int ec;
} move;

bool isValidMove(int board[10][9],int sr, int sc, int er, int ec);

// class Move
// {
//     private:
//         int sr;
//         int sc;
//         int er;
//         int ec;
//     public:
//         Move(int startR, int startC, int endR, int endC);
//         int getsr();
//         int getsc();
//         int geter();
//         int getec();
// };

// class ChessPiece
// {
//     private:
//         int type;
//         int row;
//         int col;
//         int player;
//         bool dead;
//     public:
//         void setVal(int t, int r, int c, int p);
//         int getRow();
//         int getCol();
//         void setPosition(int r, int c);
//         void generateMoves(std::vector<Move>);
//         bool isdead();
//         void setDead();
//         int getType();
//         int getPlayer();
// };

#endif