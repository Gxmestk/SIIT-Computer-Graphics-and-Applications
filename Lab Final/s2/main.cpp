#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <math.h>
#include <time.h>
#define ROTX 1
#define ROTY 2
#define ROTZ 3

GLfloat ang=0, dang=0.05, x =1,y=0,z=0;
int axis = ROTX;

void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur)
    {
    }
}

void draw_Origin()
{
    glColor3f(1,1,1);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
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
void output_Text(float x, float y, float z, char *text) //output a text at x,y,z
{
    int len, i;
    glColor3f(0, 0, 0); //black text
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(60, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(1.0,1.0,1.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
}
void draw_tri()
{
    glPushMatrix();
    glRotatef(ang,x,y,z);
    glColor3f(1,0,0);
    glBegin(GL_TRIANGLES);
    glVertex3d(1,0,0);
    glVertex3d(-1,1,0);
    glVertex3d(-1,-1,0);
    glEnd();
    glPopMatrix();
    ang += dang;

}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    draw_tri();
    draw_Origin();
    plot_Axis();
    output_Text(-200,-240,15,"Right click for the menu");
    glutSwapBuffers();
}

void Menu_Color(int axis)
{
    if (axis == ROTX)
    {
        x = 1;
        y = 0;
        z = 0;
    }
    else if (axis == ROTY)
    {
        x = 0;
        y = 1;
        z = 0;
    }
    else if (axis == ROTZ)
    {
        x = 0;
        y = 0;
        z = 1;
    }
}
void createGLUTMenus() {
    int menu = glutCreateMenu(Menu_Color);
    glutAddMenuEntry("X-Axis",ROTX);
    glutAddMenuEntry("Y-Axis",ROTY);
    glutAddMenuEntry("Z-Axis",ROTZ);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
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
    createGLUTMenus();
    glutMainLoop();
    return 0;
}

