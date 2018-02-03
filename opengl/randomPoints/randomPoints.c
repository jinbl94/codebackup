#include<iostream>
#include<fstream>
#include<math.h>
#include<GL/glut.h>
using namespace std;
#define Max 640
#define pointNumber 10
int main()
{
	fstream myfile;
	myfile.open("./points.dat",ios::out|ios::trunc);
	if(!myfile)
	{
		cerr<<"WARNING: open points.dat failed!"<<endl;
		exit(1);
	}
	GLdouble x,y;
	for(int i=0;i<pointNumber;i++)
	{
		x=(GLdouble)(random()%Max);
		y=(GLdouble)(random()%Max);
		myfile<<x<<" "<<y<<endl;
	}
	myfile.close();
	return 0;
}
