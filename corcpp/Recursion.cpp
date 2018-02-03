#include<iostream>
#include<string>
using namespace std;
typedef struct Node
{
	int data;
	struct Node *prior,*next;
}node;
class A
{
private:
	node *head,*p,*s;
public:
	A()
	{
		head=(node *)malloc(sizeof(node));
		head->next=NULL;
		p=head;
		for(int i=0;i<20;i++)
		{
			s=(node *)malloc(sizeof(node));
			s->data=5*i;s->prior=p;s->next=NULL;
			p->next=s;p=s;
		}
		p=head->next;
	}
	void show();
	void add(int temp);
	void dele(int temp);
	int search(int temp);
	~A()
	{
		for(;p!=NULL;)
		{
			s=p;free(p);p=s->next;
		}
		free(head);free(s);
	}
};
void A::add(int temp)
{
    s=(node *)malloc(sizeof(node));
    s->data=temp;s->next=p;s->prior=head;
    p->prior=s;head->next=s;
    free(s);p=head->next;
    cout<<"After added:"<<endl;
    show();
    cout<<endl;
}
void A::show()
{
	if(p!=NULL)
	{
		cout<<p->data<<'\t';
		p=p->next;
		show();
	}
	else p=head->next;
}
int A::search(int temp)
{
	if(p->data!=temp&&p->next!=NULL)
	{
		p=p->next;search(temp);
	}
	return p->data;
}
void A::dele(int temp)
{
    cout<<"Delete "<<temp<<" :";
    p=head->next;
    for(;p->data!=temp&&p->next!=NULL;)p=p->next;
    if(p->data!=temp)cout<<"No such a number in this series!";
    else
    {
        p->prior->next=p->next;p->next->prior=p->prior;
        free(p);
        cout<<"Deleted successfully!";
    }
    p=head->next;
    cout<<endl;
}
int main()
{
	A a;int temp,i;
	a.show();a.add(19);                                //添加
	for(i=0;i<2;i++)                                              //查找表中的元素
    {
        temp=a.search(50+i);
        cout<<"Search "<<50+i<<" :";
        if(temp==50+i)cout<<"Find it!"<<endl;
        else cout<<"No such data!"<<endl;
    }
    for(i=0;i<2;i++){a.dele(75+i);a.show();}                    //删除操作
	return 0;
}
