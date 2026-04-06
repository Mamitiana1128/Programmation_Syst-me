#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF 256 

int main(int argc , char **argv )
{
    int fd_read ,fd_write ;
    char message[BUF] ;

    // Verification des argument
    if ( argc != 3 )
    {
        fprintf(stderr , "Usage : %s <pipe[0]>  <pipe[1]", argv[0] ) ;
        exit(0);
    }

    // Recuperation descripteur 
    
    fd_read =  atoi(argv[1] ) ;
    fd_write = atoi(argv[2]);

    close(fd_write);

    if ( read(fd_read , message , BUF ) == -1 )
    {
        fprintf(stderr , "Erreur : read\n") ;
        exit(1);
    }
    
    // affichage du message 

    printf("Fils Message recu : %s" , message ) ;

    close(fd_read) ;

    return (0);
}