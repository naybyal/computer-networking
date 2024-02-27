#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>

#define PACKET_SIZE 1024

// Simulate packet loss by dropping packets randomly with a given probability
bool isPacketLost(double lossProbability) {
    double randomValue = ((double)rand() / RAND_MAX);
    if (randomValue < lossProbability) {
        return true;
    }
    return false;
}

// Sender function
void sender(int sockfd, double lossProbability) {
    int sequenceNumber = 0;
    char packet[PACKET_SIZE];

    while (true) {
        // Prepare packet with sequence number
        sprintf(packet, "Packet-%d", sequenceNumber);

        // Send packet to receiver
        printf("Sender: Sending packet %d\n", sequenceNumber);
        if (!isPacketLost(lossProbability)) {
            send(sockfd, packet, strlen(packet), 0);
        }

        // Wait for acknowledgment from receiver
        printf("Sender: Waiting for acknowledgment...\n");
        recv(sockfd, packet, PACKET_SIZE, 0);
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

    while (true) {
        // Receive packet from sender
        recv(sockfd, packet, PACKET_SIZE, 0);

        // Simulate packet loss
        if (!isPacketLost(lossProbability)) {
            // Send acknowledgment back to sender
            printf("Receiver: Received packet %s\n", packet);
            send(sockfd, "ACK", 3, 0);
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
    int sockfd[2]; // Socket file descriptors for sender and receiver
    pid_t pid;

	sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
	sockfd[1] = socket(AF_INET, SOCK_STREAM, 0);
    // Create a pair of connected sockets for sender and receiver
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) < 0) {
        perror("socketpair");
        exit(EXIT_FAILURE);
    }

    // Fork a child process to act as sender
    pid = fork();
    if (pid == 0) {
        close(sockfd[0]); // Close unused receiver socket in child process
        sender(sockfd[1], 0.2); // 20% packet loss probability
    } else if (pid > 0) {
        // Parent process acts as receiver
        close(sockfd[1]); // Close unused sender socket in parent process
        receiver(sockfd[0], 0.2); // 20% packet loss probability
    } else {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}

