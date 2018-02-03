#include<iostream>
#include<GL/glut.h>
using namespace std;
#define screenWidth 640
#define screenHeight 640
#define INITPX 100
#define INITPY 100
void drawDot(int x,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}
void myInit(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0f,1.0f,1.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)screenWidth,0.0,(GLdouble)screenHeight);
}
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}
void myMouse(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN)
	{
		drawDot(x,screenHeight-y);
		glFlush();
	}
	else if(button==GLUT_RIGHT_BUTTON)
	{
		double value[3];
		for(int i=0;i<3;i++)
		{
			value[i]=random()/1000.0;
			int temp=(int)value[i];
			value[i]-=(double)temp;
		}
		glClearColor(value[0],value[1],value[2],0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(INITPX,INITPY);
	glutCreateWindow("button1.o");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	myInit();
	glutMainLoop();
	return 0;
}
