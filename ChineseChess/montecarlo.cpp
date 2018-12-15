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

movesMC *newMcNode(movesMC *parent, move *mv, int **board, int curPlayer) {
    movesMC *node = (movesMC *)malloc(sizeof(movesMC));
    node -> mv = mv;
    node -> n = 0;
    node -> parent = parent;
    node -> wins = 0;
    node -> player = flipPlayer(curPlayer); 
    //the player playing this move

    if (mv != NULL){
        int endPiece = makeMove(board, mv->sr, mv->sc, mv->er, mv->ec);
        node -> possibleMoves = generateAllMoves(board, curPlayer);
        unmakeMove(board, mv->sr, mv->sc, mv->er, mv->ec, endPiece);
    }else{
        node -> possibleMoves = generateAllMoves(board, curPlayer);
    }
    node->nextIndex = 0;
    return node;
}

movesMC *ucbBestChild(movesMC *node) {
    double curVal;
    int v;
    movesMC *chosenChild = NULL;
    double maxValue = -DBL_MAX;
    int n = node->n;
    for (std::vector<movesMC*>::iterator it = (node->children).begin(); 
        it != (node->children).end(); it++) {
        movesMC *child = *it;
        curVal = child->wins*1.0/(child->n) + C*sqrt(log(n)/(child->n));
        if (curVal > maxValue){
            maxValue = curVal;
            chosenChild = child;
        }
    }
    return chosenChild;
}

movesMC *select(int **board, movesMC *root) {
    movesMC *node = root;
    while (gameOver(board) == 0){
        //expandable
        if (node->possibleMoves.size()>node->nextIndex){
            movesMC *child = newMcNode(node, node->possibleMoves[node->nextIndex],board,node->player);
            (node->children).push_back(child);
            if (node->children.size()>5){
                std::cout<<"possibleMoves "<<(node->children[5]->possibleMoves).size()<<"\n";
            }
            return child;
        }
        node->possibleMoves.clear();
        //select best ucb child
        // node = ucbBestChild(node);
        node = node->children.at(5);
        std::cout<<"best finished with "<<(node->possibleMoves).size()<<"\n";

        makeMove(board, node->mv->sr, node->mv->sc, node->mv->er, node->mv->ec);
    }
    return node;
}

void back(movesMC *node, int win_inc){
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

int simulate(int **board, movesMC *leaf, int curPlayer) {
    makeMove(board, leaf->mv->sr, leaf->mv->sc, leaf->mv->er, leaf->mv->ec);
    std::vector<move*> possibleMoves;
    int index, step;
    move *curMove;
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

move *mcts(int **board, int curPlayer, int simulations){
    int **copyBoard;
    int result;
    time_t t;
    srand((unsigned) time(&t));
    movesMC *root = newMcNode(NULL, NULL, board, curPlayer);
    copyBoard = (int **)malloc(10 * sizeof(int *));
    for (int i = 0; i < 10; i++){
        copyBoard[i] = (int *)malloc(9 * sizeof(int));
    }

    for (int i = 0; i < simulations; i++) {
        deepCopyBoard(board,copyBoard);
        movesMC *leaf = select(copyBoard, root);
        int win_inc = simulate(copyBoard, leaf, curPlayer);
        back(leaf, win_inc);
    }

    for (int i = 0; i < 10; i++){
        free(copyBoard[i]);
    }
    free(copyBoard);
    return ucbBestChild(root)->mv;
}

move *calculateStepMC(int **board, int curPlayer){
    return mcts(board, curPlayer, 40);
}