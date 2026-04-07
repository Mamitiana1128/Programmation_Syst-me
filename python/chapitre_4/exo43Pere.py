"""
Écrire un programme qui crée un tube, crée un processus ﬁls,
puis, dans le ﬁls, lance par execv un autre programme, appelé programme ﬁls. Le programme
père transmets les descripteurs de tubes au programmes ﬁls en argument, et transmet un
message au ﬁls par le tube. Le programme ﬁls aﬃche le message.
"""

import os
import sys

def main():
    # Verification argument
    if len(sys.argv) != 2:
        print("Entrez le nom du programme fils en argument")
        sys.exit(1)

    # Création du pipe
    tube_r, tube_w = os.pipe()

    # Fork
    try:
        pid = os.fork()
    except OSError:
        print("Erreur Fork")
        sys.exit(1)

    if pid == 0:
        # Convertion en chaine de caractere du tube
        arg_read  = str(tube_r)
        arg_write = str(tube_w)

        args = [sys.argv[1], arg_read, arg_write]
        os.execv(sys.argv[1], args)

        print("Erreur execv")
        sys.exit(0)

    else:
        os.close(tube_r)
        message = "Bonjour je suis ton Père\n"
        os.write(tube_w, message.encode() + b'\x00')

        os.close(tube_w)
        os.wait()

    return 0

main()