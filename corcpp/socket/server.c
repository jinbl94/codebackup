#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#define PORT 9999
#define SIZE 4096
int close_socket(int sock){
	if(close(sock)){
		fprintf(stderr,"Failed closing socket!\n");
		return 1;
	}
	return 0;
}
int main(int argc,char* argv[]){
	int sock,c_sock;
	ssize_t readret;
	socklen_t c_size;
	struct sockaddr_in addr,c_addr;
	char buf[SIZE],sd[SIZE];
	//creat server socket
	if((sock=socket(PF_INET,SOCK_STREAM,0))==-1){
		fprintf(stderr,"Failed creating socket.\n");
		return EXIT_FAILURE;
	}
	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=INADDR_ANY;
	//bind listening socket
	if(bind(sock,(struct sockaddr*)&addr,sizeof(addr))){
		close_socket(sock);
		fprintf(stderr,"Failed binding socket.\n");
		return EXIT_FAILURE;
	}
	//listen
	if(listen(sock,5)){
		close_socket(sock);
		fprintf(stderr,"Error when listening on socket.\n");
		return EXIT_FAILURE;
	}
	fprintf(stdout,"Server\n");
	//loop to detect if there are connecting request
	while(1){
		c_size=sizeof(c_addr);
		if((c_sock=accept(sock,(struct sockaddr*)&c_addr,&c_size))==-1){
			close_socket(sock);
			fprintf(stderr,"Error answering connection request.\n");
			return EXIT_FAILURE;
		}
		readret=0;
		//recieve the message sent by client
		while((readret=recv(c_sock,buf,SIZE,0))>1){
			//show the message sent by client
			fprintf(stdout,"Client: %sLocal: ",buf);
			//enter the message will be sent to client
			fgets(sd,SIZE,stdin);
			if(send(c_sock,sd,strlen(sd),0)!=strlen(sd)){
				close_socket(c_sock);
				close_socket(sock);
				fprintf(stderr,"Error sending message.\n");
				return EXIT_FAILURE;
			}
			memset(buf,0,SIZE);
		}
		if(readret==-1){
			close_socket(c_sock);
			close_socket(sock);
			fprintf(stderr,"Error recieving message.\n");
			return EXIT_FAILURE;
		}
	}
	close_socket(sock);
	return EXIT_SUCCESS;
}

