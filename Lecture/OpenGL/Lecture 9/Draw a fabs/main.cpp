#include <windows.h>
#include <gl/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

GLint w=400;
GLint h=400;
GLint w1=w;

void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0, 0.0, 0.0); // set the drawing color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);//the math coordinates
}
void printvp_Data()
{
//print window params
    printf("window:height=%d width=%d\n",w,h);
//print viewport params
    int VD[4];
    glGetIntegerv(GL_VIEWPORT,VD);//gets x0,y0 and width and height of the viewport
    printf("VD[0]=%d, VD[1]=%d\n",VD[0],VD[1]);
    printf("VD[2]=%d, VD[3]=%d\n",VD[2],VD[3]);
    printf("ratioVD=%f\n",(double)VD[3]/VD[2]);
}
void Draw_fun()
{
    GLdouble x;
    GLdouble step=0.1;
    GLdouble A=200;
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.0, 1.0);
    for(x = 0; x < w1 ; x +=step)
    {
        GLdouble func = A*fabs(cos(x/(40)));
         glVertex2d(x,func);
    }
                    glEnd();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glColor3f(0,0,0);
    Draw_fun();// draw the function
    printvp_Data();
    glFlush(); // send all output to display
}
void reshape(GLint width, GLint height) // what happens when the window changes
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity(); // Reset the projection matrix
    gluOrtho2D(0,width, 0, height);
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(w,h); // set window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("example 5, glutReshape/glViewport");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc (reshape); // reshape the window
    myInit();
    glutMainLoop();
    return 0;
}
