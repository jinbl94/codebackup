/****im****/
#include"heads/server.h"
#include"heads/client.h"
int main(int argc,char* argv[]){
	unsigned short int port=atoi(argv[4]);
	if(argc!=5){
		fprintf(stderr,"arguments error!\n");
		usage();
	}
	//creat a new process, and the value of pid in the new process is 0
	int pid=fork();
	if(pid)
		client(argv[1],argv[2],argv[3]);
	else
		server(port);
	return 0;
}
