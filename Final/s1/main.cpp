#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

GLfloat Pi=M_PI;

GLfloat angle=0;
bool rotate=false;
bool move=true;

void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur)
    {
    }
}

float ax[3]= {4,0,0};
float ay[3]= {0,4,0};
float az[3]= {0,0,4}; //axes

void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3]) //plot vector
{
    float zero[3]= {0,0,0};
    plot_Arrow(zero,v);
}
void plot_Axis()
{
    glColor3f(0,0,0);
    plot_Vector(ax);
    plot_Vector(ay);
    plot_Vector(az);
}
void output_Text(float x, float y, char *text) //output a text at x,y
{
    int len, i;
    glColor3f(0, 0, 0); //red text
    glRasterPos3f(x, y, 0);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}
GLfloat R=1;


GLfloat x1(GLfloat t)
{
    return sin(3*t);
}
GLfloat y1(GLfloat t)
{
    return sin(2*t);
}
GLfloat z1(GLfloat t)
{
    return 0;
}


GLfloat x2(GLfloat t)
{
    return t-1;
}
GLfloat y2(GLfloat t)
{
    return 0;
}
GLfloat z2(GLfloat t)
{
    return sin(10 * (t-1) * (t-1));
}


void DrawTrajectory1()
{
    GLfloat t,dt;
    glColor3d(1,0,0);
    dt=0.05;
    glBegin(GL_LINES);
    for (t=0; t<=Pi + 2.35 ; t+=dt)
    {
        glVertex3d(x1(t),y1(t),z1(t));
    }
    glEnd();
}

void DrawTrajectory2()
{
    GLfloat t,dt;
    glColor3d(0,0,1);
    dt=0.01;
    glBegin(GL_LINE_STRIP);
    for (t=0; t<=2; t+=dt)
    {
        glVertex3d(x2(t),y2(t),z2(t));
    }
    glEnd();
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(45, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(2.0,2.0,2.0, -1.0,-1.0,-1.0, 0.0,1.0,0.0);
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_Axis();
    glLineWidth(3);
    DrawTrajectory1();
    glLineWidth(1);
    DrawTrajectory2();
    glutSwapBuffers();
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Example 12");
    myInit();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutMainLoop();
    return 0;
}

