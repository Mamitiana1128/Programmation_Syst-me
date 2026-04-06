/*
Écrire un programme, avec un compteur global compt, et qui crée deux
threads :
• Le premier thread itère l’opération suivante : on incrémente le compteur et attend un
temps alléatoire entre 1 et 5 secondes.
• Le deuxième thread aﬃche la valeur du compteur toutes les deux secondes.
Les accès au compteur seront bien sûr protégés par un mutex. Les deux threads se terminent
lorsque le compteur atteint une valeur limite passée en argument (en ligne de commande) au
programme.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;


int compt = 0 ;

void *incremente(void *arg) ;
void *affichage(void *arg) ;

int main(int argc , char **argv)
{
    srand(time(NULL)) ;
    pthread_t thread[2] ;
    int limite ;

    // verification des arguments
    if (argc != 2 )
    {
        fprintf(stderr , "Ussage : %s <limite_compteur>\n",argv[0] ) ;
        exit(1) ;
    }

    limite = atoi(argv[1]) ;
    // Lancement des 2 threads
    pthread_create(&thread[0] , NULL , incremente , (void*)(intptr_t)limite ) ;
    pthread_create(&thread[1], NULL , affichage , (void *)(intptr_t)limite ) ;

    // Attend la fin des deux threads
    for (int i = 0 ; i < 2 ; i++)
    {
        pthread_join(thread[i] , NULL ) ;
    }
    
    printf("Fin du programme. Compteur : %d\n",compt) ;

    return (0);
}

void *incremente(void *arg)
{
    int rang = (int)(intptr_t)arg ;
    int temp ;

    while (compt < rang )
    {
        pthread_mutex_lock(&mutex) ;
        compt++ ;
        pthread_mutex_unlock(&mutex);

        temp = (rand()%5) + 1 ;
        sleep(temp);
    
    }
    
    pthread_exit(NULL) ;
}

void *affichage(void* arg)
{
    int compteur = (int)(intptr_t)arg ;

    while(compt < compteur )
    {
        pthread_mutex_lock(&mutex);
        printf("Compteur : %d \n",compt) ;
        fflush(stdout);
        pthread_mutex_unlock(&mutex);

        sleep(2) ;
    }

    pthread_exit(NULL) ;
}