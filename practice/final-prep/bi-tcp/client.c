#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

//  CLIENT program


void main() {
  int clientSockDescriptor, len;
  char buffer[BUFFER_SIZE];

  struct sockaddr_in client, server;

  //  socket
  clientSockDescriptor = socket(AF_INET, SOCK_STREAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(5600);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  //  connect to server
  int connnectionEst = connect(clientSockDescriptor, (struct sockaddr*)&server, sizeof(server));

  while (1) {
    printf("Client: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    len = strlen(buffer);
    buffer[len-1] = '\0';

    send(clientSockDescriptor, buffer, BUFFER_SIZE, 0);
    recv(clientSockDescriptor, buffer, BUFFER_SIZE, 0);
    printf("Server: %s\n", buffer);
  }

  int closeConnection = close(clientSockDescriptor);
}
