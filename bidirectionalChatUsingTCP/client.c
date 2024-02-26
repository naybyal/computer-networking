#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main() {

	/*CLIENT PROGRAM*/

	int csd, len;
	char sendmsg[30], recvmsg[20];
	struct sockaddr_in cliaddr, servaddr;
	
	//	SOCKET
	csd = socket(AF_INET, SOCK_STREAM, 0);
	
	/**/
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(33345);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	 /**/
	//	CONNECT
	connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	while(1) {
		//	SEND
		printf("Client: ");
		fgets(sendmsg, 30, stdin);
		len = strlen(sendmsg);
		sendmsg[len-1] = '\0';
		send(csd, sendmsg, 20, 0);

		//	RECEIVE	
		recv(csd, recvmsg, 20, 0);
		printf("Server: %s\n", recvmsg);
	}
	//	CLOSE
	int x = close(csd);
}

