#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER ;

int compteur = 0 ;
double u ;

void *ma_fonction_thread(void *arg) ;

double f1(double x ) ;
double f2(double x ) ;

int main()
{
    int i ;
    pthread_t T[2] ;
    srand(time(NULL));  
    u = 1 ;

    // Lancement des 2 threads
    for ( i = 0 ; i < 2 ; i++)
    {
        pthread_create(&T[i] , NULL , ma_fonction_thread , (void*)(__intptr_t)i ) ;
    }
    
    // Attend la fin des threads
    for(i=0 ; i<2 ; i++)
    {
        pthread_join(T[i] , NULL ) ;
    }

    return (0) ;

}

double f1(double x )
{
    return (0.25*(x-1)*(x-1)) ;
}

double f2(double x)
{
    return ( (1.0/6.0)*(x-2)*(x-2) );
}

void *ma_fonction_thread(void *arg)
{
    int id = (int)(intptr_t)arg ;

    while(1)
    {
        // Verouillage du mutex 
        pthread_mutex_lock(&mutex);

        compteur++ ;

        if (id == 0 )
        {
            u = f1(u) ;
        }
        else
        {
            u = f2(u) ;
        }
        
        printf("Thread[%d]. Valeur u = %g\n" , id + 1 , u ) ;
        fflush(stdout) ;

        // Dévérouillage du mutex
        pthread_mutex_unlock(&mutex) ;


        sleep( rand()%5+ 1 ) ;

    }
}