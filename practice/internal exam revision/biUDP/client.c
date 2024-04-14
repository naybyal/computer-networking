#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define PORT 5600

void main() {
    int sockfd, length;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server, client;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    int serverSize = sizeof(server);
    while (1) {

        printf("Client : ");
        fgets(buffer, BUFFER_SIZE, stdin);
        int len = strlen(buffer);
        buffer[len-1] = '\0';
        sendto(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (const struct sockaddr*)&server, sizeof(server));


        len = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_CONFIRM, (const struct sockaddr*)&server, &serverSize);
        buffer[len-1] = '\0'; 
        printf("Client : %s", buffer);
       
    }
}