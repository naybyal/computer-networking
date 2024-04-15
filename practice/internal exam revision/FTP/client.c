#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define MAX_FILENAME_LENGTH 40
#define MAX_BUFFER_SIZE 1024

void main() {
    int sockfd, n, res;
    char fname[MAX_FILENAME_LENGTH], buffer[MAX_BUFFER_SIZE];
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    printf("\nEnter the name of the file at server... ");
    scanf("%s", fname);

    n = strlen(fname);

    // send filename to server
    write(sockfd, fname, n);

    //  GET response from the server
    res = read(sockfd, buffer, MAX_BUFFER_SIZE);
    printf("\nContents of the file are... \n\n");
    printf("%s\n", buffer);

    close(sockfd);
}