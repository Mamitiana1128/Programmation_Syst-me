/*
Ecrire un programme qui prend en argument un chemin vers un répertoire R, et copie le répertoire courant dans ce répertoire R.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc , char **argv)
{
    if (argc != 2 )
    {
        perror("Inserez le chemin vers le repertoire\n");
        exit(-1);
    }
    else
    {
        execl("/usr/bin/cp" , "cp" , "-r" , getenv("PWD")  , argv [1] , NULL ) ;
    }
    
    return 0 ;
}