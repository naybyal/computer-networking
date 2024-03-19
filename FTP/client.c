#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 20
#define MAX_BUFFER_SIZE 300

int main() {
    int clientsockfd, n, rc;
    char sendline[MAX_FILENAME_LENGTH], recvline[MAX_BUFFER_SIZE];
    struct sockaddr_in serveraddr;

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(3000);

    clientsockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(clientsockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        printf("\nCannot Connect");
        exit(0);
    }

    printf("\nEnter the name of a file at the server\t");
    scanf("%s", sendline);
    n = strlen(sendline);
    write(clientsockfd, sendline, n);
    bzero(recvline, sizeof(recvline));
    rc = read(clientsockfd, recvline, MAX_BUFFER_SIZE);

    printf("\nThe contents of the file at the server are\n\n");
    printf("%s", recvline);

    close(clientsockfd);
    return 0;
}

