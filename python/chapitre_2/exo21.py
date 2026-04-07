import os
import sys

def main():
    pidFils = os.fork()
    status = 0

    if pidFils == -1:
        print("Erreur de lancement du Fork")
        sys.exit(-1)
    elif pidFils == 0:
        print("Je suis le fils")
        os._exit(0)
    else:
        print("Je suis le Pére")
        os.wait()

if __name__ == "__main__":
    main()