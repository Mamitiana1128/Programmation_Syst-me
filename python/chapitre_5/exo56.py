"""
réer un programme qui a en variable globale un tableau de N double,
avec N=100.
Dans le main, le tableau sera initialisé avec des valeurs réelles aléatoires entre 0 et 100, sauf
les valeurs tableau[0] et tableau[99] qui vallent 0.
Le programme crée deux threads :
- Le premier thread remplace chaque valeur tableau[i], avec i = 1,2,. . .,98 par la moyenne
(tableau[i-1]+tableau[i]+tableau[i+1])/3
Il attend ensuite un temps alléatoire entre 1 et 3 secondes ;
- Le deuxième thread aﬃche le tableau toutes les 4 secondes.
"""

import threading
import time
import random
import sys

mutex = threading.Lock()

N = 100
tableau = [0.0] * N


def affiche(arg):
    while True:
        with mutex:
            for i in range(N):
                print(f"{tableau[i]:g} ", end='')
                sys.stdout.flush()
            print("\n-----------------------------------------------------------------")

        time.sleep(4)


def changement(arg):
    while True:
        with mutex:
            for i in range(1, N - 1):
                tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3

        temp = random.randint(1, 3)
        time.sleep(temp)


def main():
    random.seed()

    # Initialisation du tableau
    for i in range(N):
        if i == 0 or i == 99:
            continue
        tableau[i] = random.randint(0, 9999) / 100.0

    # Lancement des threads
    threads = [
        threading.Thread(target=changement, args=(None,)),
        threading.Thread(target=affiche,    args=(None,))
    ]

    for t in threads:
        t.start()

    # Attend la fin des deux threads
    for t in threads:
        t.join()

    return 0

main()