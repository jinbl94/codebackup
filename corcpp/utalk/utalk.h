/***************************************************************************
 * utalk.h
 * head file of utalk
 */

struct usernode{
	node * next;
	char * name;
	struct sockaddr_in addr;
	bool status;
}user,*userptr;

//message node
struct msgnode{
	char * head;
	time_t time;
	char * content;
	char * from;
}message,*messageptr;
