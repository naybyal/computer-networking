#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int ssd, len, netSetDestination, clilen;
    char recvmsg[20];
    struct sockaddr_in servaddr, cliaddr;
    
    // SOCKET
    ssd = socket(AF_INET, SOCK_STREAM, 0);
    if (ssd == -1) 
        perror("Socket creation failed");
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(33345);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    // BIND
    if (bind(ssd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) 
        perror("Bind failed");

    // LISTEN
    if (listen(ssd, 5) == -1) 
        perror("Listen failed");
 
    printf("Listening to client on port 33345\n");
    

    // ACCEPT
    clilen = sizeof(cliaddr);
    netSetDestination = accept(ssd, (struct sockaddr*)&cliaddr, &clilen);
    if (netSetDestination == -1) 
        perror("Accept failed");
    
    // RECEIVE
    recv(netSetDestination, recvmsg, sizeof(recvmsg), 0);
    printf("Client says: %s\n", recvmsg);

    // CLOSE
    // close(netSetDestination);
    // close(ssd);
}
