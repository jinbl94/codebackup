#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
void usage(void);
int main(int argc,char* argv[]){
	if(argc!=3){
		usage();
		exit(1);
	}
	char ori;
	ifstream myfile_ori;
	ofstream myfile_obj;
	myfile_ori.open(argv[1],ios::in);
	myfile_obj.open(argv[2],ios::out|ios::trunc);
	if(!myfile_ori){
		cerr<<"Erro: open "<<argv[1]<<" failed!";
		exit(1);
	}
	if(!myfile_obj){
		cerr<<"Erro: open "<<argv[2]<<" failed";
		exit(1);
	}
	for(;!myfile_ori.eof();){
		myfile_ori>>ori;
		if('A'<=ori&&ori<='Z')
			myfile_obj<<ori;
		else if('a'<=ori&&ori<='z'){
			ori-=32;myfile_obj<<ori;
		}
		else;
	}
	return 0;
}
void usage(void){
	cout<<"USAGE: ./adjust [original file] [object file]"<<endl;
}
