#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <strings.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_BUFFER_SIZE 300

int main() {
    int serversockfd, newserversockfd, clilen, n, f;
    char line[MAX_FILENAME_LENGTH], fline[MAX_BUFFER_SIZE];
    struct sockaddr_in clientaddr, serveraddr;

    serversockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(3000);

    bind(serversockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(serversockfd, 5);

    while (1) {
        clilen = sizeof(clientaddr);
        newserversockfd = accept(serversockfd, (struct sockaddr *)&clientaddr, &clilen);
        n = read(newserversockfd, line, MAX_FILENAME_LENGTH);
        printf("\n The requested file name from the client is\t\t%s", line);

        printf("\n");

        f = open(line, O_RDWR);
        n = read(f, fline, MAX_BUFFER_SIZE);
        printf("\nThe contents of the file are\n\n");
        printf("%s", fline);
        write(newserversockfd, fline, n);
        close(newserversockfd);
    }

    close(serversockfd);
    return 0;
}

