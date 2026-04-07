"""
(Problème des lecteurs et des rédacteurs) Ce problème modélise
les accès à une base de données. On peut accepter que plusieurs processus lisent la base en même
temps mais si un processus est en train de la modiﬁer, aucun processus, pas même un lecteur,
ne doit être autorisé à y accéder. Comment programmer les lecteurs et les rédacteurs ? Proposer
une solution avec famine des écrivains : les écrivains attendent qu'il n'y ait aucun lecteur. Écrire
une programme avec N threads lecteurs et M threads rédacteurs, les nombres N et M étant
saisis au clavier. La base de donnée est représentée par un tableau de 15 octets initialisés à 0.
À chaque lecture/écriture, le lecteur/écrivain lit/modiﬁe l'octet à un emplacement aléatoire.
Entre deux lectures, les lecteurs attendent un temps aléatoire entre 1 et 3 secondes. Entre deux
écritures, les écrivains attendent un temps aléatoire entre 1 et 10 secondes.
"""

import threading
import time
import random

TAILLE = 15

mutex        = threading.Lock()
dataBase     = [0] * TAILLE
nb_lecteur   = 0
sem_dataBase = threading.Semaphore(1)


def fn_redacteur(arg):
    id = arg

    while True:
        time.sleep(random.randint(1, 10))  # attente

        # Demande d'accés
        sem_dataBase.acquire()

        nombre = random.randint(0, 9)
        indice = random.randint(0, TAILLE - 1)
        dataBase[indice] = nombre
        print(f"Redacteur[{id + 1}] crée : tab[{indice}] = {nombre}")

        # Autorise les autres
        sem_dataBase.release()


def fn_lecteur(arg):
    global nb_lecteur
    id = arg

    while True:
        time.sleep(random.randint(1, 3))  # Attente

        with mutex:
            nb_lecteur += 1
            if nb_lecteur == 1:
                sem_dataBase.acquire()  # Bloque les ecrivains

        indice = random.randint(0, TAILLE - 1)
        print(f"Lecteur[{id + 1}] Lit : tab[{indice}] = {dataBase[indice]}")

        with mutex:
            nb_lecteur -= 1
            if nb_lecteur == 0:
                sem_dataBase.release()  # Autorise les ecrivains


def main():
    random.seed()

    # Initialisation du semaphore
    # (sem_dataBase déjà initialisé globalement à 1)

    n = int(input("Nombre de lecteurs (N) : "))
    m = int(input("Nombre de rédacteurs (M) : "))

    lect_thread = []
    red_thread  = []

    # Création des threads lecteurs
    for i in range(n):
        t = threading.Thread(target=fn_lecteur, args=(i,))
        lect_thread.append(t)
        t.start()

    # Création des threads rédacteurs
    for i in range(m):
        t = threading.Thread(target=fn_redacteur, args=(i,))
        red_thread.append(t)
        t.start()

    # Attente
    for t in lect_thread:
        t.join()
    for t in red_thread:
        t.join()

    return 0

main()