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

typedef struct tree {
    NODE* root;
}TREE;

NODE* createNode(int value, int nbChilds, t_move* moves, t_localisation loc);

TREE* createTree();

void addChild(NODE* parent, NODE* child, int posChild);

NODE* buildTree(int level, int maxLevel, int nbChildren, int val, t_move* moves, t_localisation loc, t_map map);

void printTree(NODE* node, int depth);

#endif //UNTITLED1_TREE_H
