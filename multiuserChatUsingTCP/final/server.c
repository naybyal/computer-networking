#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 20
#define BUFFER_SIZE 500
#define PORT 8880

int clients[MAX_CLIENTS];
int client_count = 0;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void send_to_all(char *msg, int current) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; ++i) {
        if (clients[i] != current) {
            send(clients[i], msg, strlen(msg), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void *receive_message(void *client_sock) {
    int sd = *((int *)client_sock);
    char msg[BUFFER_SIZE];
    int len;
    while ((len = recv(sd, msg, BUFFER_SIZE - 1, 0)) > 0) {
        msg[len] = '\0';
        send_to_all(msg, sd);
    }
    close(sd);
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; ++i) {
        if (clients[i] == sd) {
            clients[i] = clients[client_count - 1];
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);
    return NULL;
}

int main() {
    struct sockaddr_in servaddr;
    int server_sock, client_sock;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(server_sock, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(server_sock, 5);

    printf("Server started on port %d\n", PORT);

    while (1) {
        client_sock = accept(server_sock, NULL, NULL);

        pthread_mutex_lock(&clients_mutex);
        if (client_count < MAX_CLIENTS) {
            clients[client_count++] = client_sock;
            pthread_t recv_thread;
            pthread_create(&recv_thread, NULL, receive_message, &client_sock);
        } else {
            close(client_sock);
        }
        pthread_mutex_unlock(&clients_mutex);
    }

    close(server_sock);
    return 0;
}

