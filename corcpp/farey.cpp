#include<iostream>
#include<malloc.h>
using namespace std;
typedef struct sect
{
	double price;
	int n1,n2;
	struct sect *prior,*next;
}node;
class Farey
{
private:
	double max;
	node *temp,*head,*p,*s;
public:
	void get_max();
	void set_list();
	void sort_list();
	void show_list();
	int chek(int b,int a);
	~Farey()
	{
		p=head;
		for(;p!=NULL;)
		{
			temp=p->next;
			free(p);
			p=temp;
		}
		free(head);
	}
};
int Farey::chek(int b,int a)
{
	int t;
	for(;b!=0;)
	{
		t=a%b;a=b;b=t;
	}
	return a;
}
void Farey::get_max()
{
	cout<<"Please input the value of max:";
	cin>>max;
}
void Farey::set_list()
{
	double i,j;
	int ch;
	head=(node *)malloc(sizeof(node));			//ÉêÇëÍ·½áµã
	p=head;
	p->price=0;
	for(i=max;i>=1;i--)							//Ë³ÐòÌî³ä 
	{
		for(j=1;j<i;j++)
		{
			ch=chek((int)j,(int)i);
			if(ch==1)
			{
				s=(node *)malloc(sizeof(node));
				s->price=j/i;
				s->n1=(int)j;s->n2=(int)i;
				s->next=NULL;
				p->next=s;
				p=s;	
			}
		}
	}
}
void Farey::sort_list()						//ÔªËØÅÅÐò 
{
	double t1;
	int t2;
	p=head;
	for(;p!=NULL;p=p->next)
	{
		for(s=p->next;s!=NULL;s=s->next)
		{
			if(p->price>s->price)
			{
				t1=p->price;p->price=s->price;s->price=t1;
				t2=p->n1;p->n1=s->n1;s->n1=t2;
				t2=p->n2;p->n2=s->n2;s->n2=t2;
			}
		}
	}
}
void Farey::show_list()
{
	cout<<"0"<<'\t';
	p=head->next;
	for(;p!=NULL;p=p->next)cout<<p->n1<<"/"<<p->n2<<'\t';
	cout<<"1"<<endl;
}
int main()
{
	Farey farey;
	farey.get_max();
	farey.set_list();
	farey.sort_list();
	farey.show_list();
	return 0;
}
