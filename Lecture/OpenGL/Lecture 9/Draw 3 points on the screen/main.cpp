#include <windows.h>
#include <gl/glut.h>
//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color, 0.0-opacity
    glColor3f(0.0, 0.0, 0.0); // set the drawing color - black
    glPointSize(4.0); // a dot is 4 by 4 pixels
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);//math coordinates comply with the window
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glBegin(GL_POINTS);
    glVertex2i(100, 50); // draw a group of 3 points

    glVertex2i(100, 130);
    glVertex2i(150, 130);
    glEnd();
    glFlush(); // send all output to display
}
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);// set display mode
    glutInitWindowSize(640,480); // set the window size
    glutInitWindowPosition(100, 150); // set the window position on screen
    glutCreateWindow("Three points"); // open the window
    glutDisplayFunc(myDisplay); // register the redraw function
    myInit();
    glutMainLoop();// OpenGL loop
    return 0;
}
