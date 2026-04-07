import os
import sys

BUF = 256

def main():
    # Verification des arguments
    if len(sys.argv) != 2:
        print(f"Usage : {sys.argv[0]} <VariableEnvName>", file=sys.stderr)
        sys.exit(1)

    message = bytearray(BUF)

    # Lire la variable d'environement
    val = os.getenv(sys.argv[1])

    if val is None:
        print("Erreur var d'env", file=sys.stderr)
        sys.exit(0)

    # Recuperation du tube
    parts = val.split(':')
    fd_read  = parts[0]
    fd_write = parts[1]

    # Lecture du message
    os.close(int(fd_write))

    data = os.read(int(fd_read), BUF)
    print(f"Fils : message recu => {data.decode()}")

    os.close(int(fd_read))

    return 0

main()