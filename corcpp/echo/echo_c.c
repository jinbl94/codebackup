/***************************************************************************
 * echo_c.c
 * This is an echo client based on TCP
 ***************************************************************************
 */
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "socket.h"
int TCPecho(const char *host, const char *service);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

#define LINELEN 128

/*
 * main
 */
int main(int argc, char *argv[]){
    char *host="localhost";//default host if there is no host ip provided
    char *service="echo";//default service of this program
    switch(argc){
	case 1:
	    host="localhost";
	    break;
	case 3:
	    service=argv[2];
	    break;
	case 2:
	    host=argv[1];
	    break;
	default:
	    fprintf(stderr,"usage: echo_c [host [port]]\n");
	    exit(1);
    }
    TCPecho(host, service);
    exit(0);
}

//TCPecho
int TCPecho(const char *host, const char *service){
	char buf[LINELEN+1];
	int s, n;
	int outchars, inchars;

	s=connectTCP(host, service);

	while(fgets(buf, sizeof(buf), stdin)){
		buf[LINELEN]='\0';
		outchars=strlen(buf);
		(void) write(s, buf, outchars);

		for(inchars=0;inchars<outchars;inchars+=n){
			n=read(s, &buf[inchars], outchars-inchars);
			if(n<0)
				errexit("socket read failed: %s\n",strerror(errno));
		}
		fputs(buf, stdout);
	}
}
