"""
Écrire un programme qui saisit au clavier un tableau d'entiers et sauve-
garde ce tableau au format binaire dans un ﬁchier ayant permission en écriture pour le groupe
du ﬁchier et en lecture seule pour les autres utilisateurs.
b) Écrire une programme qui charge en mémoire un tableau d'entiers tel que généré au a). Le
ﬁchier d'entiers ne contient pas le nombre d'éléments. Le programme doit fonctionner pour un
nombre quelconque de données entières dans le ﬁchier.
"""

import struct
import sys

def main():
    tab = None

    try:
        with open("data.bin", "rb") as f:
            # 1. Déterminer la taille du fichier
            f.seek(0, 2)               # Aller à la fin du fichier
            taille_octets = f.tell()   # Obtenir la position actuelle
            f.seek(0)                  # Revenir au début pour lire

            # 2. Calculer le nombre d'entiers
            nb_elements = taille_octets // 4   # sizeof(int) = 4

            if nb_elements == 0:
                print("Le fichier est vide.")
                return 0

            # 3. Allouer la mémoire et lire
            data = f.read(taille_octets)
            tab = list(struct.unpack(f'{nb_elements}i', data))

    except FileNotFoundError:
        print("Impossible d'ouvrir le fichier")
        return 1

    # 4. Affichage pour vérification
    print(f"Chargement de {nb_elements} entiers :")

    for i in range(nb_elements):
        print(f"[{tab[i]}] ", end='')

    print()

    return 0

main()