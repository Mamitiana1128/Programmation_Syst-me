/*
Ecrire un programme qui saisit des nom de ﬁchiers texte au clavier et
ouvre tous ces ﬁchiers dans l’éditeur emacs. Le programme doit se poursuivre jusqu’à ce que
l’utilisateur demande de quitter.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    char **fichiers ;
    int i = 0 ;
    char rep ;
    __pid_t pidFils ;

    while (1)
    {
        printf("Entrer le fichier : ") ;
        scanf("%s" , fichiers[i]) ;
        i++ ;
        while(getchar() != '\n');
        printf("Voulez vous continuez à ajouter(o/n)");
        rep = getchar() ;
        if ( rep != 'o')
        {
            break ;           
        }
    }
    
    for (int j = 0 ; j < i ; j++)
    {
        switch (pidFils = fork() )
        {
        case -1 :
            perror("Erreur Fork\n");
            exit(-1);
            break;
        case 0 :
            execl("/usr/bin/vim" , "vim" , fichiers[j] , NULL );
            exit(-1) ;
            break;
        default:
            break;
        }
    }
    
    wait(NULL) ;
    printf("Processus términer\n") ;
    
    return 0 ;
}