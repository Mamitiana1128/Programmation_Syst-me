/*
Ecrire un programme qui crée un ﬁls qui fait un calcul sans ﬁn. Le processus
père propose alors un menu :
• Lorsque l’utilisateur appuie sur la touche 's', le processus père endort son ﬁls.
• Lorsque l’utilisateur appuie sur la touche 'r', le processus père redémare son ﬁls.
• Lorsque l’utilisateur appuie sur la touche 'q', le processus près tue son ﬁls avant de se
terminer.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main()
{
    pid_t pid_fils;
    char choix;
    int continuer = 1;
    unsigned long i = 0;

    pid_fils = fork();

    if (pid_fils < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid_fils == 0)
    {
        // calcul infini
        while (1) {
            i++; 
        }
    } 
    else
    {
        // menu de contrôle 
        printf("Contrôle du fils (PID %d)\n", pid_fils);
        
        while (continuer) {
            printf("\n's': Stop | 'r': Resume | 'q': Quit\nChoix : ");
            scanf(" %c", &choix);

            switch (choix) {
                case 's':
                    kill(pid_fils, SIGSTOP);
                    break;
                case 'r':
                    kill(pid_fils, SIGCONT);
                    break;
                case 'q':
                    kill(pid_fils, SIGKILL);
                    continuer = 0;
                    break;
                default:
                    printf("Invalide\n");
            }
        }
    }

    return 0;
}