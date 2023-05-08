#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <math.h>
#include <time.h>

GLfloat Pi=M_PI;

GLfloat angle=0 , dang = 0.005;
GLfloat angle2=0 , dang2= 0.1;
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

    glPushMatrix();

    glLineWidth(3);
    glColor3d(1,0,1);

    glRotated(angle,0,1,0);

    glBegin(GL_LINES);
    glVertex3f(0,1,0);
    glVertex3f(0,1,4);
    glEnd();
    glLineWidth(1);
    angle+= dang;

    glTranslated(0,1,4);
    glColor3d(0,0,0);
    glRotated(angle2,0,0,1);
    glutWireCone(1,2,20,20);
    glPopMatrix();
    plot_Axis();
    angle2 += dang2;
    glutSwapBuffers();
}

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(60, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(6.0,6.0,6.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Display_TeaPot();

}
void Do_Nothing(void)
{ }
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

