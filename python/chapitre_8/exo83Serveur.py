# === SERVEUR ===
import socket
import os
import sys
import time

def traite_client(sock, addr_client):
    # Construction du nom du fichier de sauvegarde
    t        = time.localtime()
    ip       = addr_client[0]
    buf      = bytearray(1024)

    # Remplacer les points par des underscores dans l'IP
    ip = ip.replace('.', '_')

    # Format : /home/save/IP_aaaa_mm_jj.txt
    nom_fichier = f"/home/save/{ip}_{t.tm_year:04d}_{t.tm_mon:02d}_{t.tm_mday:02d}.txt"

    try:
        fp = open(nom_fichier, "wb")
    except Exception:
        print("fopen sauvegarde", file=sys.stderr)
        sock.close()
        return 1

    # Recevoir et écrire le fichier
    while True:
        buf = sock.recv(1024)
        if not buf:
            break
        fp.write(buf)

    fp.close()
    print(f"Fichier sauvegardé : {nom_fichier}")
    sock.close()


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    addr = ('', 12345)
    sock.bind(addr)
    sock.listen(5)

    print("Serveur démarré sur le port 12345")
    while True:
        cli, client_addr = sock.accept()
        if os.fork() == 0:
            traite_client(cli, client_addr)
            sys.exit(0)
        cli.close()

main()