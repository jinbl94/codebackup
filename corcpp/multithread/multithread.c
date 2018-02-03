#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_BUFFER_SIZE 10

enum Flag {FALSE,TRUE};

enum Flag flags[MAX_BUFFER_SIZE];
int buffer[MAX_BUFFER_SIZE];
int buffer_len=0;

sem_t sem_buffer;		//semaphore for the operation of buffer
sem_t sem_consumer;		//semaphore for consumer

int in=0;
int out=0;

void put(int number){
	buffer[in]=number;
	flags[in]=TRUE;
	buffer_len++;
	fprintf(stdout,"(%d)Put: %d\n",in,number);
	in=(in+1)%MAX_BUFFER_SIZE;
	return;
}

int take(void){
	int number;
	flags[out]=FALSE;
	buffer_len--;
	fprintf(stdout,"(%d)Take: %d\n",out,buffer[out]);
	number=buffer[out];
	out=(out+1)%MAX_BUFFER_SIZE;
	return number;
}

void *producer(void *msg){
	int num;
	int i=0;
	//produce 50 numbers and exit
	while(i<50){
		//produce a random number
		num=rand()%100;
		sem_wait(&sem_buffer);

		//add the random number into buffer while buffer isn't full
		if(buffer_len<10){
			put(num);

			//increase index
			i++;

			//notity the consumer when buffer isn't empty
			if(buffer_len==1){
				sem_post(&sem_consumer);
			}
		}

		sem_post(&sem_buffer);
	}
	//fprintf(stdout,"producer end\n");
	return 0;
}

void *consumer(void *msg){
	int num;
	int i=0;
	sem_wait(&sem_consumer);
	//get 50 numbers and exit
	while(i<50){
		sem_wait(&sem_buffer);
		num=take();
		sem_post(&sem_buffer);

		//increase index
		i++;
		
		//wait when buffer is empty
		if(buffer_len==0&&i<50){
			sem_wait(&sem_consumer);
			fprintf(stdout,"consumer waiting...\n");
		}
	}
	//fprintf(stdout,"consumer end\n");
	return 0;
}

void erroExit(char *msg){
	fprintf(stderr,"Error: %s\n",msg);
	exit(1);
}

int main(int argc,char **argv){
	pthread_t th_consumer,th_producer;
	//initialize buffer
	int i=0;
	for(;i<MAX_BUFFER_SIZE;i++){
		flags[i]=FALSE;
	}
	//set seed for random number
	srand((unsigned)time(NULL));

	//semaphore initialize
	if(sem_init(&sem_consumer,0,0)<0)
		erroExit("sem_consumer init");
	if(sem_init(&sem_buffer,0,1)<0)
		erroExit("sem_buffer init");

	//thread initialize
	if(pthread_create(&th_consumer,NULL,consumer,NULL)<0)
		erroExit("th_consumer create");
	if(pthread_create(&th_producer,NULL,producer,NULL)<0)
		erroExit("th_producer_a create");

	//thread destroy
	if(pthread_join(th_producer,NULL)<0)
		erroExit("th_producer destroy");
	if(pthread_join(th_consumer,NULL)<0)
		erroExit("th_consumer destroy");

	//semaphore destroy
	sem_destroy(&sem_consumer);
	sem_destroy(&sem_buffer);

	return 0;
}
