#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include"../include/libsudoku.h"
#include"../include/grille.h"


#define TAILLE_THREADS 8

bool solution_trouvee = false;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


typedef struct {

  int ** sudoku;
  int indice;
  int ligne;
  int col;

}arg_t;


void* essaiResoudreAvecThread(void* arg);
void viderCasesThreads(int**,int);

int main(int argc, char * argv[]) {

  if (argc < 2 || atoi(argv[1]) < 40 || atoi(argv[1]) > 50) {
    printf("Veuillez donner nombre de cases non vides N compris entre 40 et 50: \n");
    exit(-1);
  }

  printf("\n\nBienvenue dans notre programme de Sudoku !\n");
  printf("==========================================\n");
  printf("Sudoku généré aléatoirement valide\n");
  printf("==========================================\n");

  int ** sudoku = sudoku_init();
  generationGrilleValide(sudoku); // genere un sudoku valide aléatoirement
  sudoku_print(sudoku);

  printf("\n\n==========================================\n");
  printf("Sudoku avec %s cases non vides SANS threads\n", argv[1]);
  printf("==========================================\n");

  viderCases(sudoku, atoi(argv[1])); //atoi() retourne un entier depuis une chaine de char
  sudoku_print(sudoku);
  //  ---------------------------------------------------------------------------------
  printf("\n\n==========================================\n");
  printf("Sudoku avec %s cases non vides AVEC %d threads\n", argv[1],TAILLE_THREADS);
  printf("==========================================\n");

  viderCasesThreads(sudoku, atoi(argv[1])); 
  sudoku_print(sudoku);
  
  // Désallocation du mutex avant la fin du programme
  pthread_mutex_destroy(&mutex);
  sudoku_free(sudoku);

  return 0;
}

void* essaiResoudreAvecThread(void* arg) {

  pthread_mutex_lock( &mutex);
  bool solution = solution_trouvee;
  pthread_mutex_unlock( &mutex);

  if (solution)
    pthread_exit(NULL);

  arg_t* threads_arg = (arg_t *) arg;

  int indice = threads_arg->indice;
  int ** sudoku = threads_arg->sudoku;
  int ligne = threads_arg->ligne;
  int col = threads_arg->col;

  if (estValide(sudoku, ligne, col, indice)) {
    pthread_mutex_lock( & mutex);
    solution_trouvee = true;
    pthread_mutex_unlock( & mutex);
  }
  pthread_exit(NULL);

}

//Fonction pour vider les case aléatoirement d'un sudoku valide et qu'il sois unique en utilisant des threads
void viderCasesThreads(int ** sudoku, int cases_non_vide) {

  int cases_a_vider = TAILLE_GRILLE * TAILLE_GRILLE - cases_non_vide;
  int cases_a_vides_i = 0;
  // Créer un tableau d'indices mélangés

  int indices[TAILLE_GRILLE * TAILLE_GRILLE]; //matrice 9x9 mélangé
  int indices_i = 0;
  for (int i = 0; i < TAILLE_GRILLE; i++)
    for (int j = 0; j < TAILLE_GRILLE; j++)
      indices[indices_i++] = i * TAILLE_GRILLE + j;

  melangeArray(indices, TAILLE_GRILLE * TAILLE_GRILLE); // Mélanger les indices

  int index = 0;

  while (cases_a_vides_i < cases_a_vider && index < TAILLE_GRILLE * TAILLE_GRILLE) {

    int pos = indices[index++];
    int ligne = pos / TAILLE_GRILLE;
    int col = pos % TAILLE_GRILLE;
    // Vérifier si la case n'est pas déjà vide
    if (sudoku_get(sudoku, ligne, col) != 0) {

      int valeur = sudoku_get(sudoku, ligne, col);
      int t[TAILLE_THREADS];

      for (int i = 0; i < TAILLE_THREADS; ++i)//  remplaçant cette case par tous les autres chffres
        if (i >= valeur - 1)
          t[i] = i + 2;
        else
          t[i] = i + 1;
      	
      	pthread_t threads[TAILLE_THREADS];
	      arg_t threads_arg[TAILLE_THREADS];

      for (int i = 0; i < TAILLE_THREADS; ++i) {
        threads_arg[i].indice = t[i];
        threads_arg[i].sudoku = sudoku;
        threads_arg[i].ligne = ligne;
        threads_arg[i].col = col;

        int result = pthread_create( &threads[i], NULL, essaiResoudreAvecThread, (void*) &threads_arg[i]);
        if (result != 0) {
          fprintf(stderr, "Erreur lors de la création du thread %d\n", i);
          exit(EXIT_FAILURE);
        }
      }
      
     for (int i = 0; i < TAILLE_THREADS; ++i)
    	   if(pthread_join(threads[i], NULL) != 0){
            fprintf(stderr, "Erreur lors de l'attente du thread %d\n", i);
            exit(EXIT_FAILURE);}

      if (!solution_trouvee) {
        cases_a_vides_i++;
        sudoku_set(sudoku, ligne, col, 0);
        solution_trouvee = false;
      }

    }
  }

}
