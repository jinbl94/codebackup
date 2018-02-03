#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct Member
{
	string name;
	string phone1,phone2,phone3;
};
class PhoneBook
{
private:
	Member member[200];
public:
	PhoneBook()
	{
		for(int i=0;i<200;i++)
			member[i].name="ZZZZ";
	}
	~PhoneBook()
	{
		cout<<"感谢使用!"<<endl;
	}
	void Start();
	void Show();
	int Finm();
	void Addm();
	int Delm();
	int Edim();
	void Check();
	void End();
};
//开始界面
void PhoneBook::Start()
{
	int i=0,l=0;
	cout<<"*****************************"<<endl<<
	"0.显示全部联系人"<<endl<<"1.查找联系人(默认按姓名查找)"<<endl<<
	"2.添加联系人"<<endl<<"3.删除联系人"<<endl<<"4.编辑联系人"<<endl<<
	"5.检查重复并排序(默认按姓名排序)"<<endl<<"6.退出"<<endl;
	ifstream a("d:\\phonenumber.txt");
	if(!a)
	{
		cerr<<"wrong!"<<endl;
		exit(1);
    }
	for(;!a.eof();i++)
	{
		a>>member[i].name>>member[i].phone1>>member[i].phone2>>member[i].phone3;
	}
	a.close();
}
//显示所有联系人
void PhoneBook::Show()
{
	int i=0;
	cout<<"姓名"<<'\t'<<"电话1"<<'\t'<<"电话2"<<'\t'<<"电话3"<<endl;
	for(;i<200;i++)
	{
		if(member[i].name!="ZZZZ")
			cout<<member[i].name<<'\t'<<member[i].phone1<<'\t'<<member[i].phone2<<'\t'<<member[i].phone3<<endl;
	}
}
//查找联系人
int PhoneBook::Finm()
{
	char in[20],choi='0';
	int i=0;
	cout<<"请输入查询方式(0.按姓名	1.按号码1):";
	if(choi=='1')
	{
		cout<<"请输入号码:";
		cin>>in;
		for(;member[i].phone1!=in&&i<199;i++);
	}
	else
	{
		cout<<"请输入姓名:";
		cin>>in;
		for(;member[i].name!=in&&i<199;i++);
	}
	
	if(member[i].name=="ZZZZ")
	{
		cout<<"无此联系人！"<<endl;
	}
	else
	{
		cout<<"姓名"<<'\t'<<"电话1"<<'\t'<<"电话2"<<'\t'<<"电话3"<<endl;
		cout<<member[i].name<<'\t'<<member[i].phone1<<'\t'<<member[i].phone2<<'\t'<<member[i].phone3<<endl;
	}
	return 0;
}
//添加联系人
void PhoneBook::Addm()
{
	int i=0;
	char ch='y';
	for(;member[i].name!="ZZZZ";i++);
	for(;ch!='n';i++)
	{
		cout<<"联系人"<<i<<":"<<"姓名:";
		cin>>member[i].name;
		cout<<"号码1:";
		cin>>member[i].phone1;
		cout<<"号码2:(没有请输入0)";
		cin>>member[i].phone2;
		cout<<"号码3:(没有请输入0)";
		cin>>member[i].phone3;
		cout<<"继续添加?(y/n)";
		cin>>ch;
	}
}
//删除联系人
int PhoneBook::Delm()
{
	char in[20],ch='y';
	int i=0;
	for(;ch!='n';)
	{
		cout<<"请输入要删除的联系人姓名:";
		cin>>in;
		for(i;member[i].name!=in;i++);
		if(member[i].name=="ZZZZ")
		{
			cout<<"无此联系人！";
		}
		else
			for(;member[i].name!="ZZZZ";i++)
			{
				member[i]=member[i+1];
			}
		cout<<"继续删除?(y/n)";
		cin>>ch;
	}
	return 0;
}
//编辑联系人
int PhoneBook::Edim()
{

	char in[20],j='0',ch1='y',ch2='y';
	int i=0;
	for(;ch1!='n';)
	{
		cout<<"请输入要编辑的联系人姓名:";
		cin>>in;
		for(;member[i].name!=in&&i<200;i++);
		if(member[i].name=="ZZZZ")
		{
			cout<<"无此联系人！请重新输入:";
			cin>>in;
		}
		else
		{
			for(;ch2!='n';)
			{
				cout<<member[i].name<<'\t'<<member[i].phone1<<'\t'<<member[i].phone2<<'\t'<<member[i].phone3<<endl;
				cout<<"0.姓名"<<endl<<"1.号码1"<<endl<<"2.号码2"<<endl<<"3.号码3"<<
				endl<<"请输入要修改的项目所对应序号："<<endl;
				cin>>j;
				for(;j<'0'||j>'3';)
				{
					cout<<"请重新输入!"<<endl;
					cin>>j;
				}
				switch(j)
				{
				case '0':
					cout<<"请输入修改后内容:";
					cin>>member[i].name;
					break;
				case '1':
					cout<<"请输入修改后内容:";
					cin>>member[i].phone1;
					break;
				case '2':
					cout<<"请输入修改后内容:";
					cin>>member[i].phone2;
					break;
				case '3':
					cout<<"请输入修改后内容:";
					cin>>member[i].phone3;
					break;
				}
				cout<<"继续修改此联系人?(y/n)";
				cin>>ch2;
			}
			
		}
		cout<<"继续修改其他联系人?(y/n)";
		cin>>ch1;
	}
	return 0;
}
//检查重复号码、排序
void PhoneBook::Check()
{
	char choi='0';
	int i=0,j=0,l=0;
	Member temp;
	for(;member[l].name!="ZZZZ";l++);
	for(;member[i].name!="ZZZZ";i++)
	{
		cout<<"here"<<i<<endl;
		if(member[i].phone1==member[i].phone2)
			member[i].phone2="0";
		if(member[i].phone1==member[i].phone3)
			member[i].phone3="0";
		if(member[i].phone2==member[i].phone3)
			member[i].phone3="0";
		for(j=i+1;j<l;j++)
		{
			if(member[1].phone1!="0")
			{
				if(member[1].phone1==member[2].phone1)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone1<<endl;
				if(member[i].phone1==member[j].phone2)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone1<<endl;
				if(member[i].phone1==member[j].phone3)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone1<<endl;
			}
			if(member[2].phone1!="0")
			{
				if(member[i].phone2==member[j].phone1)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone2<<endl;
				if(member[i].phone2==member[j].phone2)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone2<<endl;
				if(member[i].phone2==member[j].phone3)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone2<<endl;
			}
			if(member[3].phone1!="0")
			{
				if(member[i].phone3==member[j].phone1)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone3<<endl;
				if(member[i].phone3==member[j].phone2)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone3<<endl;
				if(member[i].phone3==member[j].phone3)
					cout<<member[i].name<<"和"<<member[j].name<<"的号码重复！请修正！"<<endl<<"重复号码："<<member[i].phone3<<endl;

			}
		}
	}
	cout<<"请选择排序方式:(0.按姓名	1.按号码1)";
	cin>>choi;
	if(choi=='1')
	{
		for(i=0;member[i].name!="ZZZZ";i++)
		{
			for(j=l-1;j>i;j--)
			{
				if(member[i].phone1>member[j].phone1)
				{
					temp=member[i];member[i]=member[j];member[j]=temp;
				}
			}
		}
	}
	else
	{
		for(i=0;member[i].name!="ZZZZ";i++)
		{
			for(j=l-1;j>i;j--)
			{
				if(member[i].name>member[j].name)
				{
					temp=member[i];member[i]=member[j];member[j]=temp;
				}
			}
		}
	}
}
//存储
void PhoneBook::End()
{
	int i=0;
	fstream a("d:\\phonenumber.txt", ios::out);
	if(!a)
	{
		cerr<<"wrong!"<<endl;
		exit(1);
	}
	for(;member[i].name!="ZZZZ";i++)
	{
		a<<member[i].name<<'\t'<<member[i].phone1<<'\t'<<member[i].phone2<<'\t'<<member[i].phone3<<endl;
	}
	a.close();
}
int main()
{
	PhoneBook phonebook;
	char a='0',c='n';
	phonebook.End();
	for(;c!='y';)
	{
		phonebook.Start();
		cout<<"*****************************"<<endl<<"请输入操作所对应序号:";
		//0.显示全部联系人 1.查找联系人(默认姓名查找) 2.添加联系人
		//3.删除联系人 4.编辑联系人 5.检查重复并排序(默认姓名排序) 6.退出 
		cin>>a;
		cout<<"*****************************"<<endl;
		for(;a<'0'||a>'6';)
		{
			cout<<"请重新输入!"<<endl;
			cin>>a;
		}
		switch(a)
		{
		case '0':
			phonebook.Show();
			break;
		case '1':
			phonebook.Finm();
			break;
		case '2':
			phonebook.Addm();
			break;
		case '3':
			phonebook.Delm();
			break;
		case '4':
			phonebook.Edim();
			break;
		case '5':
			phonebook.Check();
			break;
		case '6':
			cout<<"退出?(y/n)";
			cin>>c;
		}
		phonebook.End();
	}
	return 0;
}
