#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "moves.h"
#include "tree.h"

int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);

    #define nbMovesReg 3
    #define nbMovesTradi 4

    //Tirage mouvements

    srand(time(NULL));
    t_move movesPull[NB_TIRAGES];
    drawMoves(movesPull);

    t_localisation MarcLoc = loc_init(4, 6, NORTH);

    int startingCaseCost = map.costs[MarcLoc.pos.y][MarcLoc.pos.x];

    NODE* root = buildTree(0, 3, 4, startingCaseCost, movesPull, MarcLoc, map);
    printTree(root, 0);

    return 0;
}
