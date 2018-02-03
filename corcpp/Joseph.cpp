#include<iostream>
using namespace std;
class Joseph
{
private:
	int *Pas,down,k;
public:
	void Start();
	int Count();
	void Show();
};
void Joseph::Start()			//初始化 
{
	Pas=new int[30];
	down=0;
	k=1;
	for(int i=0;i<30;i++)
	{
		Pas[i]=i+1;
	}
}
int Joseph::Count()
{
	int i=0;
	for(i=0;i<30;i++)
	{
		if(Pas[i]==0)					//如果乘客序号为0，则计数减1 
		{k--;}
		else if(k==9&&Pas[i]!=0)		//遇到报9的乘客将其删除（赋值为零） 
		{
			Pas[i]=0;
			k=1;
			down++;						//被删除计数加1 
			if(down==15)	break;		//删除人数达到15人时跳出循环 
		}
		else	k++;
	}
	if(down==15);						//删除人数达到要求则不进行任何操作 
	else Count();						//递归调用 
}
void Joseph::Show()
{
	cout<<"被扔下大海的人是:";
	for(int i=0;i<30;i++)
	{
		if(Pas[i]==0)
		{
			cout<<"  "<<i+1;
		}
	}
	delete Pas;
	cout<<endl;
}
int main()
{
	Joseph joseph;
	joseph.Start();
	joseph.Count();
	joseph.Show();
	return 0;
}
