/*(Problème des lecteurs et des rédacteurs) Ce problème modélise
les accès à une base de données. On peut accepter que plusieurs processus lisent la base en même
temps mais si un processus est en train de la modiﬁer, aucun processus, pas même un lecteur,
ne doit être autorisé à y accéder. Comment programmer les lecteurs et les rédacteurs ? Proposer
une solution avec famine des écrivains : les écrivains attendent qu’il n’y ait aucun lecteur. Écrire
une programme avec N threads lecteurs et M threads rédacteurs, les nombres N et M étant
saisis au clavier. La base de donnée est représentée par un tableau de 15 octets initialisés à 0.
À chaque lecture/écriture, le lecteur/écrivain lit/modiﬁe l’octet à un emplacement aléatoire.
Entre deux lectures, les lecteurs attendent un temps aléatoire entre 1 et 3 secondes. Entre deux
écritures, les écrivains attendent un temps aléatoire entre 1 et 10 secondes.
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

#define TAILLE 15

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

int dataBase[TAILLE] = {0} ;
int nb_lecteur = 0 ;

sem_t sem_dataBase ;

void *fn_redacteur(void *arg) ;
void *fn_lecteur(void *arg)  ;

int main()
{
    int n, m;
    srand(time(NULL));

    // Initialisation du semathore
    sem_init(&sem_dataBase , 0 , 1 ) ; 

    printf("Nombre de leteurs (N) : ");
    scanf("%d", &n);
    printf("Nombre de rédacteurs (M) : ");
    scanf("%d", &m);

    pthread_t red_thread[n], lect_thread[m];

    // Création des threads redacteurs
    for (int i = 0; i < n; i++)
    {
        pthread_create(&lect_thread[i], NULL, fn_lecteur, (void*)(__intptr_t)i );
    }

    // Création des threads lecteurs
    for (int i = 0; i < m; i++)
    {
        pthread_create(&red_thread[i], NULL, fn_redacteur , (void*)(__intptr_t)i );
    }

    // Attente
    for (int i = 0; i < n ; i++) 
    {
        pthread_join(red_thread[i], NULL);
    }
    for (int i = 0; i < m ; i++)
    {
        pthread_join(lect_thread[i], NULL);
    }

    sem_destroy(&sem_dataBase) ;


    return (0) ;
}

void *fn_redacteur(void *arg)
{
    int id = (int)(__intptr_t)arg ;
    int nombre , indice ;

    while (1)
    {
        sleep(rand()%10+1 ) ; // attente

        // Demande d'accés 
        sem_wait(&sem_dataBase) ;

            nombre = rand() % 10 ;
            indice = rand()%TAILLE ;
            dataBase[indice] = nombre ;
            printf("Redacteur[%d] crée : tab[%d] = %d \n", id+1 , indice ,nombre ) ;

        // Autorise les autres ;
        sem_post(&sem_dataBase) ;

    }

    return NULL ;
}

void *fn_lecteur(void *arg)
{
    int id = (int)(intptr_t)arg ;
    int indice ;

    while (1)
    {
        sleep(rand()%3+1 ) ; // Attente 

        pthread_mutex_lock(&mutex) ;
            nb_lecteur++ ;

            if (nb_lecteur == 1)
            {
                sem_wait(&sem_dataBase) ; // Bloque les ecrivaints 
            }
        pthread_mutex_unlock(&mutex) ;

        indice = rand()%TAILLE ;
        printf("Lecteur[%d] Lit : tab[%d] = %d \n", id+1 , indice , dataBase[indice] ) ;
      
        pthread_mutex_lock(&mutex) ;
            nb_lecteur-- ;

            if (nb_lecteur == 0 )
            {
                sem_post(&sem_dataBase) ; // Autorise les ecrivains
            }
        pthread_mutex_unlock(&mutex) ;

    }
    
    return NULL ;
}