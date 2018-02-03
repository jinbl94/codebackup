/*
 * time_s.c
 * server program of time
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "passivesocket.h"

int passiveUDP(const char *service);
int errexit(const char *format,...);

#define UNIXEPOCH 2208988800UL

//main
int main(int argc, char *argv[]){
	struct sockaddr_in fsin;
	char *service="time";
	char buf[1];
	int sock;
	time_t now;
	unsigned int alen;

	switch(argc){
		case 1:
			break;
		case 2:
			service=argv[1];
			break;
		default:
			errexit("usage: time_s [port]\n");
	}

	sock=passiveUDP(service);

	while(1){
		alen=sizeof(fsin);
		if(recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&fsin,&alen)<0)
			errexit("recvfrom: %s\n",strerror(errno));
		(void)time(&now);
		now=htonl((unsigned long)(now+UNIXEPOCH));
		(void)sendto(sock,(char *)&now,sizeof(now),0,(struct sockaddr *)&fsin,sizeof(fsin));
	}
}
