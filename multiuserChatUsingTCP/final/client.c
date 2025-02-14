#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 500
#define PORT 8880

void *receive_message(void *sock_fd) {
    int sd = *((int *)sock_fd);
    char msg[BUFFER_SIZE];
    int len;
    while ((len = recv(sd, msg, BUFFER_SIZE - 1, 0)) > 0) {
        msg[len] = '\0';
        fputs(msg, stdout);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <client_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int sd;
    char send_msg[BUFFER_SIZE];
    char client_name[100];
    strcpy(client_name, argv[1]);

    struct sockaddr_in servaddr;
    sd = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    pthread_t recv_thread;
    pthread_create(&recv_thread, NULL, receive_message, &sd);

    while (fgets(send_msg, BUFFER_SIZE, stdin) != NULL) {
        snprintf(send_msg, sizeof(send_msg), "%s: %s", client_name, send_msg);
        send(sd, send_msg, strlen(send_msg), 0);
    }

    pthread_join(recv_thread, NULL);
    close(sd);
    return 0;
}

