#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>

GLfloat shiftx,shifty,shiftz,shift;//function Trajectory() changes
// these global variables
GLfloat r,g,b;//function Color() changes these global variables
GLfloat t=0, dt=0.001;// animation parameters

double x(double t)// equations of the spiral
{
    return sin(10*t);
}
double y(double t)
{
    return t;
}
double z(double t)
{
    return cos(10*t);
}

void Trajectory()
{
    //change the global variables
    shiftx=x(t);
    shifty=y(t);
    shiftz=z(t);
}
void Color()
{
    //change the global variables and set up the color
    r=1-t/4;//red decreasing when t=4 r=0
    g=t/4;//green increasing, when t=4 g=1
    b=0;
    glColor3d(r,g,b);
}
void DrawTrajectory()//plot the trajectory
{
    GLfloat t,dt;//local t and dt
    glColor3d(0,0,1);
    dt=0.01;
    glBegin(GL_LINES);
    for (t=0; t<=4; t=t+dt)
    {
        glVertex3d(x(t),y(t),z(t));
    }
    glEnd();
}
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); //set the projection matrix
    glLoadIdentity();
    gluPerspective(30, 1.0, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // set the modelview matrix
    glLoadIdentity();//ready to apply translations and rotations
    gluLookAt(5.0,5.0,15.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
}
void Display_TeaPot() // display teapot at the point shiftx,shifty,shiftz
{
    Trajectory();
    Color();
    glPushMatrix();
    glTranslated(shiftx,shifty,shiftz);
    glutWireTeapot(1.0); // the teapot
    glPopMatrix();
    glutSwapBuffers();
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawTrajectory();
    Display_TeaPot();
    t+=dt; // animation parameter
    if ((fabs(t)>=4) || (t<0) )
        dt=-dt;
}
void mouse(int button, int state, int x, int y) //click the left button
{
    if ((button==GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        glutIdleFunc(myDisplay); //start motion by the left click
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Example 11 ");
    myInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
