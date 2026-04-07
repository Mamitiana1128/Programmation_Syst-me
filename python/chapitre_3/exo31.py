import sys

def main():
    if len(sys.argv) != 3:
        print("Vous devez inserez 2 arguments")
        sys.exit(-1)

    somme = int(sys.argv[1]) + int(sys.argv[2])
    print("Somme :", somme)

if __name__ == "__main__":
    main()