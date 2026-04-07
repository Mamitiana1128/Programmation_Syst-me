import threading
import time
import random
import sys

mutex = threading.Lock()

compteur = 0
u = 0.0


def ma_fonction_thread(arg):
    global compteur, u
    id = arg

    while True:
        # Verouillage du mutex
        with mutex:
            compteur += 1

            if id == 0:
                u = f1(u)
            else:
                u = f2(u)

            print(f"Thread[{id + 1}]. Valeur u = {u:g}")
            sys.stdout.flush()

        # Dévérouillage du mutex (géré par 'with')

        time.sleep(random.randint(1, 5))


def f1(x):
    return 0.25 * (x - 1) * (x - 1)


def f2(x):
    return (1.0 / 6.0) * (x - 2) * (x - 2)


def main():
    global u
    random.seed()
    u = 1.0

    threads = []
    # Lancement des 2 threads
    for i in range(2):
        t = threading.Thread(target=ma_fonction_thread, args=(i,))
        threads.append(t)
        t.start()

    # Attend la fin des threads
    for t in threads:
        t.join()

    return 0

main()