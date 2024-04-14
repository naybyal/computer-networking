#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

    /*  CLIENT SIDE */

int main() {
    int sockfd, len;
    struct sockaddr_in server, client;
    char messageBuffer[BUFFER_SIZE];

    //  Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    //  Connect to the server
    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Connection failed\n");
        exit(1);
    }

    printf("Client : \t");
    fgets(messageBuffer, BUFFER_SIZE, stdin);
    len = strlen(messageBuffer);

    messageBuffer[len-1] = '\0';

    //  Send the message
    send(sockfd, messageBuffer, BUFFER_SIZE, 0);

    if (close(sockfd) == -1) {
        printf("Error closing the socket\n");
        exit(1);
    }

    return 0;
}