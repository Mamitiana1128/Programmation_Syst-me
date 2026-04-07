"""
(Problème de l'émetteur et du récepteur) Un thread émetteur
dépose , à intervalle variable entre 1 et 3 secondes, un octet dans une variable globale à
destination d'un processus récepteur. Le récepteur lit cet octet à intervalle variable aussi entre
1 et 3 secondes. Quelle solution proposez-vous pour que l'émetteur ne dépose pas un nouvel
octet alors que le récepteur n'a pas encore lu le précédent et que le récepteur ne lise pas deux
fois le même octet ?
"""

import threading
import time
import random

sem_vide  = threading.Semaphore(1)  # vide au depart
sem_plein = threading.Semaphore(0)  # non plein au depart
message   = None


def emetteur(arg):
    global message
    while True:
        time.sleep(random.randint(1, 3))  # attend l'interval de temp

        sem_vide.acquire()  # Attends que le message soit vide
        message = random.randint(0, 255)  # rempicage aléatoire du message
        print(f"Emetteur envoie : {chr(message)}")
        sem_plein.release()  # Signale que le message est rempli


def recepteur(arg):
    global message
    while True:
        time.sleep(random.randint(1, 3))  # Attente

        sem_plein.acquire()  # attend que le message soit plein
        print(f"Recepteur reçoit : {chr(message)}")

        sem_vide.release()  # Signale que le message etait lue


def main():
    random.seed()

    # creation des threads
    thread_emetteur  = threading.Thread(target=emetteur,  args=(None,))
    thread_recepteur = threading.Thread(target=recepteur, args=(None,))

    thread_emetteur.start()
    thread_recepteur.start()

    # Attend leurs fin
    thread_emetteur.join()
    thread_recepteur.join()

    return 0

main()