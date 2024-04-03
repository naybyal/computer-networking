#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/socket.h>

int clients[20];
int n =0;

void sendtoall(char *msg,int curr) {
	int i;
	for(i=0;i<n;i++) {
		if(clients[i]!=curr) {
			if(send(clients[i],msg,strlen(msg),0)<0) {
				printf("sending failure\n");
				continue;
			}
		}
	}
}

void *receive_message(void *csd) {
	int sd= *((int *)csd);
	char msg[500];
	int len;
	while((len=recv(sd,msg,500,0))>0) {
		msg[len]='\0';
		sendtoall(msg,sd);
	}
}

int main() {
	struct sockaddr_in servaddr;
	pthread_t recvt;
	int sd,csd;
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(8880);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	printf("server started");
	bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	listen(sd, 5);
	while(1) {
		csd=accept(sd,(struct sockaddr*)NULL,NULL);
		clients[n]=csd;
		n++;
		pthread_create(&recvt,NULL,(void *)receive_message,&csd);

	}
	return 0;
}
