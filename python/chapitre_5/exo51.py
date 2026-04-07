import threading
import sys

# Structure pour le tableau
class TypeTableau:
    def __init__(self):
        self.tableau = []
        self.taille  = 0


def ma_foncttion_thread(arg):
    tab = arg

    for i in range(tab.taille):
        print(tab.tableau[i], end='')

    # pthread_exit equivalent : return


def main():
    tab = TypeTableau()
    t = [2, 2, 3, 4, 5, 9]
    tab.tableau = t
    tab.taille  = 6

    thread = threading.Thread(target=ma_foncttion_thread, args=(tab,))
    thread.start()
    thread.join()

    return 0

main()