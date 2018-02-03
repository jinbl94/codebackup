/****client.h****/
#ifndef CLIENT
#define CLIENT
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
//send message
int client(char* name,char* ipaddr,char* port){
	char buf[SIZE];
	int status,p_sock,b_rec;
	struct addrinfo hints;
	//put hints into ram
	memset(&hints,0,sizeof(struct addrinfo));
	struct addrinfo* p_info;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	//transform ipaddress
	while(getaddrinfo(ipaddr,port,&hints,&p_info));
	//initialize the exit string
	char ex[]="exit",bye[]="BYE";
	memcpy(buf,name,strlen(name));
	buf[strlen(name)]='\n';
	//creat peer socket
	if((p_sock=socket(p_info->ai_family,p_info->ai_socktype,p_info->ai_protocol))==-1){
		fprintf(stderr,"peersocket\n");
		usage();
	}
	//connect to peer machine
	while(connect(p_sock,p_info->ai_addr,p_info->ai_addrlen));
	while(strncmp(buf,ex,4)){
		//send message to peer machine
		send(p_sock,buf,strlen(buf),0);
		while(!recv(p_sock,buf,SIZE,0))
			send(p_sock,buf,strlen(buf),0);
		memset(buf,0,SIZE);
		//get message
		fgets(buf,SIZE,stdin);
		if(!strncmp(buf,ex,4)){
			fprintf(stdout,"EXITING...\n");
			send(p_sock,bye,strlen(bye),0);
			freeaddrinfo(p_info);
			close(p_sock);
			return 0;
		}
	}
	close(p_sock);
	return 0;
}
#endif

