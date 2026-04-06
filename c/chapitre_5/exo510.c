/*(Problème des producteurs et des consommateurs) Des proces-
sus producteurs produisent des objets et les insère un par un dans un tampon de n places. Bien
entendu des processus consommateurs retirent, de temps en temps les objets (un par un).
Résolvez le problème pour qu’aucun objet ne soit ni perdu ni consommé plusieurs fois.
Écrire une programme avec N threads producteurs et M threads consomateurs, les nombres N
et M étant saisis au clavier. Les producteurs et les consomateurs attendent un temps aléatoire
entre 1 et 3 secondes entre deux produits. Les produits sont des octets que l’on stocke dans un
tableau de 10 octets avec gestion LIFO. S’il n’y a plus de place, les producteurs restent bloqués
en attendant que des places se libèrent.
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_vide , sem_plein ;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

#define TAILLE 10 

unsigned char tableau[TAILLE] ;
int top = -1 ;

void *producteur(void *arg) ;
void *consommateur(void *arg) ;

int  main()
{
    int n, m;
    srand(time(NULL));

    // Initialisation du semathore
    sem_init(&sem_vide , 0 , TAILLE ) ; 
    sem_init(&sem_plein , 0 , 0 ) ; 

    printf("Nombre de producteurs (N) : ");
    scanf("%d", &n);
    printf("Nombre de consommateurs (M) : ");
    scanf("%d", &m);


    pthread_t prod_threads[n], cons_threads[m];

    // Création des threads producteurs
    for (int i = 0; i < n; i++)
    {
        pthread_create(&prod_threads[i], NULL, producteur, (void*)(__intptr_t)i );
    }

    // Création des threads consommateurs
    for (int i = 0; i < m; i++)
    {
        pthread_create(&cons_threads[i], NULL, consommateur, (void*)(__intptr_t)i );
    }

    // Attente
    for (int i = 0; i < n ; i++) 
    {
        pthread_join(prod_threads[i], NULL);
    }
    for (int i = 0; i < m ; i++)
    {
        pthread_join(cons_threads[i], NULL);
    }

    sem_destroy(&sem_vide) ;
    sem_destroy(&sem_plein) ;

    return (0);
}

void *consommateur(void *arg)
{
    int id = (int)(__intptr_t)arg;

    while(1)
    {
        sleep(rand()%3+1 ) ; // Attente avant reception du produit 
        unsigned char produit ;

        sem_wait(&sem_plein) ;

        pthread_mutex_lock(&mutex) ;
    
            produit = tableau[top] ;
            top--;
            printf("Consommateur[%d] : reçoit produit %c \n", id+1 , produit) ;

        pthread_mutex_unlock(&mutex) ;

        sem_post(&sem_vide) ;

    }

    return NULL ;
}

void *producteur(void *arg)
{
    int id = (int)(__intptr_t)arg ;

    while(1)
    {
        unsigned char produit = (unsigned char)(rand()%26 + 'A' ) ; // Création du produit aléatoire
        sleep(rand()%3+1 ) ; // Attente avant création du produit 

        sem_wait(&sem_vide) ; // Attend si tableau plein 

        pthread_mutex_lock(&mutex) ;

            printf("Producteur[%d] : produit : %c\n",id + 1 , produit ) ;
            top++ ;
            tableau[top] = produit ;

        pthread_mutex_unlock(&mutex);
        
        sem_post(&sem_plein);
    }

    return NULL ;
}