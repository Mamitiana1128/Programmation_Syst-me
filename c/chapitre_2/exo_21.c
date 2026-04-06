#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    __pid_t pidFils ;
    int status ;

    switch (pidFils = fork() )
    {
    case -1 :
            printf("Erreur de lancement du Fork") ;
            exit (-1) ;
        break;
    case 0 :
            printf("Je suis le fils\n") ;
            exit(0);
        break;
    default :
            printf("Je suis le Pére\n") ;
            wait(&status) ;
        break ;
    }
    
    return 0 ;
}