//  concurrent time server application using UDP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>

#define BUFFER_SIZE 1024

void main() {
    int sockfd;
    struct sockaddr_in server;
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    sendto(sockfd, buffer, BUFFER_SIZE, MSG_CONFIRM, (struct sockaddr*)&server, sizeof(server));

    int len = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&server, sizeof(server));
    buffer[len] = '\0';
    
    printf("Server Time : %s\n", buffer);
}