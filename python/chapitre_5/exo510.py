"""
(Problème des producteurs et des consommateurs) Des proces-
sus producteurs produisent des objets et les insère un par un dans un tampon de n places. Bien
entendu des processus consommateurs retirent, de temps en temps les objets (un par un).
Résolvez le problème pour qu'aucun objet ne soit ni perdu ni consommé plusieurs fois.
Écrire une programme avec N threads producteurs et M threads consomateurs, les nombres N
et M étant saisis au clavier. Les producteurs et les consomateurs attendent un temps aléatoire
entre 1 et 3 secondes entre deux produits. Les produits sont des octets que l'on stocke dans un
tableau de 10 octets avec gestion LIFO. S'il n'y a plus de place, les producteurs restent bloqués
en attendant que des places se libèrent.
"""

import threading
import time
import random

sem_vide  = None
sem_plein = None
mutex     = threading.Lock()

TAILLE = 10

tableau = bytearray(TAILLE)
top = -1


def consommateur(arg):
    global top
    id = arg

    while True:
        time.sleep(random.randint(1, 3))  # Attente avant reception du produit

        sem_plein.acquire()

        with mutex:
            produit = tableau[top]
            top -= 1
            print(f"Consommateur[{id + 1}] : reçoit produit {chr(produit)}")

        sem_vide.release()


def producteur(arg):
    global top
    id = arg

    while True:
        produit = random.randint(0, 25) + ord('A')  # Création du produit aléatoire
        time.sleep(random.randint(1, 3))             # Attente avant création du produit

        sem_vide.acquire()  # Attend si tableau plein

        with mutex:
            print(f"Producteur[{id + 1}] : produit : {chr(produit)}")
            top += 1
            tableau[top] = produit

        sem_plein.release()


def main():
    global sem_vide, sem_plein
    random.seed()

    # Initialisation du semaphore
    sem_vide  = threading.Semaphore(TAILLE)
    sem_plein = threading.Semaphore(0)

    n = int(input("Nombre de producteurs (N) : "))
    m = int(input("Nombre de consommateurs (M) : "))

    prod_threads = []
    cons_threads = []

    # Création des threads producteurs
    for i in range(n):
        t = threading.Thread(target=producteur, args=(i,))
        prod_threads.append(t)
        t.start()

    # Création des threads consommateurs
    for i in range(m):
        t = threading.Thread(target=consommateur, args=(i,))
        cons_threads.append(t)
        t.start()

    # Attente
    for t in prod_threads:
        t.join()
    for t in cons_threads:
        t.join()

    return 0

main()