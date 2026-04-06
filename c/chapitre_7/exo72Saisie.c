/*
Ecrire un programme saisit.c qui saisit un int au clavier, et l’enregistre
dans un ﬁchier /tmp/entier.txt. Écrire un programme affiche.c qui attend (avec sleep) un
signal utilisateur du programme saisit.c. Lorsque l’entier a été saisi, le programme affiche.c
aﬃche la valeur de l’entier.
*/

#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char **argv)
{
    FILE *f;
    int n;
    pid_t pid_dest;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <PID_affiche>\n", argv[0]);
        exit(1);
    }

    pid_dest = atoi(argv[1]);

    printf("Entrez un entier : ");
    scanf("%d", &n);

    f = fopen("/tmp/entier.txt", "w");
    
    if (f == NULL) 
    {
        perror("fopen");
        exit(1);
    }
    
    fprintf(f, "%d", n);
    fclose(f);

    // Envoi du signal au programme affiche
    kill(pid_dest, SIGUSR1);

    return 0;
}