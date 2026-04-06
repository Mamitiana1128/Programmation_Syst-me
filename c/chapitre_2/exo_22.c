#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    __pid_t pidFils ;
    
    for(int i = 0 ; i < 2 ; ++i)
    {
        switch (pidFils = fork() )
        {
        case -1 :
            perror("Erreur Fork\n");
            exit(-1);
            break;
        
        case 0 : 
            printf("Je suis le fils %d\n", i + 1  );
            exit(1) ;
            break; 
        default :
            if( i == 0 )
            printf("Je suis le Père\n");
            break;
        }
    }
    return 0 ;
}