/***************************************************************************
 * client of utalk
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "socket.h"
#include "user.h"
#include "message.h"

int errexit(const char *format,...);
int connectTCP(const char *host,const char *service);

#define BUFLEN 4096
#define QLEN 32

/*
 * main
 */
int main(int argc,char *argv[]){
	char *host="localhost";
	char *service="9999";
	char *name;
	switch(argc){
		case 4:
			service=argv[3];
		case 3:
			host=argv[2];
		case 2:
			name=argv[1];
			break;
		default:
			fprintf(stderr,"usage: utalk <name> [host [port]]\n");
			exit(1);
	}
	int pid=fork();
	switch(pid){
		case 0:
			int msock=passiveTCP(service,QLEN);
			struct sockaddr_in fsin;
			unsigned int alen;
			int cc;
			char buf[BUFLEN];
			MessagePtr msg=null;
			while(1){
				alen=sizeof(fsin);
				int p_sock=accept(msock,(struct sockaddr *)fsin,&alen);
				if(p_sock<0){
					if(errno==EINTR)
						continue;
					errexit("accept: %s\n",strerror(errno));
				}
				while(cc=read(p_sock,buf,sizeof(buf))){
					if(cc<0)
						errexit("rad: %s\n",strerror(errno));
					msg=(Message)buf;
					fprintf(stdout,"%s: %s\n",msg->name,msg->msg);
				}
			}
			break;
		default:
			char msg[BUFLEN];
			while(fgets(msg,sizeof(msg),stdin)){
				sendMessage(msg);
				login();
			}
	}
	exit(0);
}
int login(,const char *name,const char *host,const char *service){
	char buf[BUFLEN];
	UserPtr userptr=(UserPtr)malloc(sizeof(User));
	userptr->next=null;
	userptr->name=name;
	userptr->time=time();
	int s;
	int cc;
	s=connectTCP(host,service);

	(void)write(s,(char *)userptr,sizeof(User));
	destroy();
	cc=read(s,buf,sizeof(buf))
		usertable=(UserPtr)buf;
}
int sendMessage(char *msg){
	UserPtr temp=usertable;
	while(temp->next!=null){
		int s;
		s=connectTCP(temp->addr->sin_addr,temp->addr->sin_port);
		(void)write(s,msg,sizeof(msg));
		temp=temp->next;
	}
}
