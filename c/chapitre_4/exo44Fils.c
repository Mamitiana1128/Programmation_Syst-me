#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF 256
int main(int argc , char **argv)
{
    
    // Verification des arguments 
    if (argc != 2)
    {
        fprintf(stderr ,"Usage : %s <VariableEnvName> \n", argv[0]);
        exit(1);
    }
    
    char *val ;
    char message[BUF] ;
    char fd_read[10] , fd_write[10] ;

    // Lire la variable d'environement
    val = getenv(argv[1]);

    if (val == NULL )
    {
        fprintf(stderr,"Erreur var d'env\n");
        exit(0);
    }
    
    // Recuperation du tube
    sscanf(val , "%s:%s" , fd_read ,fd_write ) ;

    // Lecture du message
    close( atoi(fd_write) ) ;

    read( atoi(fd_read) , message , BUF ) ;

    printf("Fils : message recu => %s\n",message ) ;

    close( atoi(fd_read)) ;

    return (0);

}