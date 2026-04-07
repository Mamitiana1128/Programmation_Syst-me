"""
Ecrire un programme qui saisit des nom de ﬁchiers texte au clavier et
ouvre tous ces ﬁchiers dans l'éditeur emacs. Le programme doit se poursuivre jusqu'à ce que
l'utilisateur demande de quitter.
"""

import os

def main():
    fichiers = []

    while True:
        fichier = input("Entrer le fichier : ")
        fichiers.append(fichier)

        rep = input("Voulez vous continuez à ajouter(o/n)")
        if rep != 'o':
            break

    for f in fichiers:
        pid = os.fork()
        if pid == 0:
            os.system(f"vim {f}")
            os._exit(0)

    os.wait()
    print("Processus términer")

if __name__ == "__main__":
    main()