"""
Ecrire un programme qui crée un ﬁls qui fait un calcul sans ﬁn. Le processus
père propose alors un menu :
- Lorsque l'utilisateur appuie sur la touche 's', le processus père endort son ﬁls.
- Lorsque l'utilisateur appuie sur la touche 'r', le processus père redémare son ﬁls.
- Lorsque l'utilisateur appuie sur la touche 'q', le processus près tue son ﬁls avant de se
terminer.
"""

import os
import sys
import signal

def main():
    try:
        pid_fils = os.fork()
    except OSError:
        print("fork", file=sys.stderr)
        sys.exit(1)

    if pid_fils == 0:
        # calcul infini
        i = 0
        while True:
            i += 1
    else:
        # menu de contrôle
        print(f"Contrôle du fils (PID {pid_fils})")

        continuer = True
        while continuer:
            choix = input("\n's': Stop | 'r': Resume | 'q': Quit\nChoix : ")

            if choix == 's':
                os.kill(pid_fils, signal.SIGSTOP)
            elif choix == 'r':
                os.kill(pid_fils, signal.SIGCONT)
            elif choix == 'q':
                os.kill(pid_fils, signal.SIGKILL)
                continuer = False
            else:
                print("Invalide")

    return 0

main()