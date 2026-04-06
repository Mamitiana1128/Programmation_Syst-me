#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int status ;

void filsAttendre()
{
    srand(time(NULL)) ;
    int nbsec = (rand() % 10 ) + 1 ; // Attend entre 1 à 10
    sleep(nbsec); 

    exit(nbsec) ;
}

int main()
{
    __pid_t pidFils ;
    int total = 0 ;

    switch ( pidFils = fork() )
    {
    case -1 :
        perror("Erreur Fork\n");
        exit(-1);
        break;
    case 0 :
        filsAttendre() ;
        break;
    default :
            wait(&status) ;
            total += WEXITSTATUS(status) ;
        break;
    }

    if (pidFils != 0 ) // on est dans le Père
    {
        printf("Pére : durée total : %d sécondes \n", total );
    }

    return 0 ;
}