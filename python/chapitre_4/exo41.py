"""
Écrire un programme qui crée deux processus. Le processus père
ouvre un ﬁchier texte en lecture. On suppose que le ﬁchier est composé de mots formés de
caractères alphabétiques séparés par des espaces. Le processus ﬁls saisit un mot au clavier. Le
processus père recherche le mot dans le ﬁchier, et transmet au ﬁls la valeur 1 si le mot est dans
le ﬁchier, et 0 sinon. Le ﬁls aﬃche le résultat.
"""

import os
import sys
import struct

BUFF = 256

def main():
    resultat = 0
    trouver = 0

    # Création des 2 pipe
    tube_mot_r, tube_mot_w = os.pipe()
    tube_rep_r, tube_rep_w = os.pipe()

    if len(sys.argv) != 2:
        print("Faut preciser le nom du fichier")
        sys.exit(-1)

    pid = os.fork()

    if pid == -1:
        print("Erreur Fork")
        sys.exit(-1)
    elif pid == 0:
        os.close(tube_mot_r)
        os.close(tube_rep_w)

        tab_fils = input("Entrez le mot : ")

        # Envoie du message au Père
        os.write(tube_mot_w, tab_fils.encode().ljust(BUFF, b'\x00'))

        # Verification du resultat venant du père
        data = os.read(tube_rep_r, 4)
        resultat = struct.unpack('i', data)[0]
        if resultat:
            print("Mot trouvé")
        else:
            print("Mot pas encore trouvé")

        sys.exit(0)
    else:
        os.close(tube_mot_w)
        os.close(tube_rep_r)

        # Reception du message venant du fils
        tab_pere = os.read(tube_mot_r, BUFF).decode().rstrip('\x00').strip()

        # recherche le mot dans le fichier et return 1 au fils si trouvé et 0 si non
        with open(sys.argv[1], 'r') as fichier:
            for ligne in fichier.read().split():
                if ligne == tab_pere:
                    trouver = 1
                    break

        # Envoie du reponse au fils
        os.write(tube_rep_w, struct.pack('i', trouver))

        os.wait()

    return 0

main()