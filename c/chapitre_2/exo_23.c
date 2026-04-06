#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    __pid_t pidFils ;
    int i ;
    
    for (i = 0 ; i < 5 ; i++)
    {
        switch ( pidFils = fork() )
        {
        case -1 :
            perror("Erreur Fork\n") ;
            exit(-1);
            break;
        case 0 : // On est dans le fils faut quitter le boucle
            printf("Je suis le Fils %d\n" , i+1 );
            exit(1);            
            break;
        default :
            if (i == 0)
            printf("Je suis le Père \n");            
            break;
        }
    }
    return 0 ;
}