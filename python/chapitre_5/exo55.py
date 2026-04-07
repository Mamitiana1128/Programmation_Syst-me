"""
Écrire un programme, avec un compteur global compt, et qui crée deux
threads :
- Le premier thread itère l'opération suivante : on incrémente le compteur et attend un
temps alléatoire entre 1 et 5 secondes.
- Le deuxième thread aﬃche la valeur du compteur toutes les deux secondes.
Les accès au compteur seront bien sûr protégés par un mutex. Les deux threads se terminent
lorsque le compteur atteint une valeur limite passée en argument (en ligne de commande) au
programme.
"""

import threading
import sys
import time
import random

mutex = threading.Lock()

compt = 0


def incremente(rang):
    global compt
    temp = 0

    while compt < rang:
        with mutex:
            compt += 1

        temp = random.randint(1, 5)
        time.sleep(temp)


def affichage(compteur):
    global compt

    while compt < compteur:
        with mutex:
            print(f"Compteur : {compt}")
            sys.stdout.flush()

        time.sleep(2)


def main():
    global compt
    random.seed()

    # verification des arguments
    if len(sys.argv) != 2:
        print(f"Usage : {sys.argv[0]} <limite_compteur>", file=sys.stderr)
        sys.exit(1)

    limite = int(sys.argv[1])

    # Lancement des 2 threads
    threads = [
        threading.Thread(target=incremente, args=(limite,)),
        threading.Thread(target=affichage,  args=(limite,))
    ]

    for t in threads:
        t.start()

    # Attend la fin des deux threads
    for t in threads:
        t.join()

    print(f"Fin du programme. Compteur : {compt}")

    return 0

main()