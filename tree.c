#include "tree.h"

NODE* createNode(int value, int nbChilds, t_move* moves, t_localisation loc) {
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->cost = value;
    node->nbChildren = nbChilds;
    node->avails = moves;
    node->loc = loc;

    node->children = (NODE**)malloc(node->nbChildren * sizeof(NODE*));
    for (int i = 0; i < nbChilds; i++) {
        node->children[i] = NULL;
    }
    return node;
}

TREE* createTree(){
    TREE* tree = (TREE*)malloc(sizeof(TREE));
    tree->root = NULL;
    return tree;
}

void addChild(NODE* parent, NODE* child, int posChild) {
    if (posChild < parent->nbChildren) {
        parent->children[posChild] = child;
    } else {
        printf("Erreur : le nœud a atteint son nombre maximum d'enfants\n");
    }
}

NODE* buildTree(int level, int maxLevel, int nbChildren, int val, t_move* moves, t_localisation loc) {
    if (level > maxLevel) {
        return NULL;
    }

    NODE* node = createNode(val, nbChildren, moves, loc);

    for (int i = 0; i < nbChildren; i++) {
        t_localisation newLoc = move(loc, moves[i]);
        t_move* childAvailablesMoves = excludeMove(moves, nbChildren, moves[i]);
        node->children[i] = buildTree(level + 1, maxLevel, nbChildren - 1, 0, childAvailablesMoves, newLoc);
    }

    return node;
}

void printTree(NODE* node, int depth) {
    if (node == NULL) {
        return;
    }

    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("Node value: %d, Depth: %d, Children: %d, Pos: (%d,%d), Orientation: %d\n", node->cost, depth, node->nbChildren, node->loc.pos.x, node->loc.pos.y, node->loc.ori);

    for (int i = 0; i < node->nbChildren; i++) {
        printTree(node->children[i], depth + 1);
    }
}
