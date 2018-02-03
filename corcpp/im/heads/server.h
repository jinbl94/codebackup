/****server.h****/
#ifndef SERVER
#define SERVER
#include<netdb.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>
#include"function.h"
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#define SIZE 4096
//wait for peer machine's request
int server(unsigned short int port){
	int sock,p_sock;
	ssize_t readret;
	socklen_t p_size;
	struct sockaddr_in addr,p_addr;
	char buf[SIZE],res[]="Peer: message recieved",bye[]="BYE";
	if((sock=socket(PF_INET,SOCK_STREAM,0))==-1){
		fprintf(stderr,"socket\n");
		usage();
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=INADDR_ANY;
	//bind socket
	if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))){
		close_socket(sock);
		fprintf(stderr,"binding\n");
		usage();
	}
	//listening
	if(listen(sock,5)){
		close_socket(sock);
		fprintf(stderr,"listening\n");
		usage();
	}
	p_size=sizeof(p_addr);
	while(1){
		if((p_sock=accept(sock,(struct sockaddr*)&p_addr,&p_size))==-1){
			close_socket(sock);
			fprintf(stderr,"accept\n");
			usage();
		}
		readret=0;
		//recieve the message sent by client
		while((readret=recv(p_sock,buf,SIZE,0))>1){
			//show the message sent by client
			buf[readret]='\0';
			fprintf(stdout,"> %s",buf);
			if(send(p_sock,res,strlen(res),0)!=strlen(res)){
				close_socket(p_sock);
				close_socket(sock);
				fprintf(stderr,"responding\n");
				usage();
			}
			if(!strncmp(buf,bye,3)){
				close_socket(p_sock);
				close_socket(sock);
				fprintf(stdout,"SERVEREXITING...\n");
				return 0;
			}
		}
		memset(buf,0,SIZE);
		if(readret==-1){
			close_socket(p_sock);
			close_socket(sock);
			fprintf(stderr,"recieving\n");
			usage();
		}
		close_socket(sock);
	}
	return 0;
}
#endif

