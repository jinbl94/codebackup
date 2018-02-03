#include<iostream>
#include<fstream>
#include<unistd.h>
#include<memory.h>
#include".aba.h"
using namespace std;
ABA::ABA(char* In,char* Out,long datalen,char* key){
	if(!(Out&&In&&key)){
		cerr<<"ERROR"<<endl;
		_exit(1);
	}
	setsubkey(key);
	for(long i=0,j=datalen>>4;i<j;++i,Out+=16,In+=16)
		aba(In,Out);
}
void ABA::setsubkey(char* key){
	int i=0,j=0,k=0;
	bool bkey[128];
	btbi(bkey,key,128);
	transform(bkey,bkey,T,128);
	for(i=0;i<4;i++){
		for(j=0;j<64;j++){
			subkey[i][j]=bkey[k%128];
			k++;
		}
		k=(k+96)%128;
	}
	for(i=0;i<3;i++){
		for(int j=0;j<64;j++){
			subkey[i+4][j]=subkey[2-i][j];
		}
	}
}
void ABA::aba(char In[16],char Out[16]){
	bool temp[64],M[128],*L=&M[0],*R=&M[64],tm[128];
	int i=0,k=0;
	btbi(M,In,128);
	memcpy(tm,M,128);
for(k=0;k<128;k++){
	memcpy(M,tm,128);
	if(M[k]==1)
		M[k]=0;
	else
		M[k]=1;
	for(i=0;i<6;i++){
		memcpy(temp,R,64);
		func(R,subkey[i]);
		Xor(R,L,64);
		memcpy(L,temp,64);
	}
	memcpy(temp,R,64);
	func(temp,subkey[i]);
	Xor(L,temp,64);
	cout<<k+1<<"C";
	for(i=0;i<128;i++)
		cout<<M[i];
	cout<<endl;
}
	bitb(Out,M,128);
}
void ABA::func(bool In[64],bool key[64]){
	transform(In,In,TK,64);
	transform(key,key,TK,64);
	Xor(In,key,64);
}
void ABA::transform(bool* Out,bool* In,const char* t,int len){
	bool temp[len];
	for(int i=0;i<len;i++)
		temp[i]=In[t[i]-1];
	memcpy(Out,temp,len);
}
void ABA::Xor(bool* In1,bool* In2,int len){
	for(int i=0;i<len;i++)
		In1[i]^=In2[i];
}
void ABA::btbi(bool* Out,char* In,int len){
	for(int i=0;i<len;i++)
		Out[i]=(In[i>>3]>>(i&7))&1;
}
void ABA::bitb(char* Out,bool* In,int len){
	memset(Out,0,len>>3);
	for(int i=0;i<len;i++)
		Out[i>>3]|=In[i]<<(i&7);
}
ABA::~ABA(){
}
void usage(void){
	cerr<<"USAGE: ./aba m c"<<endl;
	_exit(1);
}
//function main
int main(int argc,char* argv[]){
	if(argc!=3){
		cerr<<"arguments"<<endl;
		usage();
	}
	int keylen=0,datalen=0,i=0;
	char *Out,*In,*K,c;
	ifstream file_i,file_k;
	ofstream file_o;
	file_k.open("data/key",ios::in);
	if(!file_k){
		cerr<<"failed to open data/key"<<endl;
		_exit(1);
	}
	file_k.seekg(0,ios::end);
	keylen=file_k.tellg();
	keylen--;
	if(keylen!=16){
		file_k.close();
		cerr<<"Error. Key is not 128 bits."<<endl;
		_exit(1);
	}
	file_k.seekg(0,ios::beg);
	K=new char[keylen];
	file_k>>c;
	for(i=0;!file_k.eof();){
		if(!file_k.eof()){
			K[i]=c;
			i++;
			}
		file_k>>c;
	}
	file_k.close();
	file_i.open(argv[1],ios::in);
	if(!file_i){
		cerr<<"failed to open "<<argv[1]<<endl;
		_exit(1);
	}
	file_o.open(argv[2],ios::out|ios::trunc);
	if(!file_o){
		cerr<<"failed to open "<<argv[2]<<endl;
		_exit(1);
	}
	file_i.seekg(0,ios::end);
	datalen=file_i.tellg();
	datalen=((datalen+15)&0xfffffff0);
	file_i.seekg(0,ios::beg);
	In=new char[datalen];
	Out=new char[datalen];
	file_i>>noskipws;
	file_i>>c;
	for(i=0;!file_i.eof();){
		if(!file_o.eof()){
			In[i]=c;
			i++;
		}
		file_i>>c;
	}
	for(;i<datalen;i++)In[i]='\0';
	cout<<"In\t\t"<<In;
	ABA aba(In,Out,datalen,K);
	for(i=0;i<datalen;i++)
		file_o<<Out[i];
	delete []In;
	delete []Out;
	file_i.close();
	file_o.close();
	return 0;
}
