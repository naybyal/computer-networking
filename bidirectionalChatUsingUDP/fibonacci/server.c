#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 33345
#define BUFFER_SIZE 1024

int fibo[BUFFER_SIZE];

void generateFibonacciArray(int length) {
    if (length == 1) {
        fibo[0] = 0;
    } else if (length >= 2) {
        fibo[0] = 0;
        fibo[1] = 1;
        for (int i = 2; i < length; i++) {
            fibo[i] = fibo[i - 1] + fibo[i - 2];
        }
    }
}

// Server side
int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind the socket with the server address
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    int len, n;
    len = sizeof(cliaddr);
    int numberOfTerms;
    while (1) {
        // Receive number of terms(of Fibonacci series) from client
        n = recvfrom(sockfd, &numberOfTerms, sizeof(numberOfTerms), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        printf("Client requested %d terms\n", numberOfTerms);

        generateFibonacciArray(numberOfTerms);

        // Send Fibonacci array to client
        sendto(sockfd, fibo, numberOfTerms * sizeof(int), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    }

    return 0;
}
