#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netdb.h>
#define SIZE 4096
int main(int argc,char* argv[]){
	if(argc!=3){
		fprintf(stderr,"USAGE: ./client <server-ip> <port>\n");
		return EXIT_FAILURE;
	}
	char buf[SIZE];
	int status,sock;
	struct addrinfo hints;
	//put hints into the inbuild memory
	memset(&hints,0,sizeof(struct addrinfo));
	struct addrinfo* servinfo;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	//transform the ip address and port number
	if((status=getaddrinfo(argv[1],argv[2],&hints,&servinfo))!=0){
		fprintf(stderr,"Error geting address ifomation: %s\n",gai_strerror(status));
		return EXIT_FAILURE;
	}
	char ex[]="exit";
	char sd[SIZE];
	//input out loop
	fprintf(stdout,"Local: ");
	fgets(sd,SIZE,stdin);
	while(strncmp(sd,ex,4)){
		//creat server socket
		if((sock=socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol))==-1){
			fprintf(stderr,"Failed creating socket.\n");
			return EXIT_FAILURE;
		}
		//link to server
		if(connect(sock,servinfo->ai_addr,servinfo->ai_addrlen)==-1){
			fprintf(stderr,"Error connecting.\n");
			return EXIT_FAILURE;
		}
		//send message and revieve report
		int b_rec;
		send(sock,sd,strlen(sd),0);
		if((b_rec=recv(sock,buf,SIZE,0))>1){
			buf[b_rec]='\0';
			fprintf(stdout,"Server: %s",buf);
		}
		close(sock);
		//input in loop
		fprintf(stdout,"Local: ");
		fgets(sd,SIZE,stdin);
	}
	freeaddrinfo(servinfo);
	close(sock);
	return EXIT_SUCCESS;
}
