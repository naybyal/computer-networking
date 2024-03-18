#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 30

void main() {
	int ssd, clilen;
	char recvmsg[BUFFER_SIZE], sendmsg[BUFFER_SIZE];
	struct sockaddr_in cliaddr, servaddr;
	
	//	socket
	ssd = socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5600);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//	bind
	bind(ssd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	//	listen
	listen(ssd,5);

	clilen = sizeof(cliaddr);
	// client socket descriptor
	// 	accept
	int csd = accept(ssd, (struct sockaddr*)&cliaddr, &clilen);
	
	//	receive
	recv(csd, recvmsg, BUFFER_SIZE, 0);

	printf("%s\n", recvmsg);
	
	//	close
	close(ssd);
}
