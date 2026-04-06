/*
Reprendre les programmes de l’exercice ??. Nous allons faire un programme
qui fait la même chose, mais transmet les données diﬀérement. Dans le programme père, on
liera les ﬂots stdout et stdin à un tube.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUF 256 

int main(int argc , char **argv)
{
    int repPipe[2] , wordPipe[2] ;
    int reponse = 0 , resultat = 0 ;
    char filsMot[BUF] , pereMot[BUF] ;

    pid_t pid ;

    // verification du argument
    if (argc != 2 )
    {
        fprintf(stderr , "Entrez le nom du fichier\n");
        _exit(0);
    }

    // Crée des tubes
    pipe(repPipe) ;
    pipe(wordPipe) ;

    // Lancement du fork
    switch (pid = fork() )
    {
    case -1 :
        perror("Erreur Fork\n");
        _exit(0) ;
        break;
    case 0 :
        close(wordPipe[0]);
        close(repPipe[1]) ;

        printf("Entrez le mot : ");
        scanf("%s" , filsMot ) ;
        // envoie du mot 
        write(wordPipe[1] , filsMot , strlen(filsMot) + 1 ) ;

        // Verification du resultat
        read(repPipe[0] , &reponse , sizeof(int) ) ;
        if (reponse)
        {
            printf("Mot trouvé\n");
        }
        else
        {
            printf("Mot Pas trouvé\n");
        }
        _exit(0) ;
        break;
    default:
        char ligne[500] ;
        
        close(repPipe[0]);
        close(wordPipe[1]) ;

        dup2(wordPipe[0] , STDIN_FILENO ) ;
        dup2(repPipe[1] ,STDOUT_FILENO ) ;

        close(repPipe[1]);
        close(wordPipe[0]);
      
        // Ouverture du fichier
        FILE *fichier = fopen(argv[1] , "r" ) ;
        
        read(STDIN_FILENO , pereMot , BUF ) ;

        while (fscanf(fichier , "%s" ,ligne) != EOF )
        {
            if (strcmp(ligne , pereMot) == 0 )
            {
                resultat = 1 ;
                break;
            }
        }

        fclose(fichier) ;
        
        // Envoie du resultat
        fwrite(&resultat , sizeof(int) , 1 , stdout ) ;
        fflush(stdout) ;

        wait(NULL);
        break;
    }
    return (0);
}