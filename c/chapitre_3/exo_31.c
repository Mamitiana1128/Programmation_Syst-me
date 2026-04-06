#include <stdio.h>
#include <stdlib.h>

int main(int argc , char **argv)
{
    int somme ;

    if (argc != 3 )
    {
        perror("Vous devez inserez 2 arguments\n");
        exit(-1);
    }
    somme = atoi(argv[1]) + atoi(argv[2]) ;
    printf("Somme : %d \n",  somme ) ;

    return 0 ;
}