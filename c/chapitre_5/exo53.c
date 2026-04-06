/*
Créer une structure TypeTableau qui contient :
• Un tableau d’entiers ;
• Le nombre d’éléments du tableau ;
• Un entier x.
Écrire un programme qui crée un thread qui initialise un TypeTableau avec des valeurs
aléatoires entre 0 et 99. Le nombre d’éléments du tableau est passé en paramètre. Dans le
même temps, le thread principal lit un entiers x au clavier. Lorsque le tableau est ﬁni de
générer, le programme crée un thread qui renvoie 1 si l’élément x est dans le tableau, et 0
sinon.
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

// Structure TypeTableau
typedef struct 
{
    int *tableau ;
    int taille ;
    int x ;
}TypeTableau;

void *rempliçage(void *arg);
void *verification(void *arg);

int main(int argc , char **argv)
{
    pthread_t thread[2] ;
    int rep = 0  , x ;
    TypeTableau *tab = NULL ;
    int taille = atoi(argv[1]) ;
    srand(time(NULL)) ;

    // lancemenr du premier thread
    pthread_create(&thread[0] , NULL , rempliçage , (void*)(intptr_t)taille ) ;
    
    // Recupération du entier x 

    printf("Entrez l'entier x : ") ;
    scanf("%d",&x) ;

    // Attend la fin du premier thread
    pthread_join(thread[0] , (void*)&tab ) ;
    tab->x = x ;
 
    // Creation du 2eme thread
    pthread_create(&thread[1], NULL , verification , (void*)tab) ;
 
    // Attend la fin du 2eme thread
    pthread_join(thread[1] , (void *) &rep ) ;

    if ( rep )
    {
        printf("Chiffre touvé\n");
    }
    else
    {
        printf("Chiffre non trouvé\n") ;
    }    

    free(tab) ;
    return (0) ;
}

void *verification(void *arg)
{
    TypeTableau *tab = (TypeTableau *)arg ;

    // Verification si x existe
    for (int i = 0 ; i < tab->taille  ; i++)
    {
        if ( tab->tableau[i] == tab->x)
        {
            pthread_exit((void*)1) ;
        }
    }

    pthread_exit((void*)0) ;
}


void *rempliçage(void *arg)
{
    TypeTableau *tab  = malloc(sizeof(TypeTableau));
    int t = (int)(intptr_t)arg ;
    tab->taille = t ;

    tab->tableau = malloc(t*sizeof(int ) ) ;

    // Remplicage tu tableau avec rand()
    for (int i = 0 ; i < t ; i++)
    {
        tab->tableau[i] = rand()%100 ;
    }
    
    pthread_exit((void*)tab) ;
}