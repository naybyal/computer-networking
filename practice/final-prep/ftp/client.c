#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#define FILENAME_LENGTH 30
#define BUFFER_SIZE 1024

void main() {
    int sockfd, response_len;
    char request[FILENAME_LENGTH], buffer[BUFFER_SIZE];
    struct sockaddr_in server;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Set server address
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    // Get filename from user
    printf("Enter the file name to be requested from the server: ");
    scanf("%s", request);
    int len = strlen(request);

    // Send filename request to server
    write(sockfd, request, len);

    // Read response from server
    response_len = read(sockfd, buffer, BUFFER_SIZE);
    buffer[response_len] = '\0';
    printf("The contents of the file are:\n\n%s", buffer);
    close(sockfd);
}

