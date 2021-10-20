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
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
    char* message = "Hello Client";
    void sig_chld(int);
  
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
    		FD_SET(connfd, &rset);
    	}
    	
    	int rc = select(maxfdp1, &rset, NULL, NULL, NULL);
    	
    	for (fd = 0; fd < maxfdp1; fd++) {
    		if (FD_ISSET(fd, &rset)) {
    			fd = accept(fd, (struct sockaddr*)&cliaddr, &len);
				if(fd < 0 ) {
    				perror("accept fail");
    				exit(1);
    			}
    			memset(buffer, 0, MAXLINE);
                read(fd, buffer, sizeof(buffer));
                printf("Message from Client with FD(%d): %s\n", fd, buffer);
                int fp = open(buffer, O_RDONLY);
                if(fp == -1){
                	//printf("No File found!\n");
                	//strcpy(buffer, "No File Found!");
                } //else {
                	//int rd;
                	//while(rd = read(fp, buffer, MAXLINE));
                //}
                aio_req_array[fd].aio_fildes = fp;
                aio_req_array[fd].aio_offset = 0;
                aio_req_array[fd].aio_buf = buffer;
                aio_req_array[fd].aio_nbytes = MAXLINE;
    			memset(buffer, 0, MAXLINE);
                
                int test_ar = aio_read(&aio_req_array[fd]);
                if (test_ar < 0) {
                	perror("aio_read fail");
                	exit(1);
                }
                //write(fd, (const char*)buffer, sizeof(buffer));
    			//close(fd);
    		}
    		
    	}
    	
    	for (fd = 0; fd < maxfdp1; fd++) {
    		struct aiocb *aio_req = &aio_req_array[fd];
    		if (aio_error(&aio_req_array[fd]) != EINPROGRESS) {
    			printf("Server read finished! Sending Data...\n");
    			write(fd, (const char*)aio_req->aio_buf, sizeof(aio_req->aio_buf));
    			close(fd);
    			close(aio_req->aio_fildes);
    		}
    	}
    }
}
