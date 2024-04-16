#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd, length;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];
    char inputString[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    do {
        printf("Enter a string to reverse: ");
        fgets(inputString, BUFFER_SIZE, stdin);
        inputString[strcspn(inputString, "\n")] = '\0'; // Remove newline character

        send(sockfd, inputString, strlen(inputString) + 1, 0);

        recv(sockfd, buffer, BUFFER_SIZE, 0);
        printf("Reversed string received from server: %s\n", buffer);

    } while (1);

    int terminate = close(sockfd);
    return 0;
}
