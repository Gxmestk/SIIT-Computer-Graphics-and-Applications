#include <windows.h>
#include <GL\glut.h>
#include <time.h>
#include <math.h>
#define XAXIS 1
#define YAXIS 2
#define ZAXIS 3
#define REVERSE 4
#define START 5
#define STOP 6
#define INIT 7
float anglex=0.0,danglex=0.0, danglexold=0.0;
float angley=0,dangley=0.0, dangleyold=0.0;
float anglez=0,danglez=0.0, danglezold=0.0;
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
    glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
    glMatrixMode(GL_PROJECTION); //set some additional parameters
    glLoadIdentity();
    gluOrtho2D(-30, 30.0, -30, 30.0);//set your coordinate system
    glMatrixMode(GL_MODELVIEW); //set some additional parameters
    glLoadIdentity();
}
void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluPerspective(30, 1, .01, 1000);
//the coordinate system, the window and glLookAt in your assigment
//can be different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void Time_Delay(GLint dur) //time delay
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}
float zero[3]= {0,0,0};
float ax[3]= {15,0,0};
float ay[3]= {0,15,0};
float az[3]= {0,0,15}; //axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3]) //plot vector
{
    plot_Arrow(zero,v);
}
void plot_Axis(float r, float g, float b)
{
    glColor3f(r,g,b);
    plot_Vector(ax);
    plot_Vector(ay);
    plot_Vector(az);
}
void Draw_Rect(void)
{
    int i;
    glPushMatrix();
    glColor3f(1,0,0);
    glRecti(-5,-5,5,5);
    glPopMatrix();
}
void Move_Rect()
{
    glPushMatrix();
    glRotated(anglex,1,0,0);
    glRotated(angley,0,1,0);
    glRotated(anglez,0,0,1);
    Draw_Rect();
    plot_Axis(0,0,0);
    glPopMatrix();
}
void Draw_Rect0()
{
    glPushMatrix();
    glBegin(GL_LINE_LOOP);
    glVertex3f(-5,-5,0);
    glVertex3f(-5,5,0);
    glVertex3f(5,5,0);
    glVertex3f(5,-5,0);
    glEnd();
    glPopMatrix();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    anglex=anglex+danglex;
    angley=angley+dangley;
    anglez=anglez+danglez;
    Draw_Rect0();
    Move_Rect();
    plot_Axis(0,0,1);
    glutSwapBuffers();
    Time_Delay(5);
}
void Menu(int option)
{
    switch (option)
    {
    case XAXIS:
        danglex=1;
        dangley=0;
        danglez=0;
        break;
    case YAXIS:
        danglex=0;
        dangley=1;
        danglez=0;
        break;
    case ZAXIS:
        danglex=0;
        dangley=0;
        danglez=1;;
        break;
    case REVERSE:
        danglex=-danglex;
        dangley=-dangley;
        danglez=-danglez;
        break;
    case STOP:
        danglexold=danglex;
        dangleyold=dangley;
        danglezold=danglez;
        danglex=0;
        dangley=0;
        danglez=0;
        break;
    case INIT:
        anglex=0;
        angley=0;
        anglez=0;
        danglex=0;
        dangley=0;
        danglez=0;
        danglexold=0;
        dangleyold=0;
        danglezold=0;
        break;
    case START:
        danglex=danglexold;
        dangley=dangleyold;
        danglez=danglezold;
        break;
    }
}
void createGLUTMenus()
{
    int menu = glutCreateMenu(Menu);
    glutAddMenuEntry("x-axis",XAXIS);
    glutAddMenuEntry("y-axis",YAXIS);
    glutAddMenuEntry("z-axis",ZAXIS);
    glutAddMenuEntry("Reverse",REVERSE);
    glutAddMenuEntry("Re-Start",START);
    glutAddMenuEntry("Stop",STOP);
    glutAddMenuEntry("Initialize",INIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("example 5"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
    glutIdleFunc(myDisplay); // register the mouse event function
    myInit3d();
    createGLUTMenus(); //initialize settings
    glutMainLoop(); // go into the perpetual loop
}
