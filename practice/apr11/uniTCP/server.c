#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
    /*  SERVER SIDE */
int main() {
    int sockfd, clientSize;
    char messageBuffer[BUFFER_SIZE];
    struct sockaddr_in server, client;

    //  Initializing the socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //  Bind the socket to the server
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) == -1) {
        printf("Binding failed.");
        exit(0);
    }

    //  Listen for incoming connections
    if (listen(sockfd, 5) == -1) {
        printf("Listneing failed.");
        exit(0);
    }

    printf("Listening on port 5600...\n\n");
    clientSize = sizeof(client);

    //  Accept the connection
    int clientSockDescriptor = accept(sockfd, (struct sockaddr*)&client, &clientSize);
    
    // memset(messageBuffer, 0, BUFFER_SIZE);
    recv(clientSockDescriptor, messageBuffer, BUFFER_SIZE, 0);
    printf("Client says :\t %s\n", messageBuffer);    
    
    //  Terminate the connection
    if (close(sockfd) == -1) {
        printf("Failed to terminate the connection...\n");
        exit(0);
    }
    printf("\nConnection terminated!\n");

    return 0;
}
