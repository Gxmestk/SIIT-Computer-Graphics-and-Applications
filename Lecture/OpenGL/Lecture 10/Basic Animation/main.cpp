#include <windows.h>
#include <GL\glut.h>
#include <time.h>
GLfloat angle=50;

void DrawPoint(GLint x, GLint y) // draw the origin
{
    glColor3f(0.0, 0.0, 0.0); // set the drawing color black
    glPointSize(10);//large point 10x10 at x,y
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-200, 200, -200, 200);//set your math coordinate system
    glMatrixMode(GL_MODELVIEW); // the modelview matrix=transformations
    glLoadIdentity();//at this point the object is displayed “as is”
}
void Time_Delay(GLint dur) //time delay
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}
//<<<<<<<<<<<<<<<<<<<<<<<< my routines >>>>>>>>>>>>>>>>>
void Rotate_Rect(GLfloat angle)
{
    glPushMatrix(); // send the original transformation matrix to stack
    DrawPoint(0,0);// show the origin
    glRotatef(angle, 0.0, 0.0, 1.0); // Set angle-deg. rotation about the z axis.
    glTranslatef(50,50,0); // Set translation
    glRotatef(angle, 0.0, 0.0, 1.0); // Set angle-deg. rotation about the z axis.
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glRecti (-35,-35, 35, 35); // Display the rotated rectangle 70x70.
    DrawPoint(0,0); //show the origin again
    glPopMatrix(); // restore the transformation matrix
    glFlush(); //send to the screen
    Time_Delay(50);
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Rotate_Rect(angle);
    angle++;
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(400,400); // set window size
    glutInitWindowPosition(0, 0); // set window position on screen
    glutCreateWindow("example 2"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
    glutIdleFunc(myDisplay);
    myInit(); //initialize settings
    glutMainLoop(); // go into the perpetual loop
}
