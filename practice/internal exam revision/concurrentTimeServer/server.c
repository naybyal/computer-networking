#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

#define BUFFER_SIZE 1024

void main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server, client;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));

    int clientSize = sizeof(client);

    while (1) {
        int len = recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client, &clientSize);
        buffer[len] = '\0';

        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, BUFFER_SIZE, "%Y-%m-%d %H-%M-%S", timeinfo);
        

        sendto(sockfd, (char *)buffer, BUFFER_SIZE, MSG_CONFIRM, (struct sockaddr*)&client, clientSize);
    }
}