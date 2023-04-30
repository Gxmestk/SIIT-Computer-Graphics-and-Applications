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

bool type=false;//true - contracting spiral, false infinite spiral
float Rad=1,s = 0,ds =  0.001,dt = 0.001 ;  //radius of the infinite spiral


void DrawPoint(GLint x, GLint y)
{
    glColor3f(0.0, 0.0, 1.0); // set the drawing color blue
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluPerspective(60,1,0.1,1000);
    glMatrixMode(GL_MODELVIEW); //set some additional parameters
    glLoadIdentity();
    gluLookAt(2,2,2,0,0,0,0,1,0);
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


float R(float t, bool type )
{
    float a;
    if (type)
    {
        if ((1-t)>0)
            a=(1-t) ;
        else
            a=0;
    }
    else
        a=Rad;
    return a;
}
float sx(float t,bool type)
{
    return R(t,type)*sin(50*t) ;
}
float sy(float t, bool type)
{
    return R(t,type)*cos(50*t);
}
float sz(float t, float R)
{
    return t;
}

void plot_Trajectory()
{
    float x,y,z,t;
    if (s>1)
        s=0;
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    for(t = 0; t <=s; t += dt)
    {
        glColor3f(0.0, 0.0, 1.0);
        x = sx(t,type);
        y = sy(t,type);
        z = sz(t,type);
        glVertex3f(x,y,z);
    }
    glEnd();
    glLineWidth(1);
}

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


void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    plot_Trajectory();
    plot_Axis(0,0,0);
    s+=ds;
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    if (button==GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        type=1-type;//switch between true and false
    glutIdleFunc(myDisplay);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("example 6"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
    glutIdleFunc(myDisplay); // register the mouse event function
    myInit3d();
    glutMouseFunc(mouse);
    glutMainLoop(); // go into the perpetual loop
}
