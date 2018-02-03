#include<iostream>
#include<fstream>
#include<GL/glut.h>
#define ScreenHeight 640.0
#define ScreenWidth 640.0
#define Max 640
#define pointNumber 50
using namespace std;
struct Dot
{
	int x;
	int y;
};
void Points(void)
{
	Dot temp;
	fstream myfile;
	myfile.open("./stars.dat",ios::out|ios::trunc);
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
}
void myInit(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0f,1.0f,1.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,ScreenWidth,0.0,ScreenHeight);
}
void myDisplay(void)
{
	Points();
	Dot dot;
	fstream myfile;
	myfile.open("./stars.dat",ios::in);
	if(!myfile)
	{
		cerr<<"open file stars.dat failed!!"<<endl;
		exit(1);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i=0;!myfile.eof();i++)
	{
		myfile>>dot.x>>dot.y;
		glBegin(GL_POINTS);
			glVertex2i(dot.x,dot.y);
		glEnd();
	}
	myfile.close();
	glFlush();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,150);
	glutCreateWindow("stars.o");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
