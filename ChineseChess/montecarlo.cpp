#include "montecarlo.h"
#include "cChess.h"
#include "evaluate.h"
#include "generateMove.h"
#include <math.h>
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
    node -> possibleMoves = generateAllMoves(board, curPlayer);
    node -> nextIndex = 0;
    node -> score = 0.0;
    node -> mv = mv;
    node -> parent = parent;
    return node;
}

movesMC *ucbBestChild(movesMC *node, double c) {
    float curVal;
    int v;
    int chosenIndex = 0;
    double maxValue = -DBL_MAX;;
    for (int i = 0; i < node->children.size(); i++) {
        movesMC *child = node->children.at(i);
        curVal = (children->score/children->nextIndex);
        curVal += c*sqrt(2*log(node->nextIndex/child->nextIndex));
        if (curVal > maxValue){
            maxValue = curVal;
            chosenIndex = i;
        }
    }
    return node->children.at(chosenIndex);
}

movesMC *search(int **board, movesMC *root, int curPlayer) {
    movesMC *node = root;
    makeMove(board, node->mv->sr, node->mv->sc, node->mv->er, node->mv->ec);
    while (gameOver(board) == 0){
        if (node->nextIndex != node->possibleMoves.size()){
            movesMC *child = newMcNode(root, 
                node->possibleMoves.at(node->nextIndex),board,curPlayer);
            node->nextIndex++;
            return child;
        }
        node = ucbBestChild(node, 1.4);
        makeMove(board, node->mv->sr, node->mv->sc, node->mv->er, node->mv->ec);
    }
    return node;
}

void back(movesMC *node, int result){
    float sum_score = node->score;
    while (!node->parent == NULL) {
        node->score += sum_score;
        node = node->parent;
    }
    node->score += sum_score;
}

move *mcts(int **board, int curPlayer, int simulations){
    std::vector<move*> possibleMoves;
    std::vector<movesMC*> movesList;
    int **copyBoard;
    movesMC *root = newMcNode(NULL, NULL, board, curPlayer);

    copyBoard = (int **)malloc(10 * sizeof(int *));
    for (int i = 0; i < 10; i++){
        copyBoard[i] = (int *)malloc(9 * sizeof(int));
    }

    for (int i = 0; i < simulations; i++) {
        deepCopyBoard(board, copyBoard);
        movesMC *leaf = search(copyBoard, root, curPlayer);
        int result = evaluate(board, curPlayer);
        back(leaf, result);
    }

    for (int i = 0; i < 10; i++){
        free(copyBoard[i]);
    }
    free(copyBoard);
    return ucbBestChild(root, 0.0)->mv;
}

move *calculateStepMC(int **board, int curPlayer){
    // std::vector<movesMC*> movesList;
    return NULL;
}