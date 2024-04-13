#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd, length, clientSize;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);
    int clientSize = sizeof(client);
    int newSocketDescriptor = accept(sockfd, (struct sockaddr*)&client, &clientSize);

    do {
        recv(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
        printf("Client : %s", buffer);

        printf("Server : ");
        fgets(buffer, BUFFER_SIZE, stdin);
        length = len(buffer);
        buffer[length - 1] = '\0';
        send(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
    } while (1);

    int terminate2 = close(newSocketDescriptor);
    int terminate1 = close(sockfd);
}