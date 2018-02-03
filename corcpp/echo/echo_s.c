/***************************************************************************
 * echo_s.c
 * this is the echo server program
 * *************************************************************************
 */

#define _USE_BSD
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "passivesocket.h"
#include "socket.h"

#define QLEN 32
#define BUFSIZE 4096

void reaper(int);
int TCPechod(int fd);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);

//main
int main(int argc, char *argv[]){
	char *service="echo";//default service
	struct sockaddr_in fsin;
	unsigned int alen;
	int msock;
	int ssock;
	switch(argc){
		case 1:
			break;
		case 2:
			service=argv[1];
			break;
		default:
			errexit("usage: TCPecho [port]\n");
	}

	msock=passiveTCP(service, QLEN);

	(void)signal(SIGCHLD, reaper);

	while(1){
		alen=sizeof(fsin);
		ssock=accept(msock, (struct sockaddr *)&fsin, &alen);
		if(ssock<0){
			if(errno==EINTR)
				continue;
			errexit("accept: %s\n", strerror(errno));
		}
		switch(fork()){
			case 0:
				(void) close(msock);
				exit(TCPechod(ssock));
			default:
				(void) close(ssock);
				break;
			case -1:
				errexit("fork: %s\n", strerror(errno));
		}
	}
}

//TCPechod
int TCPechod(int fd){
	char buf[BUFSIZE];
	int cc;
	while(cc=read(fd, buf, sizeof(buf))){
		if(cc<0)
			errexit("echo read: %s\n",strerror(errno));
		if(write(fd, buf, cc)<0)
			errexit("echo write: %s\n", strerror(errno));
	}
	return 0;
}

//reaper
void reaper(int sig){
	int status;
	while(wait3(&status, WNOHANG, (struct rusage *)0)>=0);
}
