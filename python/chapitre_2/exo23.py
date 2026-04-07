import os
import sys

def main():
    for i in range(5):
        pidFils = os.fork()

        if pidFils == -1:
            print("Erreur Fork")
            sys.exit(-1)
        elif pidFils == 0:
            print(f"Je suis le Fils {i+1}")
            os._exit(1)
        else:
            if i == 0:
                print("Je suis le Père")

if __name__ == "__main__":
    main()