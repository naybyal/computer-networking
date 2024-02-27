#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/arq_socket"
#define PACKET_SIZE 1024

// Simulate packet loss by dropping packets randomly with a given probability
bool isPacketLost(double lossProbability) {
    double randomValue = ((double)rand() / RAND_MAX);
    return randomValue < lossProbability;
}

// Sender function
void sender(int sockfd, double lossProbability) {
    int sequenceNumber = 0;
    char packet[PACKET_SIZE];
    struct sockaddr_un server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, SOCKET_PATH);

    while (true) {
        // Prepare packet with sequence number
        sprintf(packet, "Packet-%d", sequenceNumber);

        // Send packet to receiver
        if (!isPacketLost(lossProbability)) {
            sendto(sockfd, packet, strlen(packet), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
            printf("Sender: Sent packet %d\n", sequenceNumber);
        } else {
            printf("Sender: Packet %d lost\n", sequenceNumber);
        }

        // Wait for acknowledgment from receiver
        recvfrom(sockfd, packet, PACKET_SIZE, 0, NULL, NULL);
        printf("Sender: Received acknowledgment for packet %d\n", sequenceNumber);

        // Increment sequence number
        sequenceNumber++;

        // Check for termination
        if (strcmp(packet, "exit") == 0) {
            break;
        }
    }
}

// Receiver function
void receiver(int sockfd, double lossProbability) {
    int expectedSequenceNumber = 0;
    char packet[PACKET_SIZE];
    struct sockaddr_un client_addr;
    socklen_t len = sizeof(client_addr);

    while (true) {
        // Receive packet from sender
        recvfrom(sockfd, packet, PACKET_SIZE, 0, (struct sockaddr *)&client_addr, &len);

        // Simulate packet loss
        if (!isPacketLost(lossProbability)) {
            // Send acknowledgment back to sender
            sendto(sockfd, "ACK", 3, 0, (struct sockaddr *)&client_addr, len);
            printf("Receiver: Received packet %s\n", packet);
        } else {
            printf("Receiver: Packet %s lost\n", packet);
        }

        // Check for termination
        if (strcmp(packet, "exit") == 0) {
            break;
        }
    }
}

int main() {
    int sockfd;
    struct sockaddr_un addr;

    // Create socket
    if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind socket to address
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);
    unlink(SOCKET_PATH);
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Fork a child process to act as sender
    pid_t pid = fork();
    if (pid == 0) {
        sender(sockfd, 0.2); // 20% packet loss probability
    } else if (pid > 0) {
        // Parent process acts as receiver
        receiver(sockfd, 0.2); // 20% packet loss probability
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    close(sockfd);
    return 0;
}

