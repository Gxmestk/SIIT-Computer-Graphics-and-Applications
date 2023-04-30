#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <math.h>
#include <time.h>
GLfloat x,y,z;
GLfloat Pi=M_PI;
GLfloat shiftx,shifty,shiftz,shift;
GLfloat t=0, dt=0.01;
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
void Display_TeaPot()
{
    float r,g,b;
    r=1-t/(4*Pi);
    g=0;
    b=t/(4*Pi);
    glColor3d(r,g,b);
    shiftx=sin(t);
    shifty=cos(t);
    shiftz=t/10;
    glPushMatrix();
    glTranslated(shiftx,shifty,shiftz);
    if (rotate)
    {
        glRotated(angle,0,1,0);
        angle++;
    }
    else
        glRotated(angle,0,1,0);
    glutWireTeapot(1.0); // the teapot
    glPopMatrix();
    plot_Axis();
    output_Text(-2,2,"left/right click");
    glutSwapBuffers();
}
void DrawTrajectory()
{
    GLfloat t,dt;
    glColor3d(1,0,0);
    dt=0.01;
    glBegin(GL_POINTS);
    for (t=0; t<=12*Pi; t+=dt)
    {
        x=sin(t);
        y=cos(t);
        z=t/10;
        glVertex3d(x,y,z);
    }
    glEnd();
}
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(60, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(4.0,4.0,4.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawTrajectory();
    Display_TeaPot();

    t+=dt;
    if ((t>=12*Pi)||(t<0))
        dt=-dt;
}
void Do_Nothing(void)
{ }
void mouse(int button, int state, int x, int y) //press left/right button
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            if (rotate)
                rotate=false;
            else
                rotate=true;
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            if (move)
                move =false;
            else
                move=true;
            if (move)
                glutIdleFunc(myDisplay);
            else
                glutIdleFunc(Do_Nothing);
        }
        break;
    default:
        break;
    }
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
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
