#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd, csockfd, length, size;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockadd*)&server, sizeof(server)) == -1) {
        printf("Binding failed.");
        exit(0);
    }

    if (listen(sockfd, 5) == -1) {
        printf("Listening failed.");
        exit(0);
    }
    int size = len(client);

    int newSocketDescriptor = accept(sockfd, (struct sockadd*)&client, &size);
    do {
        recv(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
        printf("Client : %s", buffer);

        printf("Server : ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
    } while (1);

    int x = close(newSocketDescriptor);
    int y = close(sockfd);
}