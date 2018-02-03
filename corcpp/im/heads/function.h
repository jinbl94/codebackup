/****functions.h****/
#ifndef FUNCTION
#define FUNCTION
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
int close_socket(int sock){
	if(close(sock)){
		fprintf(stderr,"Failed closing socket!\n");
		return 1;
	}
	return 0;
}
//call this function if you want to stop the program
int usage(void){
	fprintf(stderr,"./im <name> <peerip> <peerport> <localport>\n");
	_exit(1);
}
#endif
