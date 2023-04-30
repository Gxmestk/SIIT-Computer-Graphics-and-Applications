#include <windows.h>
#include <GL\glut.h>
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(0.0, 0.0, 0.0); // set the drawing color
    glMatrixMode(GL_PROJECTION); //set the projection matrix
    glLoadIdentity();
    gluOrtho2D(-100.0,100.0,-100.00,100.0);// your coordinate system
    glMatrixMode(GL_MODELVIEW); //set the modelview matrix
    glLoadIdentity();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glColor3f(1.0, 0.0, 0.0); //red
    glRecti(-25,-25,25,25);//draw the initial red rectangle 50x50
    glColor3f(0.0, 0.0, 1.0); //blue
    glRotatef(30, 0.0, 0.0, 1.0); //Rotate the coordinates 30-deg. about the z axis.
    glRecti(-25,-25,25,25); //draw the rectangle relative to the new origin
    glColor3f(0.0, 1.0, 0.0); //green
    glTranslatef(70.0, 0.0, 0.0); // translate the origin
    glRecti(-25,-25,25,25);//draw the rectangle relative to the new origin
    glFlush(); // send all output to display
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(400,400); // set window size
    glutInitWindowPosition(0,0); // set window position on screen
    glutCreateWindow("example 1"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
    myInit(); //initialize settings
    glutMainLoop(); // go into the perpetual loop
}
