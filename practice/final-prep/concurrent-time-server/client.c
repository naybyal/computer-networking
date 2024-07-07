#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

void  main() {
  int sockfd, len;
  struct sockaddr_in  server;
  char buffer[BUFFER_SIZE];

  // socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(5600);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  sendto(sockfd, "TR", sizeof("TR"), MSG_CONFIRM, (struct sockaddr*)&server, sizeof(server));
  recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&server, sizeof(server));
  len = strlen(buffer);

  buffer[len] = '\0';
  printf("Server : %s", buffer);

}
