#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define BUFFER_SIZE 30

void main() {
	int ssd, len, clilen;
	char recvmsg[BUFFER_SIZE], sendmsg[BUFFER_SIZE];
	struct sockaddr_in cliaddr, servaddr;

	ssd = socket(AF_INET, SOCK_STREAM, 0);

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5600);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	len = sizeof(servaddr);

	bind(ssd, (struct sockaddr*)&servaddr, len);

	listen(ssd,5);

	clilen = sizeof(cliaddr);

	int nsd = accept(ssd, (struct sockaddr*)&cliaddr, &clilen);
	recv(nsd, recvmsg, BUFFER_SIZE, 0);

	printf("%s\n", recvmsg);

	close(ssd);
}
