"""
ême question qu'à l'exercice ?? mais en passant les descripteurs de tube
comme variables d'environnement.
"""

import os
import sys

def main():
    if len(sys.argv) != 2:
        print(f"Usage : {sys.argv[0]} <Chemin_Program>", file=sys.stderr)
        sys.exit(1)

    # Creation du pipe
    tube_r, tube_w = os.pipe()

    # Creation du variable d'environement
    os.environ["DESCRIPTEUR"] = f"{tube_r}:{tube_w}"

    # Lancement du fork
    try:
        pid = os.fork()
    except OSError:
        print("Erreur Fork")
        sys.exit(0)

    if pid == 0:
        args = [sys.argv[1], "DESCRIPTEUR"]
        os.execv(sys.argv[1], args)

        print("Erreur execv")
        sys.exit(1)

    else:
        # Envoie du message du Père
        os.close(tube_r)
        message = "Salut je suis ton Père !!\n"
        os.write(tube_w, message.encode() + b'\x00')

        os.close(tube_w)
        os.wait()

    return 0

main()