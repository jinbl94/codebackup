#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define KB 1024
int main(){
	int steps=256*1024*1024;
	char *data=(char*)malloc(512*KB);
	int mod=512*KB-1;
	int strike=4;
	int extra_time;
	clock_t time;
	fprintf(stdout,"strike\ttime\n");

	//strike from 4 to 1024
	for(;strike<1025;strike<<=1){

		//access memory
		time=clock();
		for(int i=0;i<steps;i++)data[(i*strike)&mod]++;
		time=clock()-time;

		if(strike==4)extra_time=time;
		time-=extra_time;
		fprintf(stdout,"%d\t%d\n",strike,time>0?time:0);
	}

	free(data);
}
