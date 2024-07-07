// SERVER 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

#define BUFFER_SIZE 1024

void main() {
  int sockfd, len;
  char buffer[BUFFER_SIZE];
  struct sockaddr_in server, client;

  //  socket
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  server.sin_family = AF_INET;
  server.sin_port = htons(5600);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  // bind 
  bind(sockfd, (struct sockaddr*)&server, sizeof(server));

  int clilen = sizeof(client);

  while (1) {
    recvfrom(sockfd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr*)&client, &clilen);

    struct tm* timeinfo;
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", timeinfo);

    sendto(sockfd, buffer, BUFFER_SIZE, MSG_CONFIRM, (struct sockaddr*)&client, clilen);
  }
}




