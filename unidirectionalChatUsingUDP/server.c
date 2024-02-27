#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define PORT 33345
#define BUFFER_SIZE 1024

int main() {
    int sockid;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[BUFFER_SIZE];

    sockid = socket(AF_INET, SOCK_DGRAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    bind(sockid, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    int len, n;
    len = sizeof(cliaddr);

    while (1) {
        n = recvfrom(sockid, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Client : %s", buffer);
    }

    return 0;
}

