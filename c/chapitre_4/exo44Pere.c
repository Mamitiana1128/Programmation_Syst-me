/*
ême question qu’à l’exercice ?? mais en passant les descripteurs de tube
comme variables d’environnement.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc , char **argv)
{
    pid_t pid ;
    int tube[2] ;
    char varEnvName[100] ;
    char _read[10] , _write[10] ;

    if (argc != 2)
    {
        fprintf(stderr , "Usage : %s <Chemin_Program>\n", argv[0] ) ;
        exit(1);
    }
    
    // Creation du pipe
    if ( pipe(tube) == -1 )
    {
        perror("Erreur pipe\n");
        exit(1);
    }

    // Creation du varible d'environement
    sprintf( varEnvName , "DESCRIPTEUR=%d:%d" , tube[0] , tube[1] ) ;
    putenv(varEnvName);

    // Lancement du fork
    switch (pid=fork() )
    {
    case -1 :
        perror("Erreur Fork\n");
        exit(0);
        break;
    case 0 :
        char *args[] = {argv[1] , "DESCRIPTEUR" , NULL } ;
        execv(argv[1] , args ) ;

        perror("Erreur execv\n");
        exit(1) ;

        break;
    default:

        // Envoie du message du Père
        close(tube[0]);
        char *message = "Salut je suis ton Père !!\n" ;

        write(tube[1] , message , strlen(message)+1 ) ;

        close(tube[1]);

        wait(NULL) ;
        break;
    }
    return (0) ;

}