#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

void main() {
  int serverSocketDescriptor, clientLength, len;
  struct sockaddr_in server, client;
  char buffer[BUFFER_SIZE];

  //  Describing Socket
  serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  server.sin_family = AF_INET;
  server.sin_port = htons(5600);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  //  Bind server
  len = sizeof(server);
  int checkBind = bind(serverSocketDescriptor, (struct sockaddr*)&server, len);

  //  Listen
  listen(serverSocketDescriptor, 5);

  //  Accept the connection by the server 
  clientLength = sizeof(client);
  int newSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr*)&client, &clientLength);
  
  while (1) {
    //  receive
    recv(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
    printf("Client: %s\n", buffer);

    printf("Server : ");
    fgets(buffer, BUFFER_SIZE, stdin);
    len = strlen(buffer);
    buffer[len-1] = '\0';
    send(newSocketDescriptor, buffer, BUFFER_SIZE, 0);
  }

  int closeClient = close(newSocketDescriptor);
  int closeServer = close(serverSocketDescriptor);

}
