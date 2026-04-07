"""
Ecrire un programme qui saisit un nom de ﬁchier texte au clavier et ouvre ce
ﬁchier dans l'éditeur emacs.
"""

import os

def main():
    fichier = input("Entrez le fichier à éditer : ")
    os.system(f"emacs {fichier}")

if __name__ == "__main__":
    main()