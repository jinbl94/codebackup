/********************************************************/
/*                        Enigma                        */
/*you can use this program to encode and decode messages*/
/********************************************************/
//"rotor.h" (which is in the same directory with this program) must be included.
#include<iostream>
#include<fstream>
#include<cstdlib>
#include"./rotor.h"
using namespace std;
void usage(void){
	cout<<"USAGE: ./enigma M C"<<endl;
	exit(1);
}
//M and C are arguments (names of files, M is the plaintext and C the ciphertext) need to be input by you.
class Enigma{
private:
	//rotor r[0] is used as the plug board, rotor r[4] is the static rotor. the others are dynamic rotors.
	Rotor r[5];
	char in,o;
	int m,c1,c;
public:
	//file_r is the file which content the number serieses of rotors
	//file_in is the original text need to be encoded.
	//file_out is the file which is used to store the encoded messages.
	Enigma(char* f_in,char* f_out){
		ifstream file_r,file_in,file_key;
		ofstream file_out;
		//initialize the rotors based on the file rotors.
		file_r.open("data/rotors",ios::in);
		if(!file_r){
			cerr<<"failed to open data/rotors!"<<endl;
			exit(1);
		}
		for(;!file_r.eof();){
			int temp[26];
			for(int j=0;j<5;j++){
				for(int i=0;i<26;i++)
					if(!file_r.eof()) file_r>>temp[i];
				r[j].init(temp);
			}
		}
		//close "data".
		file_r.close();
		//set the initial step value of each rotor.
		file_key.open("data/key",ios::in);
		if(!file_key){
			cerr<<"failed to open data/key"<<endl;
			exit(1);
		}
		for(;!file_key.eof();){
			int temp;
			for(int i=0;i<5;i++){
				file_key>>temp;
				if(!file_key.eof())
					r[i].ss(temp);
			}
		}
		//finished setting keys.
		file_key.close();
		//encoding...
		file_in.open(f_in,ios::in);
		if(!file_in){
			cerr<<"failed to open "<<f_in<<endl;
			exit(1);
		}
		file_out.open(f_out,ios::out|ios::trunc);
		if(!file_out){
			cerr<<"failed to creat "<<f_out<<endl;
			exit(1);
		}
		file_in>>noskipws;
		for(int i=0;!file_in.eof();i++){
			int j,k,t1,t2;
			file_in>>in;
			if(!file_in.eof()){
				if(in==' '||in=='\t'||in=='\n')
					file_out<<in;
				else{
					m=(int)(in-65);
					c1=r[4].l(r[3].l(r[2].l(r[1].l(r[0].l(m)))));
					c=r[0].r(r[1].r(r[2].r(r[3].r(c1))));
					o=(char)(c+65);
					file_out<<o;
					t1=r[1].ss(1);
					t2=r[2].ss(t1);
					r[3].ss(t2);
				}
			}
		}
		//encoding finished. close the files "M" and "C".
		file_in.close();
		file_out.close();
	}
};
int main(int argc,char* argv[]){
	if(argc!=3)usage();
	Enigma enigma(argv[1],argv[2]);
	return 0;
}
