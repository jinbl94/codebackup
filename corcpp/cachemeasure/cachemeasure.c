#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define KB 1024
int main(int argc,char **argv){
	int times=12;
	int k_size=8;		
	int mod=0;
	int strike=64;
	int steps=256*1024*1024;
	clock_t start;
	int time,extra_time;
	char *data,ch;
	fprintf(stdout,"size/K\ttime\n");

	//from 8KB to 16MB
	for(;k_size<16*1024+1;k_size<<=1){
		mod=k_size*KB-1;
		data=(char*)malloc(k_size*KB);

		start=clock();
		//access memory
		for(int j=0;j<steps;j++)
			data[(j*strike)&mod]++;
		time=(double)(clock()-start);

		if(k_size==8)extra_time=time;
		time-=extra_time;
		fprintf(stdout,"%d\t%d\t\n",k_size,time>0?time:0);
		free(data);
	}
}
