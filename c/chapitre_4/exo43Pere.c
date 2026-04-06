/*
Écrire un programme qui crée un tube, crée un processus ﬁls,
puis, dans le ﬁls, lance par execv un autre programme, appelé programme ﬁls. Le programme
père transmets les descripteurs de tubes au programmes ﬁls en argument, et transmet un
message au ﬁls par le tube. Le programme ﬁls aﬃche le message.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc , char **argv)
{
    pid_t pid ;
    int tube[2] ;
    char arg_read[10] , arg_write[10] ;

    // Verification argument
    if (argc != 2 )
    {
        perror("Entrez le nom du programme fils en argument\n");
        exit(1) ;
    }
    
    // Création du pipe
    if (pipe(tube) == -1)
    {
        perror("Erreur pipe\n");
        exit(1) ;
    }
    

    // Fork
    switch (pid=fork())
    {
    case -1 :
        perror("Erreur Fork\n");
        exit(1);
        break;
    case 0:
        
        // Convertion en chaine de caractere du tube
        sprintf(arg_read , "%d" , tube[0]);
        sprintf(arg_write , "%d" , tube[1]);

        char *args[] = { argv[1] , arg_read , arg_write , NULL } ;

        execv(argv[1] , args ) ;
        
        perror("Erreur execv\n") ;
        exit(0) ;
        break;
    default:
        
        close(tube[0]);
        char *message  = "Bonjour je suis ton Père\n" ;
        write(tube[1] , message , strlen(message) + 1 ) ;

        close(tube[1]);

        wait(NULL);
        break;
    }
    return (0) ;

}