#include <windows.h>
#include <GL\glut.h>
#include <time.h>
GLfloat angle=0;
void DrawPoint(GLint x, GLint y)
{
    glColor3f(0.0, 0.0, 1.0); // set the drawing color blue
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void myInit(void)
{
    glClearColor(1.0,1.0,1.0,0.0); // set white background color
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glMatrixMode(GL_PROJECTION); //the projection matrix
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);//set your coordinate system
    glMatrixMode(GL_MODELVIEW); //the modelview matrix
    glLoadIdentity();
    DrawPoint(0,0);
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
    glPushMatrix(); // send the preceding transformation matrix to stack
    glTranslatef(100,100,0); // Set translation
    glRotatef(angle, 0.0, 0.0, 1.0); // Set angle-deg. rotation about the z axis.
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glRecti (-35,-35, 35, 35); // Display the rotated rectangle.
    DrawPoint(0,0);
    glPopMatrix(); // restore the transformation matrix
    glFlush();
    Time_Delay(50);
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Rotate_Rect(angle);
    angle++;
}
void Do_Nothing(void)
{ }
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(myDisplay);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(Do_Nothing);
        break;
    default:
        break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(400,400); // set window size
    glutInitWindowPosition(0, 0); // set window position on screen
    glutCreateWindow("example 3"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
//glutIdleFunc(myDisplay);
    glutMouseFunc(mouse); // register the mouse event function
    myInit(); //initialize settings
    glutMainLoop(); // go into the perpetual loop
}
