/*
Ecrire un programme qui saisit un nom de ﬁchier texte au clavier et ouvre ce
ﬁchier dans l’éditeur emacs, dont le ﬁchier exécutable se trouve à l’emplacement /usr/bin/emacs.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *fichier ;

    printf("Entrez le fichier à éditer : ");
    scanf("%s",fichier) ;

    execl("/usr/bin/emacs" , "emacs" , fichier , NULL ) ;

    return 0 ;
}