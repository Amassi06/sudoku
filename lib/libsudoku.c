#include <stdlib.h>
#include <stdio.h>
#include "libsudoku.h"

int **sudoku_init() {
    int **grille = (int **) calloc(9, sizeof(int *));
    for (int i = 0; i < 9; i++)
        grille[i] = calloc(9, sizeof(int));
    return grille;
}

void sudoku_free(int **sudoku) {
    for (int i = 0; i < 9; i++)
        free(sudoku[i]);
    free(sudoku);
}

void sudoku_print(int **sudoku) {
    for (int i = 0; i < 9; i++) {
        printf("\n");
        if (i % 3 == 0)
            printf("\n");

        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0)
                printf("   ");

            printf("%d ", sudoku[i][j]);
        }
    }
}

int sudoku_get(int **sudoku, int x, int y) {
    if (x >= 0 && y >= 0 && x <= 8 && y <= 8)
        return sudoku[x][y];

    fprintf(stderr, "x et y doivent être compris entre 0 et 8\n");
    return -1;
}

void sudoku_set(int **sudoku, int x, int y, int value) {
    if (x >= 0 && y >= 0 && x <= 8 && y <= 8 && value >= 0 && value <= 8)
        sudoku[x][y] = value;
    else
        fprintf(stderr, "x et y et valeur doivent être compris entre 0 et 8\n");
}
