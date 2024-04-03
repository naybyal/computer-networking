#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/socket.h>
char msg[100];
void *recieve_message(void *my_sock)
{
	int sd=*((int*)my_sock);
	int len;
	while((len=recv(sd,msg,500,0))>0)
	{
		msg[len]='\0';
		fputs(msg,stdout);
	}
}
int main(int argc,char *argv[])
{
	pthread_t recvt;
	int sd;
	char sendmsg[100];
	struct sockaddr_in servaddr;
	char client_name[100];
	strcpy(client_name,argv[1]);
	sd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(8880);
	connect(sd, (struct sockaddr *)&servaddr, sizeof(servaddr));
	pthread_create(&recvt,NULL,(void *)recieve_message,&sd);
	while(fgets(msg,100,stdin)>0)
	{
		strcpy(sendmsg,client_name);
		strcat(sendmsg,":");
		strcat(sendmsg,msg);
		send(sd,sendmsg,strlen(sendmsg),0);
	}
	pthread_join(recvt,NULL);
	close(sd);
	return 0;
}
