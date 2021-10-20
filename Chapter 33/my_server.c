// Server program
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>

#define PORT 5000
#define MAXLINE 1024
int main()
{
    int listenfd, connfd, nready, maxfdp1;
    char buffer[MAXLINE];
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
  
    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
  
    // binding server addr structure to listenfd
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);
  
  
    // clear the descriptor set
    FD_ZERO(&rset);
    
    // get maxfd
    maxfdp1 = listenfd + 1;
    
    for (;;) {
    	FD_ZERO(&rset);
    	int fd;
    	for (fd = 0; fd < maxfdp1; fd++) {
    		FD_SET(fd, &rset);
    	}
    	
    	int rc = select(maxfdp1, &rset, NULL, NULL, NULL);
    	
    	for (fd = 0; fd < maxfdp1; fd++) {
    		if (FD_ISSET(fd, &rset)) {
    			connfd = accept(fd, (struct sockaddr*)&cliaddr, &len);
    			memset(buffer, 0, MAXLINE);
                read(connfd, buffer, sizeof(buffer));
                printf("Message from Client with FD(%d): %s\n", connfd, buffer);
    			memset(buffer, 0, MAXLINE);
                strcpy(buffer, "Answer from Server!");
                write(connfd, (const char*)buffer, sizeof(buffer));
    			close(connfd);
    		}
    	}		
    }
}
