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
#include <aio.h>

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
    
	// implement aio
    struct aiocb *aio_req_array;
    aio_req_array = malloc(maxfdp1 * sizeof(struct aiocb));
    if (aio_req_array == NULL) {
    	perror("malloc aiocb fail");
    	exit(1);
    }
    
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
                int fp = open(buffer, O_RDONLY);
    			memset(buffer, 0, MAXLINE);
                if(fp == -1){
                	//printf("No File found!\n");
                	strcpy(buffer, "randomfile");
                } else {
                	int rd;
                	//strcpy(buffer, "randomfile");
                	//while(rd = read(fp, buffer, MAXLINE));
                }
                
                //https://man7.org/linux/man-pages/man7/aio.7.html iOList
                
                aio_req_array[connfd].aio_fildes = fp;
                aio_req_array[connfd].aio_offset = 0;
                aio_req_array[connfd].aio_buf = buffer;
                aio_req_array[connfd].aio_nbytes = MAXLINE;
    			memset(buffer, 0, MAXLINE);
                aio_read(&aio_req_array[connfd]);
                //write(fd, (const char*)buffer, sizeof(buffer));
    			//close(fd);
    		}
    	}
    	for (fd = 0; fd < maxfdp1; fd++) {
    		printf("aio Checking [%d]: .. \n", fd);
    		printf("aio Checking Buff[%d]: %s \n", fd, (const char*)aio_req_array[fd].aio_buf);
    		if ((const char*)aio_req_array[fd].aio_buf != NULL) {
    		int readstatus;
    		printf("aio Reading [%d]: .. \n", fd);
    		printf("aio Reading Buff[%d]: %s \n", fd, (const char*)aio_req_array[fd].aio_buf);
    		readstatus = aio_error(&aio_req_array[fd]);
    		if (readstatus == 0) {
    			printf("Server read finished! Sending Data...\n");
    			printf("Data: %s\n", (const char*)aio_req_array[fd].aio_buf);
    			
    			write(fd, (const char*)aio_req_array[fd].aio_buf, sizeof(aio_req_array[fd].aio_buf));
    			close(aio_req_array[fd].aio_fildes);
    			close(fd);
    			FD_CLR(fd, &rset);
    		} else if ( readstatus == EINPROGRESS) {
    			}
    		}
    	}
    }
}
