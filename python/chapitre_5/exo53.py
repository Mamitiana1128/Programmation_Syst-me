"""
Créer une structure TypeTableau qui contient :
- Un tableau d'entiers ;
- Le nombre d'éléments du tableau ;
- Un entier x.
Écrire un programme qui crée un thread qui initialise un TypeTableau avec des valeurs
aléatoires entre 0 et 99. Le nombre d'éléments du tableau est passé en paramètre. Dans le
même temps, le thread principal lit un entiers x au clavier. Lorsque le tableau est ﬁni de
générer, le programme crée un thread qui renvoie 1 si l'élément x est dans le tableau, et 0
sinon.
"""

import threading
import random
import time
import sys

# Structure TypeTableau
class TypeTableau:
    def __init__(self):
        self.tableau = []
        self.taille  = 0
        self.x       = 0


def verification(arg, result):
    tab = arg

    # Verification si x existe
    for i in range(tab.taille):
        if tab.tableau[i] == tab.x:
            result[0] = 1
            return
    result[0] = 0


def rempliçage(taille, result):
    tab = TypeTableau()
    tab.taille  = taille
    tab.tableau = [random.randint(0, 99) for _ in range(taille)]
    result[0] = tab


def main():
    random.seed()
    taille = int(sys.argv[1])

    tab_result = [None]
    rep_result = [0]

    # lancement du premier thread
    thread0 = threading.Thread(target=rempliçage, args=(taille, tab_result))
    thread0.start()

    # Recupération du entier x
    x = int(input("Entrez l'entier x : "))

    # Attend la fin du premier thread
    thread0.join()
    tab = tab_result[0]
    tab.x = x

    # Creation du 2eme thread
    thread1 = threading.Thread(target=verification, args=(tab, rep_result))
    thread1.start()

    # Attend la fin du 2eme thread
    thread1.join()

    if rep_result[0]:
        print("Chiffre trouvé")
    else:
        print("Chiffre non trouvé")

    return 0

main()