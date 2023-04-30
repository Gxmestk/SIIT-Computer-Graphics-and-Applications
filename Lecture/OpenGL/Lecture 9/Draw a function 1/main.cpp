#include <windows.h>
#include <GL/glut.h>
int winWidth = 400, winHeight = 400;//initial size of the window

void MyInit(void)
{
    glMatrixMode(GL_PROJECTION); // initialize the projection matrix
    glLoadIdentity(); // the projection matrix=identity
    gluOrtho2D(-2.0,2,0.0,1); // initialize the math coordinates
    glClearColor(1.0,1.0,1.0,0.0); // background color is white
    glColor3f(1.0, 0.0, 0.0); // drawing color is red
}
GLfloat f(GLfloat x) //the function
{
    return x*x;
}
void DrawFunction(void)
{
    GLfloat x, dx,fx;
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    dx=0.01;//step along x
    glBegin(GL_POINTS); // draw f(x)
    for (x = -1; x < 1.0 ; x+=dx)
    {
        fx=f(x);
        glVertex2f(x,fx);
    }
    glEnd();
    glFlush();//send to the screen
}
int main(int argc, char** argv)
{
    glutInit(&argc,argv); //initialize OpenGL
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); //setup a specific display mode
    glutInitWindowPosition(50,50); //setup a window position
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("the first window");//Open the OpenGL window
    MyInit();
    glutDisplayFunc(DrawFunction); //call the display function
    glutMainLoop(); //the openGL loop
    return 0;
}
