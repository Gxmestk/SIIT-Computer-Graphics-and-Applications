#include <windows.h>
#include <math.h>
#include <gl/glut.h>
#include <stdio.h>
const int w = 600; // width of screen window in pixels
const int h = 400; // height of screen window in pixels
int maxVp[2];
int Vp[4];
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // background color is white
    glColor3f(1.0, 0.0, 0.0); // drawing color is black
    glPointSize(2.0); // a 'dot' is 2 by 2 pixels
    glMatrixMode(GL_PROJECTION); // set "camera shape"
    glLoadIdentity();
    gluOrtho2D(0.0,4.0,-1.0,1.0);
}
void Draw_fun()
{
    GLfloat x;
    glBegin(GL_POINTS);
    for(x = 0; x <= 4.0 ; x += 0.005)
    {
        GLdouble func = exp(-x) * cos(2 * M_PI* x);
        glVertex2f(x,func);
    }
    glEnd();
    glFlush();
}
void printvp_Data()
{
    printf("viewport 2\n");
    glGetIntegerv(GL_MAX_VIEWPORT_DIMS,maxVp);
    printf("w=%d,h=%d ",maxVp[0],maxVp[1]);
    glGetIntegerv(GL_VIEWPORT,Vp);
    printf("x=%d,y=%d, w=%d, h=%d\n",Vp[0],Vp[1],Vp[2],Vp[3]);
}
void myDisplay(void)
{
    GLdouble x;
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glViewport(0,0,w,h/2); // plot the function in the 1-st viewport
    printvp_Data();
    glColor3f(1.0, 0.0, 0.0);// red
    Draw_fun();
    glViewport(0,h/2,w,h/2);// plot the function in the 2-d viewport
    printvp_Data();
    glColor3f(0.0, 0.0, 1.0);
    Draw_fun();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(w, h); // set window size
    glutInitWindowPosition(0, 0); // set window position on screen
    glutCreateWindow("Example 2 Viewports"); // open the screen window
    myInit();
    glutDisplayFunc(myDisplay); // register redraw function
    glutMainLoop(); // go into a perpetual loop
    return 0;
}
