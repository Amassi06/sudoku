
#ifndef GRILLE_H
#define GRILLE_H

#define TAILLE_GRILLE 9

// Fonction pour vérifier si une valeur est valide dans une case donnée
bool estValide(int** sudoku, int ligne, int col, int val);

// Fonction pour mélanger une array
void melangeArray(int array[], int size);

// Fonction pour remplir une grille de sudoku valide aléatoirement
void generationGrilleValide(int** sudoku);

// Fonction récursive pour remplir une case de la grille aléatoirement
bool remplirCase(int** sudoku, int ligne, int col);

//Fonction pour vider les case aléatoirement d'un sudoku valide et le sudoku doit avoir une solution unique
void viderCases(int** sudoku, int case_a_vider);

#endif //GRILLE_H
