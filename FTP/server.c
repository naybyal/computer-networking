/*
*		*********************************************************
*		*	Author	- Nabiel		                    		*
*		*	Program	- FTP (Server)	                			*
*		*						                            	*	
*		*						                            	*	
*		*********************************************************
*
*/


#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <strings.h>

#define MAX_FILENAME_LENGTH 100
#define MAX_BUFFER_SIZE 300

	//	server

int main() {
    int serversockfd, newserversockfd, clilen, n, f;
    char line[MAX_FILENAME_LENGTH], fline[MAX_BUFFER_SIZE];
    struct sockaddr_in clientaddr, serveraddr;

    // Create a socket for the server
    serversockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address structure
    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(3000);

    // Bind the socket to the server address
    bind(serversockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // Listen for incoming connections
    listen(serversockfd, 5);

    while (1) {
        clilen = sizeof(clientaddr);

        // Accept incoming connection from a client
        newserversockfd = accept(serversockfd, (struct sockaddr *)&clientaddr, &clilen);

        // Read the filename requested by the client
        n = read(newserversockfd, line, MAX_FILENAME_LENGTH);
        printf("\n The requested file name from the client is\t\t%s", line);

        // Open the requested file
        f = open(line, O_RDWR);

        // Read the contents of the file
        n = read(f, fline, MAX_BUFFER_SIZE);

        // Print the contents of the file
        printf("\nThe contents of the file are\n\n");
        printf("%s", fline);

        // Send the contents of the file to the client
        write(newserversockfd, fline, n);

        // Close the connection with the client
        close(newserversockfd);
    }

    // Close the server socket
    close(serversockfd);
    return 0;
}

