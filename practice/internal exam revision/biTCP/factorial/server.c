#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    int sockfd, length, clientSize;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    int number, result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);
    clientSize = sizeof(client);
    int newSocketDescriptor = accept(sockfd, (struct sockaddr*)&client, &clientSize);

    do {
        recv(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
        number = atoi(buffer); // Convert string to integer
        result = factorial(number);
        sprintf(buffer, "%d", result); // Convert result back to string
        send(newSocketDescriptor, buffer, strlen(buffer) + 1, 0);

    } while (1);

    int terminate2 = close(newSocketDescriptor);
    int terminate1 = close(sockfd);
    return 0;
}
