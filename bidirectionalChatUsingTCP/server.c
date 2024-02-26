#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main() {
	//	SERVER PROGRAM
	int ssd, len, clilen;
	struct sockaddr_in cliaddr, servaddr;
	char sendmsg[30], recvmsg[20];
	
	//	SOCKET
	ssd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(33345);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	printf("Listening on port 33345\n");

	//	BIND
	len = sizeof(servaddr);
	bind(ssd, (struct sockaddr*)&servaddr, len);
	
	//	LISTEN
	listen(ssd, 5);
	
	//	ACCEPT
	clilen = sizeof(cliaddr);
	int netSetDestination = accept(ssd, (struct sockaddr*)&cliaddr, &clilen);
	printf("Client says... \n");
	
	//	SEND - not implemented in unidirectional chat
	// 	RECEIVE
	recv(netSetDestination, recvmsg, 20, 0);
	printf("%s\n", recvmsg);

	//	CLOSE	
	// int x = close(ssd);
}
