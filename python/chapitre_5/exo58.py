"""
Les sémaphores permettent de réaliser simplement des rendez-vous Deux threads T1 et T2
itèrent un traitement 10 fois. On souhaite qu'à chaque itération le thread T1 attende à la ﬁn de
son traitement qui dure 2 secondes le thread T2 réalisant un traitement d'une durée aléatoire
entre 4 et 9 secondes. Écrire le programme principal qui crée les deux threads, ainsi que les
fonctions de threads en organisant le rendez-vous avec des sémaphores.
b) Dans cette version N threads doivent se donner rendez-vous, N étant passé en argument au
programme. Les threads ont tous une durée aléatoire entre 1 et 5 secondes.
"""

import threading
import time
import random
import sys

itertion  = 10
compteur  = 0
N_THEARD  = 0
semaphore = threading.Semaphore(0)
mutex     = threading.Lock()


def fonction_mutex(arg):
    global compteur, N_THEARD
    id = arg

    for i in range(itertion):
        t = random.randint(1, 5)

        print(f"T[{id + 1}] : Travaille en cours {t} s")
        time.sleep(t)

        print(f"T[{id + 1}] arrive au RDV")

        # verouillage du mutex pour que qu'aucun thread ne touche le compteur
        mutex.acquire()
        compteur += 1
        # Verification si tout le monde est la
        if compteur == N_THEARD:
            print("Dernier thread arrivé ! Libération")
            for j in range(N_THEARD - 1):
                semaphore.release()  # Libère tous les threads
            compteur = 0
            mutex.release()
        else:
            mutex.release()
            semaphore.acquire()  # Attend du dernier thread

        print(f"Ok : tout le monde au itération : {i + 1}")


def main():
    global N_THEARD

    # Verification des arguments
    if len(sys.argv) != 2:
        print(f"Usage : {sys.argv[0]} <compteur>", file=sys.stderr)
        sys.exit(1)

    random.seed()
    N_THEARD = int(sys.argv[1])

    threads = []
    # Lancement du thread
    for i in range(N_THEARD):
        t = threading.Thread(target=fonction_mutex, args=(i,))
        threads.append(t)
        t.start()

    # Attends la fin de chaque thread
    for t in threads:
        t.join()

    return 0

main()