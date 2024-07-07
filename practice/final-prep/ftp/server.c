#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024
#define FILENAME_LENGTH 30
void main() {
    int server_sockfd, client_sockfd, client_len;
    char request[FILENAME_LENGTH], buffer[BUFFER_SIZE];
    struct sockaddr_in server, client;

    // Create socket
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(server_sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(server_sockfd, 5);

    while (1) {
        client_len = sizeof(client);
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client, &client_len);

        // Read filename request from client
        int len = read(client_sockfd, request, FILENAME_LENGTH);
        request[len] = '\0';
        printf("The requested file is %s\n", request);
        // Open requested file
        int file_fd = open(request, O_RDONLY);
        // Read file contents and send to client
        int read_len = read(file_fd, buffer, BUFFER_SIZE);
        write(client_sockfd, buffer, read_len);
        
        close(file_fd);
        close(client_sockfd);
    }
    close(server_sockfd);
}
