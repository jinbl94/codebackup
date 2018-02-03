#include<iostream>
using namespace std;
#define NUM 4
long modExpFun(long a,long e,long m)
{
	long int p;   
	long int tmpbase, r=0;
	int k = 0x40000000;
	if(a<0||e<0||m<0){
		r=-1;
		return r;
	}
	else if(m==0){
		r=-2;
		return r;
	}
	else if(m==1){
		r=0;
		return r;
	}
	else if(a==0&&m!=0){
		r=0;
		return r;
	}
	else if(e==0&&a!=0){
		r=1;
		return r;
	}
	else{
		p=a%m;
		tmpbase=p;
		r=p;
		for(;(k&e)==0;k>>=1);
		k>>=1;
		for(;k!=0;k>>=1){
			r=(r*r)%m;
			if((k&e)!=0)
				r=(r*tmpbase)%m;
		}
		return r;
	}
	return r;
}
int main(int argc,char* argv[]){
	long int ar[NUM][3]={
		2,-1,3,
		2,4,0,
		2,5,12,
		2,1234,789};
	long int a,e,m,res;
	for(int i=0;i<NUM;i++){
		a=ar[i][0],e=ar[i][1],m=ar[i][2];
		res=modExpFun(a,e,m);
		cout<<a<<"^"<<e<<" mod "<<m<<"="<<res<<endl;
	}
	return res;
}
