/*(Problème de l’émetteur et du récepteur) Un thread émetteur
dépose , à intervalle variable entre 1 et 3 secondes, un octet dans une variable globale à
destination d’un processus récepteur. Le récepteur lit cet octet à intervalle variable aussi entre
1 et 3 secondes. Quelle solution proposez-vous pour que l’émetteur ne dépose pas un nouvel
octet alors que le récepteur n’a pas encore lu le précédent et que le récepteur ne lise pas deux
fois le même octet ?
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem_vide , sem_plein ;
char message ;

void *emetteur(void *arg);
void *recepteur(void *arg);

int main()
{
    pthread_t thread_emetteur , thread_recepteur ;
    srand(time(NULL));
    sem_init(&sem_vide , 0 , 1 ) ; // vide au depart
    sem_init(&sem_plein , 0 , 0 ) ; // non plein au depart


    // creation des threads
    pthread_create(&thread_emetteur , NULL , emetteur , NULL ) ;
    pthread_create(&thread_recepteur , NULL , recepteur , NULL ) ;

    // Attend leurs fin 
    pthread_join(thread_emetteur , NULL );
    pthread_join(thread_recepteur , NULL) ;
    

    sem_destroy(&sem_vide);
    sem_destroy(&sem_plein) ;

    return (0) ;
}

void *emetteur(void *arg)
{
    while (1)
    {
        sleep(rand()%3+1); // attend l'interval de temp

        sem_wait(&sem_vide) ; // Attends que le message soit vide 
        message = (char)( rand() % 256 )  ; // rempicage aléatoire du message
        printf("Emetteur envoie : %c\n",message);
        sem_post(&sem_plein) ; // Signale que le message est rempli

    }
    
    pthread_exit(NULL) ;
}

void *recepteur(void *arg)
{

    while (1)
    {
        sleep(rand()%3+1 ) ; // Attente

        sem_wait(&sem_plein) ; // attend que le message soit plein
        printf("Recepteur reçoit : %c \n",message );

        sem_post(&sem_vide) ; // Signale que le message etait lue 
    }

    pthread_exit(NULL) ;
}