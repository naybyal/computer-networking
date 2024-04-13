#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Add this line for the `inet_addr` function

#define BUFFER_SIZE 1024

int main() {
    //  client program
        
    int sockfd, length;
    struct sockaddr_in server, client;
    char buffer[BUFFER_SIZE];

    //  SOCKET
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use the `inet_addr` function to convert the IP address

    //  SEND / RECEIVE
    while (1){
        printf("Client : ");
        fgets(buffer, BUFFER_SIZE, stdin);
        length = strlen(buffer);
        buffer[length-1] = '\0';
        if (strncmp(buffer, "bye", 3) == 0) {
            printf("BYE!");
            break;
        }
        sendto(sockfd, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr*)&server, sizeof(server));
    }
    
    //  CLOSE
    int x = close(sockfd);
    return 0;
}