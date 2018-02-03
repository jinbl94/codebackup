/*********************************************************/
/*this program is used to produce random number serieses.*/
/*********************************************************/
#include<iostream>
#include<fstream>
//when programing with C in a linux system, we should include head files "cstdio", "cstdlib" and "ctime" instead of "stdio.h", "stdlib.h" and "time.h" in windows.
//in this program you can change the value of "j" in class "Order" to produce more or less number serieses.
#include<cstdlib>
#include<ctime>
using namespace std;
//set "j" to 3 to produce the number serieses for three rotors.
void usage(void){
	cout<<"USAGE: ./order rotors key"<<endl;
	exit(1);
}
class Order{
public:
	Order(char* file_r,char *file_k){
		int order[26],t,temp,i=0,j=0,used[26];
		for(int j=0;j<26;used[j]=0,order[j]=j,j++);
		ofstream file_out,file_key;
		file_key.open(file_k,ios::trunc);
		if(!file_key){
			cerr<<"failed to open "<<file_k<<endl;
			exit(1);
		}
		srand((unsigned)time(NULL));
		//produce the daily key.
		file_key<<0<<" ";
		for(j=0;j<3;j++){
			file_key<<rand()%13+1<<" ";
		}
		file_key<<0;
		file_key.close();
		//key set.
		file_out.open(file_r,ios::trunc);
		if(!file_out){
			cerr<<"faied to creat file "<<file_r<<endl;
			exit(1);
		}
		//this loop is used to creat the plug board.
		for(j=0;j<13;j++){
			temp=rand()%13+13;
			if(used[temp]==0){
				order[j]=temp;
				order[temp]=j;
				used[temp]=1;
			}
		}
		for(i=0;i<26;i++)file_out<<order[i]<<" ";
		file_out<<endl;
		//plug board set.
		for(i=0;i<26;used[i]=0,order[i]=i,i++);
		//the dynamic rotors.
		for(j=0;j<3;j++){
			for(i=0;i<26;i++){
				temp=rand()%26;
				t=order[i];
				order[i]=order[temp];
				order[temp]=t;
				}
			for(i=0;i<26;i++){
				file_out<<order[i]<<" ";
				order[i]=i;
			}
			file_out<<endl;
		}
		//rotors set.
		//the static rotor.
		for(j=0;j<26;order[j]=j,j++);
		for(j=0;j<13;j++){
			temp=rand()%13+13;
			if(used[temp]==0){
				order[j]=temp;
				order[temp]=j;
				used[temp]=1;
			}
		}
		for(i=0;i<26;i++)file_out<<order[i]<<" ";
		file_out<<endl;
		file_out.close();
		//static rotor set.
	}
};
//argv[1] stores the name of the file stores random number serieses used to creat the rotors of enigma.
//argv[2] is the file stores the daily key.
//actually you can set them by yourselt.
//this file is usually named as "data".
int main(int argc,char* argv[]){
	if(argc!=3)usage();
	Order	order(argv[1],argv[2]);
//this part is the check codes used to find out what we have got. you can also use orders such as "cat","echo" to display this file.
	/*ifstream file_in;
	file_in.open("rotors",ios::in);
	if(!file_in){
		cerr<<"failed to open file rotors"<<endl;
		exit(1);
	}
	for(;!file_in.eof();){
		file_in>>temp;
		if(file_in.eof())break;
		cout<<temp<<" ";
		i++;
		if(i%27==0)cout<<endl;
	}
	cout<<i<<endl;*/
	return 0;
}
