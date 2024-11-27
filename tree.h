#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H

#include "loc.h"
#include "moves.h"
#include "loc.h"
#include "map.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct s_node {
    int cost;
    struct s_node** children;
    int nbChildren;
    t_move* avails;
    t_localisation loc;
} NODE;

typedef struct {
    int cost;              // Coût total du chemin
    t_localisation loc;    // Position finale du robot
    t_move* moves;         // Liste des mouvements effectués
    int movesCount;        // Nombre de mouvements effectués
} Result;

typedef struct tree {
    NODE* root;
}TREE;

NODE* createNode(int value, int nbChilds, t_move* moves, t_localisation loc);

TREE* createTree();

void addChild(NODE* parent, NODE* child, int posChild);

NODE* buildTree(int level, int maxLevel, int nbChildren, int val, t_move* moves, t_localisation loc, t_map map);

void printTree(NODE* node, int depth);

void findOptimalPathRecursive(NODE* node, int currentCost, t_move* path, int depth, Result* bestResult, t_move currentMove);

Result* createResult();

Result* getOptimalPath(NODE* root);

void printResult(Result* result);

#endif //UNTITLED1_TREE_H
