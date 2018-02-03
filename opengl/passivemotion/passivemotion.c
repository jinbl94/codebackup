#include<GL/glut.h>
using namespace std;
#define screenWidth 640
#define screenHeight 640
#define INITPX 100
#define INITPY 100
struct Dot
{
	int x,y;
};
Dot corner[2];
bool selected=false;
/*void drawDot(int x,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
}*/
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0f,1.0f,1.0f);
	glPointSize(1.0);
	if(selected)
	{
		glBegin(GL_QUADS);
		glVertex2i(corner[0].x,corner[0].y);
		glVertex2i(corner[0].x,corner[1].y);
		glVertex2i(corner[1].x,corner[1].y);
		glVertex2i(corner[1].x,corner[0].y);
		glEnd();
	}
	glutSwapBuffers();
}
void myMouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON&&state==GLUT_DOWN)
	{
		corner[0].x=x;
		corner[0].y=screenHeight-y;
		selected=true;
	}
	glutPostRedisplay();
}
void myPassiveMotion(int x,int y)
{
	corner[1].x=x;
	corner[1].y=screenHeight-y;
	glutPostRedisplay();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(INITPX,INITPY);
	glutCreateWindow("test.o");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,screenWidth,0.0,screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0,0.0,0.0,0.0);
	glViewport(0,0,screenWidth,screenHeight);
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutPassiveMotionFunc(myPassiveMotion);
	glutMainLoop();
	return 0;
}
