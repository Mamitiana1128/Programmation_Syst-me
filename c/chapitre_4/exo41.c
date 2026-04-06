/*
Écrire un programme qui crée deux processus. Le processus père
ouvre un ﬁchier texte en lecture. On suppose que le ﬁchier est composé de mots formés de
caractères alphabétiques séparés par des espaces. Le processus ﬁls saisit un mot au clavier. Le
processus père recherche le mot dans le ﬁchier, et transmet au ﬁls la valeur 1 si le mot est dans
le ﬁchier, et 0 sinon. Le ﬁls aﬃche le résultat.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define BUFF 256

int main(int argc , char **argv)
{
    int resultat , trouver = 0 ;
    int tubeMot[2];
    int tubeRep[2] ;
    char tabFils[BUFF] , tabPere[BUFF] ;
    FILE *fichier ;

    // Création des 2 pipe
    pipe(tubeMot);
    pipe(tubeRep);

    if (argc != 2 )
    {
        printf("Faut preciser le nom du fichier\n");
        exit(-1);
    }
    

    __pid_t pid = fork();
    
    if( pid == -1 )
    {
        perror("Erreur Fork\n");
        exit(-1);
    }
    else if (pid == 0 )
    {
        close(tubeMot[0]);
        close(tubeRep[1]);

        printf("Entrez le mot : ");
        scanf("%s",tabFils) ;

        // Envoie du message au Père
        write(tubeMot[1] , tabFils , BUFF ) ;

        // Verification du resultat venant du père
        read(tubeRep[0] , &resultat , sizeof(int)) ;
        if (resultat)
        {
            printf("Mot trouvé\n");
        }
        else
        {
            printf("Mot pas encore touvé\n") ;
        }
        
        exit(0);
    }
    else
    {
        fichier = fopen(argv[1] , "r" ) ;
        char ligne[500] ;
        close(tubeMot[1]);
        close(tubeRep[0]) ;

    // Reception du message venant du fils
        read(tubeMot[0] , tabPere , BUFF ) ;
    // recherche le mot dans le fichier et return 1 au fils si trouvé et 0 si non
        while ( fscanf(fichier , "%s" , ligne ) != EOF )
        {
            if (strcmp(ligne , tabPere ) == 0 )
            {
                trouver = 1 ;
                break;
            }
        }

        fclose(fichier) ;

        // Envoie du reponse au fils
        write(tubeRep[1] , &trouver , sizeof(int) ) ;

        wait(NULL);
    }

    
    return (0) ;
}