#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>

void main() {
	printf("\nWaiting for client.... \n");
	struct sockaddr_in servaddr, cliaddr;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&servaddr, 0 , sizeof(servaddr));
	memset(&cliaddr, 0 , sizeof(cliaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5600);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	
	int len = sizeof(cliaddr);
	int frames[100], n;
	
	recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&cliaddr, &len);
	printf("\nClient connected successfully!\n");
	printf("Waiting from total number of frames");
	recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr*)&cliaddr, &len);
	int p, ack;
	
	while (1) {
		recvfrom(sockfd, &p, sizeof(n),0,(struct sockaddr*)&cliaddr, &len);
		if (p == -99)
			break;
		printf("\nReceived frame %d ", p);
		printf("\nEnter 1 for +ve ACK and -1 for -ve ACK");
		scanf("%d", &ack);
		sendto(sockfd, &ack, sizeof(n),0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
	}
}
