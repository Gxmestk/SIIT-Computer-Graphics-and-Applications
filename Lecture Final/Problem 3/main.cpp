#include <windows.h>
#include<GL/glut.h>
#include <time.h>
#include <string.h>
#include <math.h>
#define X_axis 1
#define Y_axis 2
#define Z_axis 3
#define RED 1
#define BLUE 2
#define GREEN 3
#define SQRE 4
#define TRIA  3
#define CIRC 100
#define PI 3.14159265359

float angle = 0.0; //rotating angle
float dangle=0.1;
float vx=1,vy=0,vz=0;
int red=1, green=0, blue=0;
int shape=TRIA; //shape

void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur)
    {
    }
}

void Display_Polygon(int n)
{
    //appr. 13 lines
    float step, t,x,y,z,R=1;
    int i;
    step=2*M_PI/n;
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (i=1; i<=n; i++)
    {
        t=step*i;
        x=R*cos(t);
        y=R*sin(t);
        glVertex3f(x,y,0);
    }
    glEnd();
}

void myInit3d()
{
    //appr. 6 lines
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30, 1.33, .01, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 3.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Draw_Axis()
{
    //appr 9 lines
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();
}

void DrawPoint(GLint x, GLint y)
{
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void myDisplay(void) //our display function
{
//appr. 9 lines
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotated(angle,vx,vy,vz);
    Display_Polygon(shape);
    angle=angle+dangle;
    glPopMatrix();
    DrawPoint(0,0);
    Draw_Axis();
    glutSwapBuffers();
}

void Menu_Orientation(int option)
{
    // switch 6 lines
    switch (option)
    {
    case X_axis:
        vx=1.0;
        vy=0.0;
        vz=0.0;
        break;
    case Y_axis:
        vx=0.0;
        vy=1.0;
        vz=0.0;
        break;
    case Z_axis:
        vx=0.0;
        vy=0.0;
        vz=1.0;
        break;
    default :
        break;
    }
}

void Menu_Color(int option)
{
    // switch 6 lines
    switch (option)
    {
    case RED:
        red=1.0;
        green=0.0;
        blue=0.0;
        break;
    case GREEN:
        red=0.0;
        green=1.0;
        blue=0.0;
        break;
    case BLUE:
        red=0.0;
        green=0.0;
        blue=1.0;
        break;
    default :
        break;
    }
}

void Menu_Shape(int option)
{
    // one line
    shape=option;
}

void createGLUTMenus()
{
    //generate the menus , 17 lines
    int menu1=glutCreateMenu(Menu_Orientation);
    glutAddMenuEntry("X-axis",X_axis);
    glutAddMenuEntry("Y-axis",Y_axis);
    glutAddMenuEntry("Z-axis",Z_axis);
    int menu2=glutCreateMenu(Menu_Color);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Blue",BLUE);
    int menu3=glutCreateMenu(Menu_Shape);
    glutAddMenuEntry("Square",SQRE);
    glutAddMenuEntry("Triangle",TRIA);
    glutAddMenuEntry("Circle",CIRC);
    int menu = glutCreateMenu(NULL);
    glutAddSubMenu("Rotation",menu1);
    glutAddSubMenu("Color",menu2);
    glutAddSubMenu("Shape",menu3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Problem 3");
    myInit3d();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    createGLUTMenus();
    glutMainLoop();
}
