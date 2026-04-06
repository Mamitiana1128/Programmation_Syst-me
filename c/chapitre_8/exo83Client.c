// === CLIENT ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



#define BUF 1024


int main(int argc, char **argv)
{
    int n ;
    FILE *fp ;

    if (argc != 4) 
    {
        printf("Usage : %s ip port fichier\n", argv[0]);
        exit(1);
    }

    // 1. Ouvrir le fichier local
    
    fp = fopen(argv[3], "r");
    if (!fp)
    {
        perror("fopen");
        exit(1);
    }

    // 2. Créer la socket et se connecter au serveur
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[2]));
    inet_aton(argv[1], &addr.sin_addr);
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));


    // 3. Envoyer le fichier par blocs de 1024 octets
    char buf[BUF];
    while ((n = fread(buf, 1, BUF, fp)) > 0)
    {
        write(sock, buf, n);
    }

    fclose(fp);
    close(sock);

    puts("Fichier envoyé au serveur.");

    return 0;
}