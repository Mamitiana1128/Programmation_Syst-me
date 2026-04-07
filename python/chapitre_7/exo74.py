"""
Ecrire un programme qui saisit les valeurs d'un tableau d'entier tab de n
éléments alloué dynamiquement. L'entier n sera saisi au clavier. Le programme aﬃche la valeur
d'un élément tab[i] où i est saisi au clavier. En cas d'erreur de segmentation le programme
fait resaisir la valeur de i avant de l'aﬃcher.
"""

import os
import sys
import signal

reessayer = False

def gestionnaire(sig, frame):
    global reessayer
    msg = "\nErreur de segmentation ! Ressaisissez i.\n"
    os.write(sys.stderr.fileno(), msg.encode())
    reessayer = True

def main():
    global reessayer

    signal.signal(signal.SIGSEGV, gestionnaire)

    n = int(input("Taille du tableau : "))

    tab = [0] * n
    for j in range(n):
        tab[j] = int(input(f"tab[{j}] = "))

    # On vérifie le retour de sigsetjmp
    # (En Python, on utilise une boucle avec vérification des bornes)
    while True:
        if reessayer:
            print("Indice invalide, réessayez.")
            reessayer = False

        line = input("\nEntrez l'indice i à afficher : ")
        if not line:
            break
        i = int(line)

        # Vérification manuelle AVANT l'accès
        if i < 0 or i >= n:
            print(f"Indice {i} hors limites [0, {n}[")
            break

        print(f"Valeur tab[{i}] = {tab[i]}")
        break

    return 0

main()