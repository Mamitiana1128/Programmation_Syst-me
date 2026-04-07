"""
Ecrire un programme qui saisit des noms de répertoires au clavier et copie
le répertoire courant dans tous ces répertoires. Le programme doit se poursuivre jusqu'à ce que
l'utilisateur demande de quitter le programme.
"""

import os
import shutil

def main():
    while True:
        repertoire = input("Entrer le repertoire : ")
        shutil.copytree(os.getcwd(), repertoire, dirs_exist_ok=True)

        rep = input("Voulez vous continuez à ajouter(o/n)")
        if rep != 'o':
            break

if __name__ == "__main__":
    main()