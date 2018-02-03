#include<math.h>
#include<GL/glut.h>
struct GLintPoint
{
	GLint x,y;
};
void drawDot(GLint x,GLint y)
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
	gluOrtho2D(0.0,640,0.0,640);
}
void sierpinski(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	GLintPoint T[3]={{10,10},{630,10},{300,620}};
	int index=random()%3;
	GLintPoint point=T[index];
	drawDot(point.x,point.y);
	for(int i=0;i<55000;i++)
	{
		index=random()%3;
		point.x=(point.x+T[index].x)/2;
		point.y=(point.y+T[index].y)/2;
		drawDot(point.x,point.y);
	}
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(640,640);
	glutInitWindowPosition(100,100);
	glutCreateWindow("sierpinski.o");
	glutDisplayFunc(sierpinski);
	myInit();
	glutMainLoop();
	return 0;
}
