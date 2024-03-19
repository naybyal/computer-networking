#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 30

void main() {
	int csd, clilen;
	char recvmsg[BUFFER_SIZE], sendmsg[BUFFER_SIZE];
	struct sockaddr_in cliaddr, servaddr;
	
	//	socket
	csd = socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5600);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//	connect
	connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	//	send and receive msg
	do {
		printf("Client : ");
		fgets(sendmsg, BUFFER_SIZE, stdin);
		send(csd, sendmsg, BUFFER_SIZE, 0);

		printf("Server : ");
		recv(csd, recvmsg, BUFFER_SIZE, 0);
		printf("%s\n", recvmsg);
	} while (1);

	//	close
	close(csd);
}
