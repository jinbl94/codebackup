#include <stdio.h>

const static int s[16]={
	0x6, 0x4, 0xc, 0x5, 0x0, 0x7, 0x2, 0xe,
	0x1, 0xf, 0x3, 0xd, 0x8, 0xa, 0x9, 0xb
};

int main(){
	int counter_array[0x10];
	int max=0;
	fprintf(stdout,"-\t");
	for(int j=0;j<0x10;j++){
		fprintf(stdout,"%x, ",j);
	}
	fprintf(stdout,"\n");
	for(int i=1;i<0x10;i++){
		max=0;
		fprintf(stdout,"%x\t",i);
		for(int j=0;j<0x10;j++){
			counter_array[j]=0;
		}
		for(int j=0;j<0x10;j++){
			counter_array[s[j]^s[j^i]]+=1;
		}
		for(int j=0;j<0x10;j++){
			fprintf(stdout,"%x, ",counter_array[j]);
			if(max<counter_array[j])max=counter_array[j];
		}
		fprintf(stdout,"max=%x\n",max);
	}
	return 0;
}
