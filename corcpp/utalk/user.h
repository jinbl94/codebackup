/***************************************************************************
 * user.h
 * this is the declar of usernode
 */
#include <time.h>
#include <malloc.h>
struct user_node{
	usernode * next;
	char * name;
	struct sockaddr_in addr;
	time_t time;
}User,*UserPtr;
UserPtr usertable=(UserPtr)malloc(sizeof(User));
int size=0;
void initTable(){
	usertable->next=null;
	usertable->name=null;
	usertable->addr=null;
	usertable->time=null;
}
void addUser(UserPtr userptr){
	UserPtr first=usertable,
			second=usertable->next;
	//insert 'usertptr' into the list
	for(;(second!=null)&&(second->name!=userptr->name);){
		first=second;
		second=second->next;
	}
	if(second==null){
		userptr->next=usertable->next;
		usertable->next=userptr;
		size++;
	}else{
		second->addr=userptr->addr;
		second->time=userptr->time;
	}
}
void delUser(char *name){
	UserPtr first=usertable,
			second=usertable->next;
	//look for the user who's name if 'name'
	for(;(second!=null)&&(second->name!=name);){
		first=second;
		second=second->next;
	}
	if(second==null){
		//user not found, maybe he logged out.
	}else{
		//adjust the list and free the memory of this node.
		first->next=second->next;
		free(second);
		size--;
	}
}
void destroy(void){
	UserPtr temp;
	while(usertable->next!=null){
		temp=usertable;
		usertable=usertable->next;
		free(temp);
	}
}
