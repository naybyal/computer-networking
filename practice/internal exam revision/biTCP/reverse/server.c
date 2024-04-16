#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

void reverseString(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length / 2; i++) {
        char temp = str[i];
        str[i] = str[length - i - 1];
        str[length - i - 1] = temp;
    }
}

int main() {
    int sockfd, length, clientSize;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];
    char reversedString[BUFFER_SIZE];

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
        printf("Original string received from client: %s\n", buffer);

        reverseString(buffer);
        printf("Reversed string: %s\n", buffer);

        send(newSocketDescriptor, buffer, strlen(buffer) + 1, 0);

    } while (1);

    int terminate2 = close(newSocketDescriptor);
    int terminate1 = close(sockfd);
    return 0;
}
