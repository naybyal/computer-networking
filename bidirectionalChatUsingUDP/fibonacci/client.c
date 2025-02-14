#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 33345
// #define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    int buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    int len, n;
    len = sizeof(servaddr);

    while (1) {
        // Send number of terms(of Fibonacci series) to server
        printf("Client: ");
        int numberOfTerms;
        scanf("%d", &numberOfTerms);  

        sendto(sockfd, &numberOfTerms, sizeof(numberOfTerms), MSG_CONFIRM, (const struct sockaddr *)&servaddr, len);

        // Receive Fibonacci array from server
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[numberOfTerms] = '\0';

        printf("Server: ");
        for (int i = 0; i < numberOfTerms; i++) {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }
    close(sockfd);
    return 0;
}
