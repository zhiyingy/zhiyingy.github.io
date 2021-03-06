#ifndef __CCHESS_H__
#define __CCHESS_H__

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

#define MCST 0
#define AB 1

class Move{
	public:
		int sr;
		int sc;
		int er;
		int ec;
		Move(int sR, int sC, int eR, int eC) {
			sr = sR;
			sc = sC;
			er = eR;
			ec = eC;
		}
};

bool isValidMove(int **board,int sr, int sc, int er, int ec);
int makeMove (int **board, int sr, int sc, int er, int ec);
void unmakeMove (int **board, int sr, int sc, int er, int ec, int piece);
int gameOver(int **board);
int flipPlayer(int curPlayer);
int **makeCopy(int **board);
void freeBoard(int **board);

#endif