
#ifndef LIBSUDOKU_H
#define LIBSUDOKU_H
/* Création d'une grille de sudoku */
int **sudoku_init();

/* Libération de la mémoire allouée pour la grille */
void sudoku_free(int **sudoku);

/* Affichage de la grille */
void sudoku_print(int **sudoku);

/* Récupération de la valeur d'une case (si la case est vide, renvoit 0) et renovoi -1 si ya un probleme */
int sudoku_get(int **sudoku, int x, int y);

/* Modification de la valeur d'une case */
void sudoku_set(int **sudoku, int x, int y, int value);
#endif //LIBSUDOKU_H
