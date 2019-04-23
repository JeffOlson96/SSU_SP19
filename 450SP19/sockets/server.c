#include<sys/types.h>	
#include<sys/socket.h>	
#include<arpa/inet.h>
#include<netinet/in.h>	
#include<sys/time.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

#define PORT_NUMBER 8085
#define MAXLINE 200
#define LISTENQ 5

// This server program creates a TCP socket and listen on port "PORT_NUMBER".

// To compile, do:
// gcc server.c -o server.x
// To run, do:
// ./server.x

// A server must be launched before clients can talk to it!
 
int main(int argc, char **argv)
{
    int	listenfd, connfd;
    socklen_t   len;
    struct sockaddr_in  servaddr, cliaddr;
    char	buff[MAXLINE];
    time_t	ticks;

    // Create an end-point for IPv4 Internet Protocol
    if( ( listenfd = socket(AF_INET, SOCK_STREAM, 0) ) < 0 ) {
	fprintf( stderr, "socket failed.  %s\n", strerror( errno ) );
	exit( 1 );

    }


    bzero(&servaddr, sizeof(servaddr));  // puts zeros in a chunk of memory (zero out struct)
    servaddr.sin_family      = AF_INET;  // Communicate using the Internet domain (AF_INET)
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);   // Who should we accept connections from? 
    // accept connections from anyone, or might have to restrict IPs if built for in-House stuff   
    							//host to network, convert value to be acceptable/readable by both host and client
    servaddr.sin_port        = htons(PORT_NUMBER);  // Which port should the server listen on?        

    // Bind the server end-point using the specifications stored in "serveraddr"
    if( bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
	fprintf( stderr, "Bind failed.  %s\n", strerror( errno ) );
	exit( 1 );
    }

    // Listen on the in-comming connections; pile up at most LISTENQ number of connections.
    if( listen(listenfd, LISTENQ) < 0 ) {
	fprintf( stderr, "Listen failed.  %s\n", strerror( errno ) );
	exit( 1 );
    }

    for ( ; ; ) {
		len = sizeof(cliaddr);
	// establish a connection with an incoming client.
		if( ( connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len) ) < 0 ) {
	    	fprintf( stderr, "Accept failed.  %s\n", strerror( errno ) );
	    	exit( 1 );
		}
		printf("connection from %s, port %d\n",
	    inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff)),
	    ntohs(cliaddr.sin_port));
	    // inet_ntop gets the IP address string
	    // ntohs gets the port number from the clientaddr

		// send info back to client using the connfd and buffer
		ticks = time(NULL);
		snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
		if( write(connfd, buff, strlen(buff)) < 0 ) {
	    	fprintf( stderr, "Write failed.  %s\n", strerror( errno ) );
	    	exit( 1 );
		}
		// finished talking to this client.  Close the connection.
		close(connfd);
    }
}
