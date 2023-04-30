#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
int winWidth = 400, winHeight = 400;//initial size of the window
float r=0., g=1., b=1.;
void MyInit(void)
{
    glClearColor(1,1,1,0.0);//set up an RGB background color
    glClear (GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // initialize some viewing values
    glLoadIdentity(); // initialize some viewing values
    gluOrtho2D(-1, 1, -1, 1);//the coordinates
}
void Plot_Quad()
{
    glBegin(GL_QUADS); // Each set of 4 vertices form a quad
    glColor3f(r, g, b); // Red
    glVertex2f(-0.8, 0.1); // Define vertices in counter-clockwise (CCW) order
    glVertex2f(-0.2, 0.1); // so that the normal (front-face) is facing you
    glVertex2f(-0.2, 0.7);
    glVertex2f(-0.8, 0.7);
    glEnd();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    Plot_Quad();
    glFlush(); // send all output to display
}
void mouse(GLint button, GLint state, GLint x, GLint y)
{
    if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN)
    {
        g=1-g;
        r=1-r;
        myDisplay();
    }

}
int main(int argc, char** argv)
{
    glutInit(&argc,argv); //initialize OpenGL
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); //setup a specific display mode
    glutInitWindowPosition(50,50); //setup a window position
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow("example 8"); //Open the OpenGL window
    MyInit();
    glutDisplayFunc(myDisplay);//call the display function
    glutMouseFunc(mouse);//call the mouse function
    glutMainLoop(); //activate the graphics output above
}
