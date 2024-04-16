#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 100

char msg[SIZE];

void *receive(void *mySocket) {
    int sockfd = *((int *)mySocket);
    int len;

    while ((len = recv(sockfd, msg, SIZE, 0)) > 0) {
        msg[len] = '\0';
        fputs(msg, stdout);
    }
}

int main(int argc, char *argv[]) {
    pthread_t receiver;
    char sendmsg[SIZE], clientName[SIZE];
    int sockfd;
    struct sockaddr_in server;

    strcpy(clientName, argv[1]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5600);
    server.sin_addr.s_addr = INADDR_ANY;

    connect(sockfd, (struct sockaddr*)&server, sizeof(server));

    pthread_create(&receiver, NULL, (void *)receive, &sockfd);

    while (fgets(msg, SIZE, stdin) > 0) {
        strcpy(sendmsg, clientName);
        strcat(sendmsg, " : ");
        strcat(sendmsg, msg);
        send(sockfd, sendmsg, strlen(sendmsg), 0);
    }

    pthread_join(receiver, NULL);
    return 0;
}