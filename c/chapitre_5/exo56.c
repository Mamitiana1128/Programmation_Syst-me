/*
réer un programme qui a en variable globale un tableau de N double,
avec N=100.
Dans le main, le tableau sera initialisé avec des valeurs réelles aléatoires entre 0 et 100, sauf
les valeurs tableau[0] et tableau[99] qui vallent 0.
Le programme crée deux threads :
• Le premier thread remplace chaque valeur tableau[i], avec i = 1,2,. . .,98 par la moyenne
(tableau[i-1]+tableau[i]+tableau[i+1])/3
Il attend ensuite un temps alléatoire entre 1 et 3 secondes ;
• Le deuxième thread aﬃche le tableau toutes les 4 secondes.
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

#define N 100
double tableau[N] = {0} ;

void *changement(void * arg) ;
void *affiche(void *arg) ;

int main()
{
    srand(time(NULL));
    pthread_t thread[2] ;

    int i = 0 ;

    // Initialisation du tableau
    for ( i = 0 ; i < N ; i++)
    {
        if (i== 0 || i == 99 )
        {
            continue ;
        }
        tableau[i] = (double)(rand()%10000) / 100.0 ;
    }
    
    // Lancement des threads
    pthread_create(&thread[0] , NULL , changement , (void*)NULL ) ;
    pthread_create(&thread[1] , NULL , affiche , (void *) NULL ) ;

    // Attend la fin des deux threads
    for(i = 0 ; i < 2 ; ++i)
    {
        pthread_join(thread[i] , NULL ) ;
    }

    return (0);
}

void *affiche(void *arg)
{
    int i ;

    while(1)
    {
        pthread_mutex_lock(&mutex) ;

        for ( i = 0 ; i < N ; i++)
        {
            printf("%g ",tableau[i] ) ;
            fflush(stdout) ;
        }
        printf("\n-----------------------------------------------------------------\n");

        pthread_mutex_unlock(&mutex) ;
        
        sleep(4) ;
    }
}

void *changement(void *arg)
{
    int temp  , i ;

    while(1)
    {
        pthread_mutex_lock(&mutex);
        for( i = 1 ; i < N-1  ; ++i)
        {
            tableau[i] = (tableau[i-1] + tableau[i] + tableau[i +1]) / 3 ;
        }
        pthread_mutex_unlock(&mutex);
        
        temp = (rand()%3)+1 ;
        sleep(temp);
    }
}