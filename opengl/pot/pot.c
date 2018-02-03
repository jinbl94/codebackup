#include <GL/glut.h>

void init(void){
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5,5,-5,5,5,15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,10,0,0,0,0,1,0);
    return;
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.5,1,1);
    glutWireTeapot(2.7);
    glFlush();
    return;
}

int main(int argc,char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(640,640);
    glutCreateWindow("pot.o");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
