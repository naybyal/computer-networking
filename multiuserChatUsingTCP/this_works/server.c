#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

pthread_mutex_t mutex;
int clients[20];
int n = 0;

void sendtoall(char *msg, int curr) {
    int i;
    pthread_mutex_lock(&mutex);
    for (i = 0; i < n; i++) {
        if (clients[i] != curr) {
            send(clients[i], msg, strlen(msg), 0);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *receive_message(void *csd) {
    int sd = *((int *)csd);
    char msg[500];
    int len;
    while ((len = recv(sd, msg, 500, 0)) > 0) {
        msg[len] = '\0';
        sendtoall(msg, sd);
    }
    return NULL;
}

int main() {
    struct sockaddr_in servaddr;
    pthread_t recvt;
    int sd = 0, csd = 0;

    pthread_mutex_init(&mutex, NULL);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8880);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    printf("server started\n");

    bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(sd, 5);

    while (1) {
        csd = accept(sd, (struct sockaddr*)NULL, NULL);
        pthread_mutex_lock(&mutex);
        clients[n] = csd;
        n++;
        pthread_create(&recvt, NULL, receive_message, &csd);
        pthread_mutex_unlock(&mutex);
    }

    close(sd);
    return 0;
}

