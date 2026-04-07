# === CLIENT ===
import socket
import sys

BUF = 1024

def main():
    if len(sys.argv) != 4:
        print(f"Usage : {sys.argv[0]} ip port fichier")
        sys.exit(1)

    # 1. Ouvrir le fichier local
    try:
        fp = open(sys.argv[3], "rb")
    except Exception:
        print("fopen", file=sys.stderr)
        sys.exit(1)

    # 2. Créer la socket et se connecter au serveur
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((sys.argv[1], int(sys.argv[2])))

    # 3. Envoyer le fichier par blocs de 1024 octets
    while True:
        buf = fp.read(BUF)
        if not buf:
            break
        sock.send(buf)

    fp.close()
    sock.close()

    print("Fichier envoyé au serveur.")

    return 0

main()