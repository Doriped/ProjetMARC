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

NODE* buildTree(int level, int maxLevel, int nbChildren, int val, t_move* moves, t_localisation loc, t_map map) {
    if (level > maxLevel) {
        return NULL;
    }

    NODE* node = createNode(val, nbChildren, moves, loc);

    for (int i = 0; i < nbChildren; i++) {
        t_localisation newLoc = move(loc, moves[i]);
        t_move* childAvailablesMoves = excludeMove(moves, nbChildren, moves[i]);

        int newCost;
        if (isValidLocalisation(newLoc.pos, map.x_max, map.y_max)){
            newCost = map.costs[newLoc.pos.y][newLoc.pos.x];
        }
        else {
            newCost = 10000;
        }
        node->children[i] = buildTree(level + 1, maxLevel, nbChildren - 1, newCost, childAvailablesMoves, newLoc, map);
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

void findOptimalPathRecursive(
        NODE* node,
        int currentCost,
        t_move* path,
        int depth,
        Result* bestResult,
        t_move currentMove
) {
    // Vérification du nœud
    if (!node) return;

    // Mise à jour du coût courant
    currentCost += node->cost;

    // Ajouter le mouvement courant au chemin actuel
    path[depth] = currentMove;

    // Si le nœud est une feuille
    if (node->nbChildren == 0) {
        if (currentCost < 1000 && currentCost < bestResult->cost) {
            // Mise à jour des résultats
            bestResult->cost = currentCost;
            bestResult->movesCount = depth + 1;

            // Réallocation du tableau de mouvements dans le meilleur résultat
            free(bestResult->moves);
            bestResult->moves = malloc(sizeof(t_move) * (depth + 1));
            if (!bestResult->moves) {
                perror("Failed to allocate memory for bestResult->moves");
                exit(EXIT_FAILURE);
            }

            // Copier le chemin actuel dans le meilleur résultat
            for (int i = 0; i <= depth; i++) {
                bestResult->moves[i] = path[i];
            }
        }
        return;
    }

    // Parcourir les enfants du nœud courant
    for (int i = 0; i < node->nbChildren; i++) {
        findOptimalPathRecursive(
                node->children[i],
                currentCost,
                path,
                depth + 1,
                bestResult,
                node->avails[i]
        );
    }
}

Result* createResult() {
    // Allouer de la mémoire pour un nouvel objet Result
    Result* newResult = malloc(sizeof(Result));

    // Initialiser les champs de la structure
    newResult->cost = 1000;       // Coût maximum par défaut
    newResult->moves = NULL;         // Pas de mouvements au départ
    newResult->movesCount = 0;       // Nombre de mouvements initialisé à 0

    return newResult;
}

Result* getOptimalPath(NODE* root) {
    if (!root) return NULL;

    Result* bestResult = createResult();
    t_move* path = malloc(sizeof(t_move) * 100);

    findOptimalPathRecursive(root, 0, path, 0, bestResult, F_10);  // Exemple de mouvement initial
    free(path);
    return bestResult;
}

void printResult(Result* result) {
    if (!result || result->movesCount == 0) {
        printf("No valid path found.\n");
        return;
    }
    printf("Optimal path cost: %d\n", result->cost);
    printf("Moves: ");
    for (size_t i = 0; i < result->movesCount; i++) {
        printf("%d ", result->moves[i]);
    }
    printf("\n");
}

