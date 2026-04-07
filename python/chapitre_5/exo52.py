"""
Écrire un programme qui crée un thread qui alloue un tableau d'entiers,
initialise les éléments par des entiers aléatoires entre 0 et 99, et retourne le tableau d'entiers.
"""

import threading
import random
import time

TAILLE = 4

def ma_fonction_thread(arg, result):
    tab = [random.randint(0, 99) for _ in range(TAILLE)]
    result.extend(tab)
    # pthread_exit equivalent : return


def main():
    random.seed()
    tableau = []

    # Lancement du thread
    thread = threading.Thread(target=ma_fonction_thread, args=(None, tableau))
    thread.start()
    thread.join()

    # test affichage du tableau
    for i in range(TAILLE):
        print(f"[{tableau[i]}] ", end='')

    return 0

main()