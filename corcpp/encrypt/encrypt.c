#include<stdlib.h>
#include<iostream>
#include<fstream>
using namespace std;
void encrypto(char* original,char* object,int a,int b);
char func(char c,int a,int b);
void usage(void);
int main(int argc,char* argv[]){
	if(argc!=3){
		usage();
		exit(1);
	}
	int a=1,b=0;
	cout<<"enter args (a,b): ";
	cin>>a>>b;
	ofstream myfile_key;
	myfile_key.open("./keys.secret",ios::app);
	if(!myfile_key){
		cerr<<"Erro: open ./keys.secret failed!"<<endl;
		exit(1);
	}
	myfile_key<<argv[2]<<'\t'<<a<<'\t'<<b<<endl;
	myfile_key.close();
	encrypto(argv[1],argv[2],a,b);
	return 0;
}
void encrypto(char* original,char* object,int a,int b){
	char ori,obj;
	ifstream myfile_ori;
	ofstream myfile_obj;
	myfile_ori.open(original,ios::in);
	myfile_obj.open(object,ios::out|ios::trunc);
	if(!myfile_ori){
		cerr<<"open file "<<original<<" failed!"<<endl;
		exit(1);
	}
	if(!myfile_obj){
		cerr<<"open file "<<object<<" failed!"<<endl;
		exit(1);
	}
	for(;!myfile_ori.eof();){
		myfile_ori>>ori;
		if(myfile_ori.eof())break;
		obj=func(ori,a,b);
		myfile_obj<<obj;
	}
	myfile_ori.close();
	myfile_obj.close();
}
char func(char c,int a,int b){
	char result;
	result=(a*(c-65)+b)%26+65;
	return result;
}
void usage(void){
	cout<<"USAGE: ./crypto [original file] [object file]"<<endl;
}
