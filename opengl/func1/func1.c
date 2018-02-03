#include<math.h>
#include<GL/glut.h>
#define screenWidth 640
#define screenHeight 640
#define INITPX 100
#define INITPY 100
#define PI 3.14159265
GLdouble A,B,C,D;
void myInit(void)
{
	glClearColor(0.0,0.0,0.0,0.0);
	glColor3f(1.0f,1.0f,1.0f);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)screenWidth,0.0,(GLdouble)screenHeight);
	A=screenWidth/4.0;
	B=0.0;
	C=D=screenHeight/2.0;
}
void myDisplay(void)
{
	GLdouble x=0;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for(;x<4.0;x+=0.005)
	{
		GLdouble func=exp(-x)*(cos(2*PI*x));
		glVertex2d(A*x+B,C*func+D);
	}
	glEnd();
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(INITPX,INITPY);
	glutCreateWindow("func1.o");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
