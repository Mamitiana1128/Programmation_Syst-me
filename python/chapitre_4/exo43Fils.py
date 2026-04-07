import os
import sys

BUF = 256

def main():
    # Verification des argument
    if len(sys.argv) != 3:
        print(f"Usage : {sys.argv[0]} <pipe[0]>  <pipe[1]>", file=sys.stderr)
        sys.exit(0)

    # Recuperation descripteur
    fd_read  = int(sys.argv[1])
    fd_write = int(sys.argv[2])

    os.close(fd_write)

    message = os.read(fd_read, BUF)
    if not message:
        print("Erreur : read", file=sys.stderr)
        sys.exit(1)

    # affichage du message
    print(f"Fils Message recu : {message.decode()}")

    os.close(fd_read)

    return 0

main()