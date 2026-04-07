"""
Reprendre les programmes de l'exercice ??. Nous allons faire un programme
qui fait la même chose, mais transmet les données diﬀérement. Dans le programme père, on
liera les ﬂots stdout et stdin à un tube.
"""

import os
import sys
import struct

BUF = 256

def main():
    reponse = 0
    resultat = 0

    # verification du argument
    if len(sys.argv) != 2:
        print("Entrez le nom du fichier", file=sys.stderr)
        os._exit(0)

    # Crée des tubes
    rep_pipe_r, rep_pipe_w = os.pipe()
    word_pipe_r, word_pipe_w = os.pipe()

    # Lancement du fork
    try:
        pid = os.fork()
    except OSError:
        print("Erreur Fork")
        os._exit(0)

    if pid == 0:
        os.close(word_pipe_r)
        os.close(rep_pipe_w)

        fils_mot = input("Entrez le mot : ")
        # envoie du mot
        os.write(word_pipe_w, fils_mot.encode() + b'\x00')

        # Verification du resultat
        data = os.read(rep_pipe_r, 4)
        reponse = struct.unpack('i', data)[0]
        if reponse:
            print("Mot trouvé")
        else:
            print("Mot Pas trouvé")
        os._exit(0)

    else:
        os.close(rep_pipe_r)
        os.close(word_pipe_w)

        os.dup2(word_pipe_r, sys.stdin.fileno())
        os.dup2(rep_pipe_w, sys.stdout.fileno())

        os.close(rep_pipe_w)
        os.close(word_pipe_r)

        # Ouverture du fichier
        pere_mot = sys.stdin.buffer.read(BUF).decode().rstrip('\x00').strip()

        with open(sys.argv[1], 'r') as fichier:
            for ligne in fichier.read().split():
                if ligne == pere_mot:
                    resultat = 1
                    break

        # Envoie du resultat
        sys.stdout.buffer.write(struct.pack('i', resultat))
        sys.stdout.buffer.flush()

        os.wait()

    return 0

main()