#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

// Structure pour le tableau
typedef struct
{
    int *tableau ;
    int taille ; 
}TypeTableau;


void *ma_foncttion_thread(void *arg ) ;

int main(int argc , char **argv)
{
    TypeTableau tab ;
    int t[] = {2,2,3,4,5,9} ;
    tab.tableau = t ;
    tab.taille = 6 ;

    pthread_t thread ;

    pthread_create(&thread , NULL , ma_foncttion_thread , (void*)&tab ) ;
    pthread_join(thread , NULL) ;

    return (0);
}

void *ma_foncttion_thread( void *arg)
{
    TypeTableau *tab = (TypeTableau*)arg ;

    for (int i = 0 ; i < tab->taille ; i++)
    {
        printf("%d" , tab->tableau[i]);
    }
    
    pthread_exit(NULL) ;

}