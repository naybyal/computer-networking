#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void main() {
    int csd, len;
    char sendmsg[30];
    struct sockaddr_in servaddr;
    
    // SOCKET
    csd = socket(AF_INET, SOCK_STREAM, 0);
    if (csd == -1) 
        perror("Socket creation failed");
    
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(33345);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    
    // CONNECT
    if (connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) 
        perror("Connection failed");
    
    
    // SEND
    printf("Reading the message to be transmitted.... \n");
    fgets(sendmsg, sizeof(sendmsg), stdin);
    send(csd, sendmsg, strlen(sendmsg), 0);

    // CLOSE
    // close(csd);
    
}
