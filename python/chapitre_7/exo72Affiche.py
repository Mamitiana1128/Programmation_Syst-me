"""
crire un programme saisit.c qui saisit un int au clavier, et l'enregistre
dans un ﬁchier /tmp/entier.txt. Écrire un programme affiche.c qui attend (avec sleep) un
signal utilisateur du programme saisit.c. Lorsque l'entier a été saisi, le programme affiche.c
aﬃche la valeur de l'entier.
"""

import os
import sys
import signal
import time

# Global pour accès dans le handler
recu = 0

def handler(sig, frame):
    global recu
    recu = 1

def main():
    global recu

    # Config signal
    signal.signal(signal.SIGUSR1, handler)

    print(f"Mon PID : {os.getpid()}")
    print("En attente du signal...")

    # Attente active
    while not recu:
        time.sleep(1)

    try:
        with open("/tmp/entier.txt", "r") as f:
            valeur = int(f.read())
            print(f"Valeur lue : {valeur}")
    except Exception:
        pass

    return 0

main()