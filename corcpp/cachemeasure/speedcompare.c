#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define KB 1024
int result=0;
char data[32];
int main(){
	int delta_time;
	//int steps=2*KB;
	int steps=KB;
	struct timespec start,end;
	clockid_t clockid;
	pid_t pid=getpid();
	clock_getcpuclockid(pid,&clockid);
	//data access with cache enabled
	clock_gettime(clockid,&start);
	for(int i=0;i<steps;i++){
		data[i%(32)]++;
	}
	clock_gettime(clockid,&end);
	delta_time=1000000000*(end.tv_sec-start.tv_sec)+end.tv_nsec-start.tv_nsec;
	fprintf(stdout,"Time per access: %dns\n",delta_time/steps);

	//data access with cache disabled
	clock_gettime(clockid,&start);
	cache_off(void);
	for(int i=0;i<steps;i++){
		data[i%(32)]++;
	}
	cache_on(void);
	clock_gettime(clockid,&end);
	delta_time=1000000000*(end.tv_sec-start.tv_sec)+end.tv_nsec-start.tv_nsec;
	fprintf(stdout,"Time per access: %dns\n",delta_time/steps);
}
