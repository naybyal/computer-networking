#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100

int clients[20];
int n = 0;

void sendToAll(char *msg, int curr) {
    for (int i=0; i<n; i++) {
        if (clients[i] != curr) {
            if (send(clients[i], msg, strlen(msg), 0) < 0) {
                printf("Failed to send the message...");
                continue;
            }
        }
    }
}

void *receive(void *csd) {
    int sockfd = *((int *)csd);
    char msg[SIZE];
    int len;

    while ((len = recv(sockfd, msg, SIZE, 0)) > 0) {
        msg[len] = '\0';
        sendToAll(msg, sockfd);
    }
}

int main() {
    pthread_t receiver;
    int sockfd, csd;
    struct sockaddr_in server;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server, sizeof(server));
    listen(sockfd, 5);

    while (1) {
        csd = accept(sockfd, (struct sockaddr*)NULL, NULL);
        clients[n++] = csd;
        pthread_create(&receiver, NULL, (void *)receiver, &csd);
    }
}