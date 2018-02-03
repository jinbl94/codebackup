#include <stdio.h>
#include <stdlib.h>

//basic parameters
#define PROCESS_NAME_LEN 32
#define MIN_SLICE 10
#define DEFAULT_MEM_SIZE 1024
#define DEFAULT_MEM_START 0

//memory alloc algorithm
#define MA_FF 1
#define MA_BF 2
#define MA_WF 3

//default parameters
int mem_size=DEFAULT_MEM_SIZE;
int ma_algorithm=MA_FF;
static int pid=0;
int flag=0;

//free memoty block
struct free_block_type{
	int size;
	int start_addr;
	struct free_block_type *next;
};

//blocks allocated by process
struct allocated_block{
	int pid;
	int size;
	int start_addr;
	char process_name[PROCESS_NAME_LEN];
	struct allocated_block *next;
};

struct allocated_block *allocated_block_head=NULL;
//head of free blocks
struct free_block_type *free_block=NULL;


void king(struct free_block_type *h){
	struct free_block_type *p;

	if(h->next!=NULL){
		if((h->start_addr+h->size)==h->next->start_addr){
			p=h->next;
			h->size=h->size+p->size;
			h->next=p->next;
			free(p);
			king(h);
		}else{
			if(h->next!=NULL)king(h->next);
		}
	}
}

void freenode(struct free_block_type *h){
	struct free_block_type *p;
	while(h!=NULL){
		p=h;
		h=h->next;
		free(p);
	}
}

void freenod1(struct allocated_block *h){
	struct allocated_block *p;
	while(h!=NULL){
		p=h;
		h=h->next;
		free(p);
	}
}

struct free_block_type * init_free_block(int size){
	struct free_block_type *fb;
	fb=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	if(fb==NULL){
		fprintf(stdout,"Out of memoryi\n");
		return NULL;
	}
	fb->size=size;
	fb->start_addr=DEFAULT_MEM_START;
	fb->next=NULL;
	return fb;
}

void display_menu(){
	fprintf(stdout,"\n");
	fprintf(stdout,"1	Set size of memory (default=%d)\n",DEFAULT_MEM_SIZE);
	fprintf(stdout,"2	Set memory allocate algorithm\n");
	fprintf(stdout,"3	Create a process\n");
	fprintf(stdout,"4	Kill a process\n");
	fprintf(stdout,"5	Show memory statu\n");
	fprintf(stdout,"0	Exit\n");
	return;
}

//set the size of memory
int set_mem_size(){
	int size;
	if(flag!=0){
		fprintf(stdout,"Memory already set\n");
		return 0;
	}
	fprintf(stdout,"Memory Size=");
	fscanf(stdin,"%d",&size);
	if(size>0){
		mem_size=size;
		free_block->size=mem_size;
	}
	flag=1;
	return size;
}

//first fit
void rearrange_ff(){
	struct free_block_type *head,*p,*q,*s,*m,*h;
	h=free_block;
	m=free_block;
	head=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	head->next=NULL;
	s=head;
	p=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	p->size=h->size;
	p->start_addr=h->start_addr;
	s->next=p;
	p->next=NULL;
	h=h->next;

	while(h!=NULL){
		q=(struct free_block_type *)malloc(sizeof (struct free_block_type));
		q->size=h->size;
		q->start_addr=h->start_addr;
		h=h->next;
		head=s;
		p=head->next;
		while(head!=NULL){
			if(head->next==NULL){
				head->next=q;
				q->next=NULL;
				break;
			}else if(q->start_addr<p->start_addr){
				head->next=q;
				q->next=p;
				break;
			}else{
				head=head->next;
				p=head->next;
			}
		}
	}
	freenode(m);
	m=s;
	s=s->next;
	free(m);
	free_block=s;
}

//best fit
void rearrange_bf(){
	struct free_block_type *head,*p,*q,*s,*m,*h;
	h=free_block;
	m=free_block;
	head=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	head->next=NULL;
	s=head;
	p=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	p->size=h->size;
	p->start_addr=h->start_addr;
	s->next=p;
	p->next=NULL;
	h=h->next;

	while(h!=NULL){
		q=(struct free_block_type *)malloc(sizeof(struct free_block_type));
		q->size=h->size;
		q->start_addr=h->start_addr;
		h=h->next;
		head=s;
		p=head->next;
		while(head!=NULL){
			if(head->next==NULL){
				head->next=q;
				q->next=NULL;
				break;
			}else if(q->size<p->size){
				head->next=q;
				q->next=p;
				break;
			}else{
				head=head->next;
				p=head->next;
			}
		}
	}
	freenode(m);
	m=s;
	s=s->next;
	free(m);
	free_block=s;
}

//worst fit
void rearrange_wf(){
	struct free_block_type *head,*p,*q,*s,*m,*h;
	h=free_block;
	m=free_block;
	head=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	head->next=NULL;
	s=head;
	p=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	p->size=h->size;
	p->start_addr=h->start_addr;
	s->next=p;
	p->next=NULL;
	h=h->next;

	while(h!=NULL){
		q=(struct free_block_type *)malloc(sizeof(struct free_block_type));
		q->size=h->size;
		q->start_addr=h->start_addr;
		h=h->next;
		head=s;
		p=head->next;
		while(head!=NULL){
			if(head->next==NULL){
				head->next=q;
				q->next=NULL;
				break;
			}else if(q->size>p->size){
				head->next=q;
				q->next=p;
				break;
			}else{
				head=head->next;
				p=head->next;
			}
		}
	}
	freenode(m);
	m=s;
	s=s->next;
	free(m);
	free_block=s;
}

//rearrange memory blocks
void rearrange(int algorithm){
	switch(algorithm){
		case MA_FF:
			rearrange_ff();
			break;
		case MA_BF:
			rearrange_bf();
			break;
		case MA_WF:
			rearrange_wf();
			break;
		default:
			fprintf(stdout,"Algorithm error\n");
			break;
	}
}

//set memory rearrange algorithm
void set_algorithm(){
	int algorithm;
	fprintf(stdout,"1	First fit\n");
	fprintf(stdout,"2	Best fit\n");
	fprintf(stdout,"3	Worst fit\n");
	fscanf(stdin,"%d",&algorithm);
	if(algorithm>0&&algorithm<4){
		ma_algorithm=algorithm;
	}else{
		fprintf(stdout,"Using default algorithm %d\n",ma_algorithm);
	}
	rearrange(ma_algorithm);
}

//allocate memory
int allocate_mem(struct allocated_block *ab){
	struct free_block_type *h;
	int request_size=ab->size;
	rearrange(ma_algorithm);
	h=free_block;
	while(h!=NULL){
		if(h->size>=request_size)break;
		h=h->next;
	}
	if(h==NULL){
		fprintf(stdout,"Out of memory\n");
		return -1;
	}else{
		if(h->size-request_size<MIN_SLICE)
			h->size=0;
		else
			h->size=h->size-request_size;
		ab->start_addr=h->start_addr;
		h->start_addr=ab->start_addr+ab->size;
		fprintf(stdout,"Memory allocate succeed\n");
		return ab->size;
	}
}

struct allocated_block * find_process(int p){
	struct allocated_block *h;
	h=allocated_block_head;
	while(h!=NULL){
		if(h->pid==p)break;
		else h=h->next;
	}
	return h;
}

//free memory
int free_mem(struct allocated_block *ab){
	int algorithm=ma_algorithm;
	struct free_block_type *h,*fbt;
	h=free_block;
	fbt=(struct free_block_type *)malloc(sizeof(struct free_block_type));
	fbt->size=ab->size;
	fbt->start_addr=ab->start_addr;
	while(h->next!=NULL)
		h=h->next;
	h->next=fbt;
	fbt->next=NULL;
	rearrange_ff();
	king(free_block);
	rearrange(algorithm);
	return ab->size;
}

//release ab
int dispose(struct allocated_block *free_ab){
	struct allocated_block *pre,*ab;
	if(free_ab==allocated_block_head){
		allocated_block_head=allocated_block_head->next;
		free(free_ab);
		return free_ab->size;
	}
	pre=allocated_block_head;
	ab=allocated_block_head->next;
	while(ab!=free_ab){
		pre=ab;
		ab=ab->next;
	}
	pre->next=ab->next;
	free(ab);
	return ab->size;
}

//kill a process and deallocate it's memory
void kill_process(){
	struct allocated_block *ab;
	int p;
	fprintf(stdout,"Process id: ");
	fscanf(stdin,"%d",&p);
	ab=find_process(p);
	if(ab!=NULL){
		free_mem(ab);
		dispose(ab);
	}
}

//create new process
int new_process(){
	struct allocated_block *ab;
	int size;
	int ret;
	ab=(struct allocated_block *)malloc(sizeof(struct allocated_block));
	if(!ab)exit(-5);
	ab->next=NULL;
	pid++;
	sprintf(ab->process_name,"PROCESS-%d",pid);
	ab->pid=pid;
	fprintf(stdout,"Size of %s: ",ab->process_name);
	fscanf(stdin,"%d",&size);
	if(size>0)ab->size=size;
	ret=allocate_mem(ab);
	if(ret==ab->size){
		if(allocated_block_head==NULL){
			allocated_block_head=ab;
			return ab->pid;
		}else{
			ab->next=allocated_block_head;
			allocated_block_head=ab;
			return ab->pid;
		}
	}else if(ret==-1){
		fprintf(stdout,"Allocate failed\n");
		free(ab);
		return -1;
	}else{
		fprintf(stdout,"Unknown erro\n");
	}
	return ab->pid;
}

//show memory statu
int display_mem_usage(){
	struct free_block_type *fbt=free_block;
	struct allocated_block *ab=allocated_block_head;
	if(fbt==NULL){
		fprintf(stdout,"Out of memory\n");
		return -1;
	}
	fprintf(stdout,"Memory free\n%20s%20s\n","start addr","size");
	while(fbt!=NULL){
		if(fbt->size==0){
			fbt=fbt->next;
			continue;
		}
		fprintf(stdout,"%20d%20d\n",fbt->start_addr,fbt->size);
		fbt=fbt->next;
	}
	fprintf(stdout,"Memory allocated\n%10s%20s%10s%10s\n","pid","proc name","start addr","size");
	while(ab!=NULL){
		fprintf(stdout,"%10d%20s%10d%10d\n",ab->pid,ab->process_name,ab->start_addr,ab->size);
		ab=ab->next;
	}
	return 0;
}

int main(){
	char choice='6';
	pid=0;
	free_block=init_free_block(mem_size);
	while(1){
		display_menu();
		choice=getchar();
		while(choice>'5'||choice<'0'){
			choice=getchar();
			fprintf(stdout,"%c",choice);
		}
		switch(choice){
			case '1':
				set_mem_size();
				break;
			case '2':
				set_algorithm();
				flag=1;
				break;
			case '3':
				new_process();
				flag=1;
				break;
			case '4':
				kill_process();
				flag=1;
				break;
			case '5':
				display_mem_usage();
				flag=1;
				break;
			case '0':
				freenode(free_block);
				freenod1(allocated_block_head);
				exit(0);
				break;
			default:
				fprintf(stdout,"%d\n",choice);
				break;
		}
	}
	return 0;
}
