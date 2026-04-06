/*
Ecrire un programme qui saisit des noms de répertoires au clavier et copie
le répertoire courant dans tous ces répertoires. Le programme doit se poursuivre jusqu’à ce que
l’utilisateur demande de quitter le programme.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *repertoire ;

    printf("Entrer le repertoire : ");
    scanf("%s",repertoire);

    execl("/usr/bin/cp" , "cp" , "-r" , getenv("PWD") , repertoire , NULL ) ;
    
    return 0 ;
}