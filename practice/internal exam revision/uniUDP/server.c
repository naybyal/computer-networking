#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024

int main() {
    int sockfd, length;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server, client;

    //  socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //  bind
    if (bind(sockfd, (const struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("Error binding socket");
        exit(1);
    }

    length = sizeof(client);

    //  send / receive
    while (1) {
        // fflush(stdin);
        recvfrom(sockfd, (const char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client, &length);
        // buffer[len-1] = '\0';
        printf("Client : %s", buffer);
    } 

    //  close
    if (close(sockfd) < 0) {
        perror("Error closing socket");
        exit(1);
    }
    
    return 0;
}
