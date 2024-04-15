#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void main() {
    struct sockaddr_in server;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    int n = -1;

    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&server, sizeof(server));
    printf("Server connected successfully!\n");

    printf("Enter the total number of frames... ");
    scanf("%d", &n);
    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&server, sizeof(server));

    int len, ack;

    for (int i=1; i<=n; i++) {
        ack = -1;
        do {
            printf("\nSending frames %d", i);
            sendto(sockfd, &i, sizeof(n), 0, (struct sockaddr*)&server, sizeof(server));
            printf("\nWaiting for ACK...\n");
            recvfrom(sockfd, &ack, sizeof(n), 0, (struct sockaddr*)&server, sizeof(server));
            if (ack == 1)
                printf("\nNegative ACK received... Resending... \n");
        } while (ack == -1);
    }

    n = -99;
    sendto(sockfd, &n, sizeof(n),0, (struct sockaddr*)&server, sizeof(server));
    printf("\nSuccessfully sent all frames...\n");
    close(sockfd);
}