/*
Ecrire un programme qui prend en argument des noms de répertoire et aﬃche
la liste des ﬁchiers de ces répertoires qui ont une taille supérieure à (à peu près) 1M o avec
l’UID du propriétaire du ﬁchier.
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc , char **argv)
{
    // Verification des arguments 
    if (argc != 2 )
    {
        fprintf(stderr , "Usage : %s <File>\n", argv[0] ) ;
        exit(1) ;
    }

    struct stat st ;
    DIR *dir = opendir(argv[1]) ;
    struct dirent *file ;
    
    // Parcour du repertoire 
    while ((file = readdir(dir)) != NULL )
    {
        stat(file->d_name , &st ) ;
        
        if( S_ISREG(st.st_mode) && st.st_size >= 1000000 ) // Si supperieur à 1Mo
        {
            printf("Fichier : %s (%d)\n",file->d_name , st.st_uid) ;
        }
    }
    
    closedir(dir);
    
    return (0) ;
}