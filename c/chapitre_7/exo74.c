/*
Ecrire un programme qui saisit les valeurs d’un tableau d’entier tab de n
éléments alloué dynamiquement. L’entier n sera saisi au clavier. Le programme aﬃche la valeur
d’un élément tab[i] où i est saisi au clavier. En cas d’erreur de segmentation le programme
fait resaisir la valeur de i avant de l’aﬃcher.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

sigjmp_buf env ;

void gestionnaire(int sig)
{
    const char msg[] = "\nErreur de segmentation ! Ressaisissez i.\n";
    write(STDERR_FILENO, msg, sizeof(msg) - 1);
    siglongjmp(env, 1);
}

int main() {
    int n, i, *tab;
    struct sigaction sa;

    sa.sa_handler = gestionnaire;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGSEGV, &sa, NULL);

    printf("Taille du tableau : ");
    scanf("%d", &n);

    tab = malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) 
    {
        printf("tab[%d] = ", j);
        scanf("%d", &tab[j]);
    }

    //On vérifie le retour de sigsetjmp
    if (sigsetjmp(env, 1) != 0)
    {
        printf("Indice invalide, réessayez.\n");
    }

    printf("\nEntrez l'indice i à afficher : ");
    if (scanf("%d", &i) != 1)
    {
        free(tab);
        return 1;
    }

    // Vérification manuelle AVANT l'accès
    if (i < 0 || i >= n) {
        printf("Indice %d hors limites [0, %d[\n", i, n);
        free(tab);
        return 1;
    }

    printf("Valeur tab[%d] = %d\n", i, tab[i]);

    free(tab);
    return 0;
}