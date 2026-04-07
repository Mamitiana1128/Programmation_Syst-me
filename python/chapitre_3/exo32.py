"""
Ecrire un programme qui prend en argument un chemin vers un répertoire R, et copie le répertoire courant dans ce répertoire R.
"""

import os
import sys
import shutil

def main():
    if len(sys.argv) != 2:
        print("Inserez le chemin vers le repertoire")
        sys.exit(-1)
    else:
        shutil.copytree(os.getcwd(), sys.argv[1], dirs_exist_ok=True)

if __name__ == "__main__":
    main()