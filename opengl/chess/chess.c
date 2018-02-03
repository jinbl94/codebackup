#include<math.h>
#include<GL/glut.h>
#define screenWidth 640
#define screenHeight 640
#define INITPX 100
#define INITPY 100
GLdouble STEPX=screenWidth/8.0;
GLdouble STEPY=screenHeight/8.0;
struct Point
{
	GLdouble x1,y1,x2,y2;
};
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
	double r=1.0,g=1.0,b=0.0;
	Point point={0,0,STEPX,STEPY};
	glClear(GL_COLOR_BUFFER_BIT);
	for(int i=1;point.y2<=screenHeight;i++)
	{
		if(i%2==1){point.x1=STEPX;point.x2=2*STEPX;}
		for(;point.x2<=screenWidth;)
		{
			glColor3f(r,g,b);
			glRecti(point.x1,point.y1,point.x2,point.y2);
			point.x1+=2*STEPX;
			point.x2+=2*STEPX;
			r-=1.0/16;
			if(i<5)g-=1.0/8;
			else g+=1.0/8;
			b+=1.0/16;
		}
		point.x1=0;
		point.x2=STEPX;
		point.y1+=STEPY;
		point.y2+=STEPY;
	}
	glFlush();
}
int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(screenWidth,screenHeight);
	glutInitWindowPosition(INITPX,INITPY);
	glutCreateWindow("chess.o");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();
	return 0;
}
