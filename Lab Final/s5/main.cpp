#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

GLfloat Pi=M_PI;

GLfloat angle=0,dang = 0.01;
GLfloat angle2=0,dang2 = 0.05;

bool inc=false;

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
GLfloat xp(GLfloat t)
{
    return R * cos(t);
}
GLfloat yp(GLfloat t)
{
    return R * sin(t);
}
GLfloat zp(GLfloat t)
{
    return 0;
}
void draw_Origin()
{
    glColor3f(0,0,0);
    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
}
void Display_TeaPot()
{
    glColor3d(1,0,0);

    glPushMatrix();

    glRotated(angle,0,1,0);
    angle+=dang;

    glBegin(GL_TRIANGLES);

    for (double t=0; t<= 4 * Pi / 3; t+=2*Pi / 3)
    {
        glVertex3d(xp(t),yp(t),zp(t));
    }
    glEnd();
    glColor3d(0,0,0);
    draw_Origin();
    glPopMatrix();

    //plot_Axis();

    output_Text(-2,2,"right click for menu");
    glutSwapBuffers();
}

void DrawTrajectory()
{
    GLfloat t,dt;
    glColor3d(0,0,1);
    dt=0.05;
    glPushMatrix();
    glRotated(angle2,0,0,1);
    angle2+=dang2;
    glBegin(GL_LINES);
    for (t=0; t<=2*Pi; t+=dt)
    {
        glVertex3d(xp(t),yp(t),zp(t));
    }
    glEnd();
    glPopMatrix();
}
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(60, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(0.0,0.0,3.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawTrajectory();
    Display_TeaPot();

}
void Do_Nothing(void)
{ }
void Menu_Color(int option)
{
    if (option == 0)
    {
        dang = -dang;
        dang2 = - dang2;
    }
}
void createGLUTMenus()
{
    int menu = glutCreateMenu(Menu_Color);
    glutAddMenuEntry("ReverseRot",0);
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

