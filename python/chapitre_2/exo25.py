import os
import sys
import random
import time

def filsAttendre():
    random.seed(time.time())
    nbsec = random.randint(1,10)
    time.sleep(nbsec)
    os._exit(nbsec)

def main():
    total = 0
    pidFils = os.fork()

    if pidFils == -1:
        print("Erreur Fork")
        sys.exit(-1)
    elif pidFils == 0:
        filsAttendre()
    else:
        pid, status = os.wait()
        total += os.WEXITSTATUS(status)

    if pidFils != 0:
        print(f"Pére : durée total : {total} sécondes")

if __name__ == "__main__":
    main()