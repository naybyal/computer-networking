/*
*		*********************************************************
*		*	Author	- Nabiel		                    		*
*		*	Program	- FTP (Client)		                		*
*		*							                            *	
*		*							                            *	
*		*********************************************************
*
*/
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define MAX_FILENAME_LENGTH 20
#define MAX_BUFFER_SIZE 300

int main() {
    int clientsockfd, n, rc;
    char sendline[MAX_FILENAME_LENGTH], recvline[MAX_BUFFER_SIZE];
    struct sockaddr_in serveraddr;

    // Initialize server address structure
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(3000);

    // Create a socket for communication with the server
    clientsockfd = socket(AF_INET, SOCK_STREAM, 0);
    connect(clientsockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // Prompt user to enter a filename to request from the server
    printf("\nEnter the name of a file at the server\t");
    scanf("%s", sendline);
    n = strlen(sendline);

    // Send the filename to the server
    write(clientsockfd, sendline, n);
    
    // Clear the receive buffer
    bzero(recvline, sizeof(recvline));
    
    // Read the response from the server
    rc = read(clientsockfd, recvline, MAX_BUFFER_SIZE);

    // Print the contents of the file received from the server
    printf("\nContents of the file received from the server... \n\n");
    printf("%s", recvline);

    // Close the socket
    close(clientsockfd);
    return 0;
}

