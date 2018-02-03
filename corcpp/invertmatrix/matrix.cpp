#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <NTL/mat_ZZ.h>
#include <NTL/ZZ.h>
#include <NTL/vec_ZZ.h>

#include <cmath>
#include <stack>

using namespace std;
using namespace NTL;

int main(int argc,char* argv[]){
	mat_ZZ p_m,p_s;
	vec_ZZ temp_m,temp_s;
	int op[3];
	if(argc!=2)exit(1);
	int size_n=atoi(argv[1]);

	p_s.SetDims(size_n,size_n);
	p_m.SetDims(size_n,size_n);
	for(int i=0;i<size_n;i++){
		for(int j=0;j<size_n;j++){
			p_s[i][j]=RandomBnd(100);
			p_m[i][j]=RandomBnd(100);
		}
	}

	temp_m.SetLength(size_n);
	temp_s.SetLength(size_n);

	srand((int)time(NULL));

	for(int i=0;i<size_n*10;i++){
		op[0]=rand()%size_n;
		do{
			op[1]=rand()%size_n;
		}while(op[0]==op[1]);
		op[2]=rand()%3-1;
		temp_m=p_m[op[0]];
		for(int j=0;j<size_n;j++){
			temp_s[j]=p_s[j][op[1]];
		}
		if(op[2]==0){
			p_m[op[0]]=p_m[op[1]];
			p_m[op[1]]=temp_m;
			for(int j=0;j<size_n;j++){
				p_s[j][op[1]]=p_s[j][op[0]];
				p_s[j][op[0]]=temp_s[j];
			}
		}else{
			p_m[op[1]]+=temp_m*op[2];
			for(int j=0;j<size_n;j++){
				p_s[j][op[0]]+=temp_s[j]*(-op[2]);
			}
		}
	}

	exit(0);
}
