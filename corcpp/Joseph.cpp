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
void Joseph::Start()			//��ʼ�� 
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
		if(Pas[i]==0)					//����˿����Ϊ0���������1 
		{k--;}
		else if(k==9&&Pas[i]!=0)		//������9�ĳ˿ͽ���ɾ������ֵΪ�㣩 
		{
			Pas[i]=0;
			k=1;
			down++;						//��ɾ��������1 
			if(down==15)	break;		//ɾ�������ﵽ15��ʱ����ѭ�� 
		}
		else	k++;
	}
	if(down==15);						//ɾ�������ﵽҪ���򲻽����κβ��� 
	else Count();						//�ݹ���� 
}
void Joseph::Show()
{
	cout<<"�����´󺣵�����:";
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
