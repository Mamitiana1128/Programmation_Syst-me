/*
crire un programme saisit.c qui saisit un int au clavier, et l’enregistre
dans un ﬁchier /tmp/entier.txt. Écrire un programme affiche.c qui attend (avec sleep) un
signal utilisateur du programme saisit.c. Lorsque l’entier a été saisi, le programme affiche.c
aﬃche la valeur de l’entier.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* Global pour accès dans le handler */
int recu = 0;

void handler(int sig)
{
    recu = 1;
}

int main()
{
    FILE *f;
    int valeur;
    struct sigaction sa ;

    // Confid signal
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);

    printf("Mon PID : %d\n", getpid());
    printf("En attente du signal...\n");

    /* Attente active */
    while (!recu)
    {
        sleep(1);
    }

    f = fopen("/tmp/entier.txt", "r");
    if (f)
    {
        fscanf(f, "%d", &valeur);
        printf("Valeur lue : %d\n", valeur);
        fclose(f);
    }

    return 0;
}