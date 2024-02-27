#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 33345
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sockid;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in servaddr;

    sockid = socket(AF_INET, SOCK_DGRAM, 0);

    //memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    while (1) {
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp(buffer, "bye", 3) == 0) {
            printf("Exiting...\n");
            break;
        }
        sendto(sockid, (const char *)buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    }

    close(sockid);
    return 0;
}

