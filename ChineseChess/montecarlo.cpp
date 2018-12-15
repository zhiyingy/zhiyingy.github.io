#include "montecarlo.h"
#include "cChess.h"
#include "evaluate.h"
#include "generateMove.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void deepCopyBoard (int **board, int **result) {
    int i, j;
    for (i=0; i < 10; i++) {
        for (j=0; j<9; j++){
            result[i][j] = board[i][j];
        }
    }
}

MovesMC *newMcNode(MovesMC *parent, Move *mv, int **board, int curPlayer) {
    int endPiece;
    if (mv != NULL){
        endPiece = makeMove(board, mv->sr, mv->sc, mv->er, mv->ec);
    }
    MovesMC *node = new MovesMC(parent,mv,flipPlayer(curPlayer),generateAllMoves(board,curPlayer));
    return node;
}

MovesMC *ucbBestChild(MovesMC *node, double c) {
    double curVal;
    int v;
    MovesMC *chosenChild = NULL;
    double maxValue = -1.0;
    int n = node->n;
    int index = 0;
    int chosenIndex = 0;
    for (std::vector<MovesMC*>::iterator it = (node->children).begin(); 
        it != (node->children).end(); it++) {
        MovesMC *child = *it;
        curVal = child->wins*1.0/(child->n) + c*sqrt(log(n)/(child->n));
        if (curVal > maxValue){
            maxValue = curVal;
            chosenChild = child;
            chosenIndex = index;
        }
        index++;
    }
    return chosenChild;
}

MovesMC *select(int **board, MovesMC *root) {
    MovesMC *node = root;
    while (gameOver(board) == 0){
        //expandable
        if (node->possibleMoves.size()>node->nextIndex){
            MovesMC *child = newMcNode(node, node->possibleMoves[node->nextIndex],board,node->player);
            (node->children).push_back(child);
            node->nextIndex++;
            return child;
        }
        node->possibleMoves.clear();
        //select best ucb child
        node = ucbBestChild(node,C);
        makeMove(board, node->mv->sr, node->mv->sc, node->mv->er, node->mv->ec);
    }
    return node;
}

void back(MovesMC *node, int win_inc){
    bool win = false;
    node -> n++;
    node -> wins += win_inc;
    while (node->parent != NULL) {
        node = node->parent;
        node -> n++;
        if (win){
            node->wins += win_inc;
        }
        win = !win;
    }
}

int simulate(int **board, MovesMC *leaf, int curPlayer) {
    std::vector<Move*> possibleMoves;
    int index, step;
    Move *curMove;
    int nextPlayer = flipPlayer(leaf->player);
    for (step = 0; step < MAXSTEP; step++){
        if (gameOver(board)!=0){
            break;
        }
        possibleMoves = generateAllMoves(board, nextPlayer);
        index = rand() % possibleMoves.size();
        curMove = possibleMoves.at(index);
        makeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec);
        possibleMoves.clear();
        nextPlayer = flipPlayer(nextPlayer);
    }
    if (evaluate(board, curPlayer)>0){
        return 1;
    }
    return 0;
}

Move *mcts(int **board, int curPlayer, int simulations){
    int **copyBoard;
    int result;
    time_t t;
    srand((unsigned) time(&t));
    MovesMC *root = newMcNode(NULL, NULL, board, curPlayer);
    copyBoard = (int **)malloc(10 * sizeof(int *));
    for (int i = 0; i < 10; i++){
        copyBoard[i] = (int *)malloc(9 * sizeof(int));
    }

    for (int i = 0; i < simulations; i++) {
        deepCopyBoard(board,copyBoard);
        MovesMC *leaf = select(copyBoard, root);
        int win_inc = simulate(copyBoard, leaf, curPlayer);
        back(leaf, win_inc);
    }

    for (int i = 0; i < 10; i++){
        free(copyBoard[i]);
    }
    free(copyBoard);
    return ucbBestChild(root,0.0)->mv;
}

Move *calculateStepMC(int **board, int curPlayer){
    return mcts(board, curPlayer, 400);
}