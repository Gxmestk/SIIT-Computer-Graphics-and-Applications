#include <windows.h>
#include <gl/glut.h>
#include <stdio.h>
#include <math.h>
GLint w=400;
GLint h=400;
void init(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(3);
    glFlush(); // send all output to display
}
void Draw_fun()
{
    GLdouble x;
    GLdouble step=0.001*w;
    GLdouble A=0.49*h;
    glBegin(GL_LINE_STRIP);
    for(x = 0; x < w ; x +=step)
    {
        GLdouble func = A*fabs(cos(x/(0.1*w)));
        glVertex2d(x,func);
    }
    glEnd();
}
void my_Display()
{
    Draw_fun();
    glFlush();
}
void Viewport1(GLint width, GLint height)
{
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset the projection matrix
    glViewport(0, 0, width, height/2);
    gluOrtho2D(0,width, 0, height/2);
}
void Viewport2(GLint width, GLint height)
{
    glViewport(0, height/2, width, height/2);
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluOrtho2D(0,width, 0, height/2);
}
void reshape(GLint width, GLint height)
{
    w=width;
    h=height; //reshape passes the parameters to the main
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    Viewport1(width,height);
    glColor3f(1,0,0);
    my_Display();
    Viewport2(width,height);
    glColor3f(0.9,0.9,0.9);
    glRectf(0,0,width,height/2);
    glColor3f(0,0,1);
    my_Display();
    glFlush();
}
void Do_Nothing(void)
{
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w,h); // set window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("example 6, two viewports");
    init();
    glutDisplayFunc(Do_Nothing);
    glutReshapeFunc (reshape); // reshape the window
    glutMainLoop();
    return 0;
}
