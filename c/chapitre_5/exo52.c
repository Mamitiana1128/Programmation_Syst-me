/*
Écrire un programme qui crée un thread qui alloue un tableau d’entiers,
initialise les éléments par des entiers aléatoires entre 0 et 99, et retourne le tableau d’entiers.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAILLE 4

void *ma_fonction_thread(void * arg) ;

int main()
{
    pthread_t mythread ;
    int *tableau = NULL ;
    srand(time(NULL));

    //Lancement du thread 
    pthread_create(&mythread , NULL , ma_fonction_thread , (void*)tableau ) ;
    pthread_join(mythread , (void*)&tableau ) ;

    // test afficahage du tableau 
    for (int i = 0; i < TAILLE ; i++)
    {
        printf("[%d] ",tableau[i] ) ;
    }
    
    return (0);
}

void *ma_fonction_thread(void *arg)
{
    int *tab = (int*)arg ;

    tab = malloc(TAILLE * sizeof(int));

    for (int i = 0 ; i < TAILLE ; i++)
    {
        tab[i] = rand() % 100 ;
    }
    
    pthread_exit((void*)tab) ;
}