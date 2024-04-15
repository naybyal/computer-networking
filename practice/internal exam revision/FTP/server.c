#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define MAX_FILENAME_LENGTH 40
#define MAX_BUFFER_SIZE 1024

void main() {
    int sockfd, newsockfd, clilen, n, req;
    char fname[MAX_FILENAME_LENGTH], buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in client, server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);

    
    while (1) {
        clilen = sizeof(client);
        newsockfd = accept(sockfd, (struct sockaddr*)&client, &clilen);

        n = read(newsockfd, fname, MAX_FILENAME_LENGTH);
        printf("\nThre requested file name from the client is : %s", fname);

        req = open(fname, O_RDWR);

        n = read(req, buffer, MAX_BUFFER_SIZE);

        printf("\nThe contents of the file are...\n\n");
        printf("%s\n", buffer);

        write(newsockfd, buffer, n);

        close(newsockfd);
    } 

    close(sockfd);    
}