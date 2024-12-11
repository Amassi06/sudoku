#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include"../include/libsudoku.h"
#include"../include/grille.h"



// Fonction pour vérifier si une valeur est valide dans une case donnée
bool estValide(int ** sudoku, int ligne, int col, int val) {
  // Vérifier la ligne
  for (int i = 0; i < TAILLE_GRILLE; i++)
    if (sudoku_get(sudoku, ligne, i) == val)
      return false;

  // Vérifier la colonne
  for (int i = 0; i < TAILLE_GRILLE; i++)
    if (sudoku_get(sudoku, i, col) == val)
      return false;

  // Vérifier la région 3x3
  int debutLigne = ligne - ligne % 3;
  int debutCol = col - col % 3;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (sudoku_get(sudoku, i + debutLigne, j + debutCol) == val)
        return false;

  return true;
}

// Fonction qui mélange un tableau
void melangeArray(int array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Fonction récursive pour remplir une case de la grille aléatoirement
// Algorithme de retour en arriére utilisé (Backtracking)
bool remplirCase(int ** sudoku, int ligne, int col) {
  int ordre[] = {1,2,3,4,5,6,7,8,9};
  // Si on a atteint la dernière case, la grille est remplie
  if (ligne == TAILLE_GRILLE - 1 && col == TAILLE_GRILLE) 
    return true;

  // Passage à la ligne suivante si on a atteint la fin d'une ligne
  if (col == TAILLE_GRILLE) {
    ligne++;
    col = 0;
  }

  // Essayer de placer un nombre dans la case dans l'ordre aléatoire actuel
  for (int i = 0; i < 9; i++) {
    int num = ordre[i];
    if (estValide(sudoku, ligne, col, num)) {
      sudoku_set(sudoku, ligne, col, num);

      // Mélanger l'ordre aléatoire pour le prochain appel récursif
      melangeArray(ordre,9);

      // Résoudre récursivement pour la case suivante
      if (remplirCase(sudoku, ligne, col + 1))
        return true;

      // Si on n'a pas pu remplir la grille avec ce nombre, remettre la case à zéro
      sudoku_set(sudoku, ligne, col, 0);
    }
  }

  // Si aucun nombre ne peut être placé, retourner faux
  return false;
}

// Fonction pour remplir une grille de sudoku valide aléatoirement
void generationGrilleValide(int ** sudoku) {
  srand(time(NULL));
  // Remplir la grille de manière récursive
  if (!remplirCase(sudoku, 0, 0)) {
    fprintf(stderr,"Impossible de générer une grille de Sudoku valide.\n");
    exit(-1);
  }
}

//Fonction pour vider les case aléatoirement d'un sudoku valide en ayant une solution unique
void viderCases(int ** sudoku, int cases_non_vide) {

  int cases_a_vider = TAILLE_GRILLE * TAILLE_GRILLE - cases_non_vide;
  int cases_a_vider_i = 0;
  // Créer un tableau d'indices mélangés

    int indices[TAILLE_GRILLE * TAILLE_GRILLE]; //9x9 matrice mélange au lieu de travailler avec le rand function c'est mieux comme cela sa evite la repetition
    int indices_i = 0;
    for (int i = 0; i < TAILLE_GRILLE; i++) 
        for (int j = 0; j < TAILLE_GRILLE; j++) 
            indices[indices_i++] = i * TAILLE_GRILLE + j;
            
    melangeArray(indices, TAILLE_GRILLE * TAILLE_GRILLE); // Mélanger les indices

  int index = 0;

  while (cases_a_vider_i < cases_a_vider && index < TAILLE_GRILLE * TAILLE_GRILLE) {  

        int pos = indices[index++];
        int ligne = pos / TAILLE_GRILLE;
        int col = pos % TAILLE_GRILLE;
    // Vérifier si la case n'est pas déjà vide
    if (sudoku_get(sudoku, ligne, col) != 0) {
  
      int valeur = sudoku_get(sudoku, ligne, col);
      int t[8];
      bool solution_unique = true;
        for (int i = 0; i < 8; ++i) // en remplissant par les ature valeur de la case pour voir si la solution est unique
          if(i>=valeur-1)
            t[i]=i+2;
          else
            t[i]=i+1;

          for(int i=0;i<8;++i)
            if(estValide(sudoku, ligne, col, t[i])){
              solution_unique = false;
              break;
            }

      if (solution_unique){
        cases_a_vider_i++;
        sudoku_set(sudoku, ligne, col, 0);     
   }
  }
  }

}



