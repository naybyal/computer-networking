#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 33345
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int main() {
    int sockfd, client_sockets[MAX_CLIENTS], max_clients = MAX_CLIENTS, activity, i, valread;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server socket options
    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(sockfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int addrlen = sizeof(cliaddr);
    fd_set readfds;

    // Initialize client sockets array
    for (i = 0; i < max_clients; i++) {
        client_sockets[i] = 0;
    }

    while (1) {
        // Clear the socket set
        FD_ZERO(&readfds);

        // Add server socket to set
        FD_SET(sockfd, &readfds);
        int max_sd = sockfd;

        // Add child sockets to set
        for (i = 0; i < max_clients; i++) {
            int sd = client_sockets[i];

            if (sd > 0) {
                FD_SET(sd, &readfds);
            }

            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // Wait for activity on any of the sockets
        activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        // If activity on server socket, then it's an incoming connection
        if (FD_ISSET(sockfd, &readfds)) {
            int new_socket;
            if ((new_socket = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&addrlen)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            // Add new connection to array of sockets
            for (i = 0; i < max_clients; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    break;
                }
            }
        }

        // Handle client requests
        for (i = 0; i < max_clients; i++) {
            int sd = client_sockets[i];

            if (FD_ISSET(sd, &readfds)) {
                // Receive message from client
                if ((valread = read(sd, buffer, BUFFER_SIZE)) == 0) {
                    // Client disconnected
                    close(sd);
                    client_sockets[i] = 0;
                } else {
                    // Broadcast message to other clients
                    for (int j = 0; j < max_clients; j++) {
                        int send_sd = client_sockets[j];
                        if (send_sd != 0 && send_sd != sd) {
                            send(send_sd, buffer, strlen(buffer), 0);
                        }
                    }
                }
            }
        }
    }

    return 0;
}

