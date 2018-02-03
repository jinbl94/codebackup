/***************************************************************************
 * server.c
 * this is the server program of utalk
*************************************************************************
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
#include "utalk.h"

#define QLEN 32
#define BUFSIZE 4096

void reaper(int);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);

//main
int main(int argc, char *argv[]){
	char *service="9999";//default service
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
				exit(sendList(ssock,(struct sockaddr_in)&fsin));
			default:
				(void) close(ssock);
				break;
			case -1:
				errexit("fork: %s\n", strerror(errno));
		}
	}
}

//sendList
int sendList(int fd,(struct sockaddr_in)addr){
	char buf[BUFSIZE];
	int cc;
	while(cc=read(fd,buf,sizeof(buf))){
		if(cc<0)
			errexit("echo read: %s\n",strerror(errno));
		buf[cc]="\0";
		UserPtr userptr=(UserPtr)buf;
		userptr->addr=addr;
		addUser(userptr);
		if(write(fd, (char *)usertable, sizeof(User)*size)<0)
			errexit("echo write: %s\n", strerror(errno));
	}
	return 0;
}

//reaper
void reaper(int sig){
	int status;
	while(wait3(&status, WNOHANG, (struct rusage *)0)>=0);
}
