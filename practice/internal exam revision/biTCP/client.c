#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd, length;
    struct sockaddr_in server, client;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    length = sizeof(server);
    
    connect(sockfd, (struct sockaddr*)&server, length);

    char buffer[BUFFER_SIZE];
    do {
        printf("Client : ");
        fgets(buffer, BUFFER_SIZE, stdin);
        int size = strlen(buffer);
        buffer[size-1] = '\0';
        send(sockfd, buffer, BUFFER_SIZE, 0);

        recv(sockfd, buffer, BUFFER_SIZE, 0);
        printf("Server : %s\n", buffer);
    } while (1);

    int x = close(sockfd);
}