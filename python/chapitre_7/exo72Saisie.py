"""
Ecrire un programme saisit.c qui saisit un int au clavier, et l'enregistre
dans un ﬁchier /tmp/entier.txt. Écrire un programme affiche.c qui attend (avec sleep) un
signal utilisateur du programme saisit.c. Lorsque l'entier a été saisi, le programme affiche.c
aﬃche la valeur de l'entier.
"""

import os
import sys
import signal

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <PID_affiche>", file=sys.stderr)
        sys.exit(1)

    pid_dest = int(sys.argv[1])

    n = int(input("Entrez un entier : "))

    try:
        with open("/tmp/entier.txt", "w") as f:
            f.write(str(n))
    except Exception:
        print("fopen", file=sys.stderr)
        sys.exit(1)

    # Envoi du signal au programme affiche
    os.kill(pid_dest, signal.SIGUSR1)

    return 0

main()