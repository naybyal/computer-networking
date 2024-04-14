#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

    bind(sockfd, (const struct sockaddr*)&server, sizeof(server));

    int clientSize = sizeof(client);

    while (1) {
        recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client, &clientSize);
        if (strncmp(buffer, "bye", 3) == 0) {
            printf("BYE!");
            break;
        }
        printf("Client : %s", buffer);
    }
}