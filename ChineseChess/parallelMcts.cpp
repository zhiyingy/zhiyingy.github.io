#include "montecarlo.h"
#include "cChess.h"
#include "evaluate.h"
#include "generateMove.h"
#include <math.h>
#include <iostream>
#include <stack> 
#include <chrono>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <omp.h>

void makeCopyBoard(int **board, int** result){
    for (int i = 0; i<10; i++){
        for (int j = 0; j<9; j++){
            result[i][j]=board[i][j];
        }
    }
}

MovesMC *newMcNode(MovesMC *parent, Move *mv, int **board, int curPlayer) {
    int endPiece;
    if (mv != NULL){
        endPiece = makeMove(board, mv->sr, mv->sc, mv->er, mv->ec);
    }
    MovesMC *node = new MovesMC(parent,mv,flipPlayer(curPlayer),generateAllMoves(board,curPlayer));
    if (mv != NULL){
        unmakeMove(board, mv->sr, mv->sc, mv->er, mv->ec, endPiece);
    }
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

void back(MovesMC *node, int win_inc, int sim_inc){
    bool win = false;
    node -> n += sim_inc;
    node -> wins += win_inc;
    while (node->parent != NULL) {
        node = node->parent;
        node -> n += sim_inc;
        if (win){
            node->wins += win_inc;
        }
        win = !win;
    }
}
void clearPossibleMoves(std::vector<Move*> possibleMoves){
    while(!possibleMoves.empty()) {
        delete possibleMoves.back();
        possibleMoves.pop_back();
    }
    possibleMoves.clear();
}

int simulate(int **board, MovesMC *leaf, int curPlayer) {
    std::vector<Move*> possibleMoves;
    int index, step;
    Move *curMove;
    makeMove(board, leaf->mv->sr, leaf->mv->sc, leaf->mv->er, leaf->mv->ec);
    leaf->n++;
    int nextPlayer = flipPlayer(leaf->player);
    for (step = 0; step < MAXSTEP; step++){
        if (gameOver(board)!=0){
            break;
        }
        possibleMoves = generateAllMoves(board, nextPlayer);
        index = rand() % possibleMoves.size();
        curMove = possibleMoves.at(index);
        makeMove(board, curMove->sr, curMove->sc, curMove->er, curMove->ec);
        clearPossibleMoves(possibleMoves);
        nextPlayer = flipPlayer(nextPlayer);
    }
    if (evaluate(board, curPlayer)>0){
        return 1;
    }
    return 0;
}

void makeMoves(int **board, MovesMC *leaf){
    if (leaf->mv == NULL){
        return;
    }
    makeMoves(board, leaf->parent);
    makeMove(board, leaf->mv->sr, leaf->mv->sc, leaf->mv->er, leaf->mv->ec);
}

MovesMC *select(int **board, MovesMC *root) {
    MovesMC *node = root;
    while (gameOver(board) == 0){
        //expandable
        if ((int)node->possibleMoves.size()>node->nextIndex){
            return node;
        }
        node->possibleMoves.clear();
        //select best ucb child
        node = ucbBestChild(node,C);
        makeMove(board, node->mv->sr, node->mv->sc, node->mv->er, node->mv->ec);
    }
    return node;
}

Move *mcts(int **board, int curPlayer, int sim){
    int **copyBoard;
    int result, i;
    time_t t;
    srand((unsigned) time(&t));
    MovesMC *root = newMcNode(NULL, NULL, board, curPlayer);
    using namespace std::chrono;
    typedef std::chrono::high_resolution_clock Clock;
    typedef std::chrono::duration<double> dsec;
    double st = 0.0;
    double bt = 0.0;

    copyBoard = (int **)malloc(10 * sizeof(int *));
    for (i = 0; i < 10; i++){
        copyBoard[i] = (int*)malloc(9 * sizeof(int));
    }

    for (i=0 ; i<sim; i++){
        makeCopyBoard(board, copyBoard);
        MovesMC *leaf = select(copyBoard, root);
        //do expansion here
        for (std::vector<Move*>::iterator it = (leaf->possibleMoves).begin(); it != (leaf->possibleMoves).end(); it++){
            MovesMC *child = newMcNode(leaf, *it, copyBoard, leaf->player);
            leaf->children.push_back(child);
            leaf->nextIndex=leaf->possibleMoves.size();
        }
        int wins;
        //do parallel simulation
        auto cst = Clock::now();
        #pragma omp parallel for default(shared) private(i) schedule(dynamic)
        for (i = 0; i < (int)leaf->children.size(); i++) {
            int **localCopy = makeCopy(board);
            MovesMC *child = leaf->children[i];
            int win = simulate(localCopy, child, curPlayer);
            freeBoard(localCopy);
        #pragma omp critical
            {
            wins += win;
            }
        }
        st += duration_cast<dsec>(Clock::now() - cst).count();

        //back propagation
        auto t = Clock::now();
        back(leaf, wins, leaf->children.size());
        bt += duration_cast<dsec>(Clock::now() - t).count();
    }
    std::cout<< "simulation time is "<<st << "\n";
    std::cout<< "back time is" << bt <<"\n";
    
    return ucbBestChild(root,0.0)->mv;
}

Move *calculateStepMC(int **board, int curPlayer){
    Move *mv= mcts(board, curPlayer, 10000);
    return mv;
}