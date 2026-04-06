/*
Écrire un programme qui saisit au clavier un tableau d’entiers et sauve-
garde ce tableau au format binaire dans un ﬁchier ayant permission en écriture pour le groupe
du ﬁchier et en lecture seule pour les autres utilisateurs.
b) Écrire une programme qui charge en mémoire un tableau d’entiers tel que généré au a). Le
ﬁchier d’entiers ne contient pas le nombre d’éléments. Le programme doit fonctionner pour un
nombre quelconque de données entières dans le ﬁchier.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *tab = NULL ;
    FILE *f = fopen("data.bin", "rb");
    if (!f)
    {
        perror("Impossible d'ouvrir le fichier");
        return 1;
    }

    // 1. Déterminer la taille du fichier
    fseek(f, 0, SEEK_END);    // Aller à la fin du fichier
    long taille_octets = ftell(f); // Obtenir la position actuelle
    rewind(f);                // Revenir au début pour lire

    // 2. Calculer le nombre d'entiers
    int nb_elements = taille_octets / sizeof(int);

    if (nb_elements == 0) {
        printf("Le fichier est vide.\n");
        fclose(f);
        return 0;
    }

    // 3. Allouer la mémoire et lire
    tab = malloc(taille_octets);
    if (!tab)
    { 
        perror("Erreur allocation"); 
        return 1; 
    }

    fread(tab, sizeof(int), nb_elements, f);
    fclose(f);

    // 4. Affichage pour vérification
    printf("Chargement de %d entiers :\n", nb_elements);
    
    for (int i = 0; i < nb_elements; i++) 
    {
        printf("[%d] ", tab[i]);
    }
    
    printf("\n");

    free(tab);
    return 0;
}