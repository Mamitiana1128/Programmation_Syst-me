/*
Les sémaphores permettent de réaliser simplement des rendez-vous Deux threads T1 et T2
itèrent un traitement 10 fois. On souhaite qu’à chaque itération le thread T1 attende à la ﬁn de
son traitement qui dure 2 secondes le thread T2 réalisant un traitement d’une durée aléatoire
entre 4 et 9 secondes. Écrire le programme principal qui crée les deux threads, ainsi que les
fonctions de threads en organisant le rendez-vous avec des sémaphores.
b) Dans cette version N threads doivent se donner rendez-vous, N étant passé en argument au
programme. Les threads ont tous une durée aléatoire entre 1 et 5 secondes.
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <semaphore.h>
#include <unistd.h>

int itertion = 10 ;
int compteur = 0 ; 
int N_THEARD ;
sem_t semaphore ;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

void *fonction_mutex(void *arg) ;

int main(int argc , char **argv)
{
    // Verification des arguments 
    if (argc != 2 )
    {
        fprintf(stderr , "Usage : %s <compteur>\n", argv[0] ) ;
        exit(1);
    }

    srand(time(NULL)) ;
    N_THEARD = atoi(argv[1]) ;  
    int i ;
    pthread_t *T = malloc(N_THEARD*sizeof(pthread_t)) ;
    sem_init(&semaphore , 0 , 0 ) ;

    
    // Lancement du thread
    for ( i = 0; i < N_THEARD ; i++)
    {
        pthread_create(&T[i] , NULL , fonction_mutex , (void*)(__intptr_t)i ) ;
    }
    
    // Attends la fin de chaque thread
    for ( i = 0 ; i < N_THEARD ; i++)
    {
        pthread_join(T[i], NULL ) ;
    }

    sem_destroy(&semaphore) ;
    
    return (0) ;
}

void *fonction_mutex(void *arg)
{
    int id = (int)(intptr_t)(arg) ;
    int i , time  ;

    for ( i = 0 ; i < itertion ; i++)
    {
        time = rand()%5+1 ;

        printf("T[%d] : Traivaille en cours %d s\n", id + 1 , time ) ;
        sleep(time) ;

        printf("T[%d] arrive au RDV\n",id + 1 ) ;

        // verouillage du mutex pour que qu'auccun thread ne touche le compteur
        pthread_mutex_lock(&mutex) ;
            compteur ++ ;
            // Verification si tout le monde est la 
            if (compteur == N_THEARD )
            {
                printf("Dernier thread arrivé ! Libération\n");
                for(int j = 0 ; j < N_THEARD - 1 ; ++j )
                {
                    sem_post(&semaphore) ; // Libère tout les threads
                }
                compteur = 0 ;
                pthread_mutex_unlock(&mutex) ;
            }
            else
            {
                pthread_mutex_unlock(&mutex) ;
                sem_wait(&semaphore); // Attend du dernier thread 
            }

            printf("Ok : tout le monde au itération : %d\n", i+1 ) ;
    }

    pthread_exit(NULL) ;
}