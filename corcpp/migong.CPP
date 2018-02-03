#include <iostream>
#include <cstdio>
#include <fstream>
#include <time.h>
#include<stdlib.h>
using namespace std;
int tu[52][52];                //二维数组存储迷宫地图 
int flag[52][52];             //标记数组 ，防止迷宫内的绕圈 
int hang,lie;
int tu2[52][52];
int bx,by,ex,ey;             //分别为 起点的xy坐标和终点的xy坐标 
                             //以上为全局变量 
struct node
{
   int x,y,p;               //栈 ，分别为某点坐标 ，和该点在栈的位置 
}stack[3000];
int len=0;
int dx[4]={1,0,0,-1};       
int dy[4]={0,1,-1,0};      //dx和dy为两个增量数组，分别为某点的探索方向 如0,1表示向下探索 
void daying()
{
	int now=len-1;          //取栈顶元素 
	for (int j=0;j<hang+2;j++)
		for (int k=0;k<lie+2;k++)
		 	tu2[j][k]=tu[j][k];           //复制地图 
	while (now!=-1){
		tu2[stack[now].x][stack[now].y]=2;
		now=stack[now].p;                //将栈中的所有通路点用2标记，以便打出通路地图 
	}
	for (int j=1;j<hang+1;j++){
		for (int k=1;k<lie+1;k++){
			if (tu2[j][k]==0) cout<<"□";
			if (tu2[j][k]==1) cout<<"■";
			if (tu2[j][k]==2) cout<<"☆";
		}
		cout<<endl;
	}
}
void find()
{
	len=0;              //栈的元素个数 
	node be;             
	be.x=bx;
	be.y=by;
	be.p=-1;              //
	stack[len]=be;           //将起点入栈 
	len++;
	for (int j=0;j<hang+2;j++)
		for(int k=0;k<lie+2;k++)
			flag[j][k]=0;           //每次找通路时将所有标记点清为0 
	flag[bx][by]=1;
	while (len>0){		
		node now=stack[len-1];
		int g=len-1;
		bool b=true; 
		for (int j=0;j<4;j++){
			if (tu[now.x+dx[j]][now.y+dy[j]]==1) continue;        //若该方向为死路 ，则continue 
			if (flag[now.x+dx[j]][now.y+dy[j]]==1) continue;	//若该点走过，则continue		 
			node next;                                       //若可以走，则入栈 
			next.x=now.x+dx[j];
			next.y=now.y+dy[j];                     
			next.p=g;                                   //记录该点的前一个点在栈中位置 
			stack[len++]=next;
			flag[next.x][next.y]=1;
			b=false;
			if (next.x==ex&&next.y==ey){
				daying();                                //若已走到终点 ，则打印地图通路 
				return;
			}                                           
		}
		if (b) len--;                                    //若是死路，则清除出栈 
	}
	cout<<"no exit"<<endl;
}
void shuchu()
{
	for (int j=1;j<hang+1;j++){
		for (int k=1;k<lie+1;k++){
			if(tu[j][k] == 1) cout << "■"; else cout << "□";   //打印地图 
		}
		cout<<endl;
	}
	cout<<endl;
}
void duru()                                         //手动生成地图时，读入文件的迷宫数据 
{
	fstream afile;
	afile.open("d:\\in.txt",ios::in);                  //使用fstream流来读取文件中数据 
	afile>>lie>>hang;
	afile>>bx>>by>>ex>>ey;
	for (int j=1;j<hang+1;j++)
		for (int k=1;k<lie+1;k++)                    
			afile>>tu[j][k];
	for (int j=0;j<hang+2;j++) {
		tu[j][0]=1;                                  //将地图最外围再加一层死路，以便使每个点都有四个方向探索 
		tu[j][lie+1]=1;
	}	
	for (int k=0;k<lie+2;k++){
		tu[0][k]=1;                                   //同上 
		tu[hang+1][k]=1;
	}
}

int start[200][2],endd[200][2];                       //多入口多出口时 将文件中的起点和终点存入这两个二维数组中 
int slen,elen;
void duru2()                                // 读入文件中的数据 
{
	fstream afile;
	afile.open("d:\\in.txt",ios::in);
	afile>>lie>>hang;                //迷宫长和宽 
	afile>>slen;                                   //入口个数 
	for (int j=0;j<slen;j++) afile>>start[j][0]>>start[j][1];
	afile>>elen;                        //出口个数 
	for (int j=0;j<elen;j++) afile>>endd[j][0]>>endd[j][1];
	for (int j=1;j<hang+1;j++)
		for (int k=1;k<lie+1;k++)
			afile>>tu[j][k];
	for (int j=0;j<hang+2;j++) {
		tu[j][0]=1;               //最外层加一层 
		tu[j][lie+1]=1;
	}	 
	for (int k=0;k<lie+2;k++){
		tu[0][k]=1;
		tu[hang+1][k]=1;
	}
}

int main() {
	int g;
	 while(1){
		system("cls");               //清空屏幕上已经显示的内容 
		cout<<"************************************************************"<<endl;
		cout<<"￥￥￥￥￥            迷           宫             ￥￥￥￥￥"<<endl; 
		cout<<"************************************************************"<<endl;
		cout<<"************************************************************"<<endl;
		cout<<"&&&&&&&&&&             操作类型                &&&&&&&&&&&&&"<<endl;
		cout<<"**********                                     *************"<<endl;    //主界面 
	    cout<<"**********    1.手动生成地图（从文件中读入）   *************"<<endl;   
	    cout<<"**********                                     *************"<<endl;
	    cout<<"**********    2.多入口多出口（从文件中读入）   *************"<<endl;
	    cout<<"**********                                     *************"<<endl;
	    cout<<"**********    3.自动生成地图                   *************"<<endl;
	    cout<<"************************************************************"<<endl<<endl<<endl<<endl;
	    cout<<"************************************************************"<<endl;
	    cout<<"请选择相应操作序号：";
     	cin>>g;
     	system("cls"); 
	if (g==1){
		duru();
		shuchu();
		find();
		system("pause");
	}else if (g==2){
		duru2();
		shuchu();
		for (int j=0;j<slen;j++){
			for (int k=0;k<elen;k++){
				bx=start[j][0];
				by=start[j][1];                                   //使用二重循环找到每个入口到每个出口的路径 
				ex=endd[k][0];
				ey=endd[k][1];
				cout<<"from ("<<bx<<','<<by<<")to ("<<ex<<','<<ey<<')'<<endl;
				find();
			}
		}system("pause");
	}else if (g==3){
		cout<<"请输入迷宫长和宽" <<endl; 
		cin>>hang>>lie;
		srand((unsigned)time(NULL));               
		for (int j=1;j<=hang;j++)
			for (int k=1;k<=lie;k++)
			 	tu[j][k]=rand()%2;             //随机函数 ，使得二维数组的每一个元素为0或1 
		for (int j=0;j<hang+2;j++) {
			tu[j][0]=1;
			tu[j][lie+1]=1;
		}	
		for (int k=0;k<lie+2;k++){
			tu[0][k]=1;
			tu[hang+1][k]=1;
		}
		shuchu();
		bx=by=1;
		ex=hang;ey=lie;
		find();
		system("pause");
	}
	} 
	return 0;
}
