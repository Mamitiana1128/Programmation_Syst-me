// === SERVEUR ===
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

void traite_client(int sock, struct sockaddr_in *addr_client)
{

    // Construction du nom du fichier de sauvegarde
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char ip[50], nom_fichier[256], buf[1024];

    // Obtenir l'IP du client sous forme de chaîne
        strcpy(ip, inet_ntoa(addr_client->sin_addr));

    // Remplacer les points par des underscores dans l'IP
    for (int i = 0; ip[i]; i++)
    {
        if (ip[i]=='.') ip[i]='_';
    }

    // Format : /home/save/IP_aaaa_mm_jj.txt
        sprintf(nom_fichier, "/home/save/%s_%04d_%02d_%02d.txt", ip,tm_info->tm_year + 1900, tm_info->tm_mon + 1 , tm_info->tm_mday);

    FILE *fp = fopen(nom_fichier, "w");
    if (!fp) 
    {
        perror("fopen sauvegarde");
        close(sock);
        return (1) ; 
    }

    // Recevoir et écrire le fichier
    int n;
    while ((n = read(sock, buf, sizeof(buf))) > 0)
    {
        fwrite(buf, 1, n, fp);
    }

    fclose(fp);
    printf("Fichier sauvegardé : %s\n", nom_fichier);
    close(sock);

}

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr, client_addr;

    socklen_t len = sizeof(client_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 5);

    puts("Serveur démarré sur le port 12345");
    while(1)
    {
        int cli = accept(sock, (struct sockaddr*)&client_addr, &len);
        if (fork() == 0)
        {
            traite_client(cli, &client_addr);
            exit(0);
        }
        close(cli);
    }
}