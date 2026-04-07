"""
Ecrire un programme qui prend en argument des noms de répertoire et aﬃche
la liste des ﬁchiers de ces répertoires qui ont une taille supérieure à (à peu près) 1M o avec
l'UID du propriétaire du ﬁchier.
"""

import os
import sys
import stat

def main():
    # Verification des arguments
    if len(sys.argv) != 2:
        print(f"Usage : {sys.argv[0]} <File>", file=sys.stderr)
        sys.exit(1)

    # Parcour du repertoire
    with os.scandir(sys.argv[1]) as dir_iter:
        for file in dir_iter:
            st = file.stat()

            if stat.S_ISREG(st.st_mode) and st.st_size >= 1000000:  # Si superieur à 1Mo
                print(f"Fichier : {file.name} ({st.st_uid})")

    return 0

main()