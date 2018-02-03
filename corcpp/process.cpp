#include<iostream>
#include<time.h>
using namespace std;
typedef struct node
{
    int data;
    struct node *next;
}List,*Listptr;
typedef struct Queue
{
	Listptr head, rear[3];
}*Queueptr;
class Process
{
private:
    Listptr s,t;
    Queueptr p;
public:
	Process()
	{
		p = (Queueptr)malloc(sizeof(Queue)); 
		p->head = (Listptr)malloc(sizeof(List));
		p->rear[0] = p->rear[1] = p->rear[2] = p->head;
		s = t = NULL; 
	}
    bool Queue_Empty();
    void Queue_Append();
    void Queue_Server();
	~Process(){ free(p->head); free(p); }
};
bool Process::Queue_Empty()
{
	return p->head == p->rear[0] && p->rear[0] == p->rear[1] && p->rear[1] == p->rear[2];
}
void Process::Queue_Append()
{
	cout << "EN QUEUE:";
	srand((unsigned)time(NULL));
	for (int i = 0; i <20; i++)
	{
		int a = 0;
		a = rand() % 5 + 1;
		s = (Listptr)malloc(sizeof(List));
		s->data = a; cout << a<<" ";
		switch (a)
		{
		case 1:
		{
				  if (p->head == p->rear[0])
				  {
					  s->next = p->rear[0]->next;
					  p->rear[0] = s;
					  p->head->next = s;
				  }
				  else
				  {
					  s->next = p->rear[0]->next;
					  p->rear[0]->next = s;
					  p->rear[0] = s;
				  }
				  break; 
		}
		case 2: case 3:
		{
					if (p->head == p->rear[1])
					{						
						s->next = p->rear[1]->next;
						p->rear[0]->next = s;
						p->rear[1] = s;
					}
					else
					{
						s->next = p->rear[1]->next;
						p->rear[1]->next = s;
						p->rear[1] = s;
					}
					break; 
		}
		case 4: case 5:
		{
					if (p->head == p->rear[2])
					{
						p->rear[1]->next = s;
						s->next = NULL;
						p->rear[2] = s;
					}
					else
					{
						s->next = p->rear[2]->next;
						p->rear[2]->next = s;
						p->rear[2] = s;
					}
					break; 
		}
		default:
			cout << "ERROR!!" << endl;
			break;
		}
	}cout << endl;
}
void Process::Queue_Server()
{
    if(Queue_Empty()) cerr<<"This Queue Is Empty!!"<<endl;
    else
    {
        cout<<"SERVER:";
        for(;p->head->next!=p->rear[2];)
		{
			s=p->head->next;cout<<s->data<<" ";
			p->head->next=s->next;
			free(s);
		}
		cout << p->rear[2]->data<<endl;
    }
}
int main()
{
    Process process;
	process.Queue_Append();
    process.Queue_Server();
    return 0;
}
