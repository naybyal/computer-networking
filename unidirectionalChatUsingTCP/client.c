#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main() {

	/*CLIENT PROGRAM*/

	int csd, len;
	char sendmsg[30], recvmsg[20];
	struct sockaddr cliaddr, servaddr;
	//	SOCKET
	csd = socket(AF_INET, SOCK_STREAM, 0);
	
	//servaddr.sin_family = AF_INET;
	//servaddr.sin_port = htons(33345);
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//	CONNECT
	connect(csd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	
	//	SEND
	printf("Reading the message to be transmitted.... \n");
	fgets(sendmsg, 30, stdin);
	//	RECEIVE	- not implemented in unidirectional chat
	//	CLOSE
	int count = close(csd);
}
