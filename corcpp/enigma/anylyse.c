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
	ifstream myfile_in;
	char temp;
	double number[26];
	double freq[26];
	double i=0;int j=0;
	for(;j<26;number[j]=0,freq[j]=0,j++);
	myfile_in.open(argv[1],ios::in);
	if(!myfile_in){
		cerr<<"Erro: open "<<argv[1]<<" failed!";
		exit(1);
	}
	for(;!myfile_in.eof();){
		myfile_in>>temp;
		temp-=65;
		number[temp]++;
		i++;
	}
	i--;
	myfile_in.close();
	ofstream myfile;
	myfile.open(argv[2],ios::out|ios::trunc);
	if(!myfile){
		cerr<<"Erro: open "<<argv[2]<<" failed!";
		exit(1);
	}
	myfile<<"N="<<"		"<<(int)i<<endl;
	for(j=0;j<26;j++){
		myfile<<(char)(j+65)<<"		"<<number[j]<<endl;
	}
	myfile.close();
	return 0;
}
void usage(void){
	cout<<"USAGE: ./anylyse [original file] [object file]"<<endl;
}
