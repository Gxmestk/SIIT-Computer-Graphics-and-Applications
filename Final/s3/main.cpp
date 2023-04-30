#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <math.h>
#include <time.h>


GLfloat angle=0, dang=0.01;

bool rotate=true;

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

    glColor3d(1,0,0);
    glPushMatrix();
    if (rotate)
    {
        glRotated(angle,0,1,0);
        angle+=dang;
    }
    else
        glRotated(angle,0,1,0);
    glRotated(90,1,0,0);
    glTranslated(1,1,0);
    glRecti(-1,-1,1,1);

    glPopMatrix();
    plot_Axis();
    output_Text(-2,2,"Press Some Key");
    glutSwapBuffers();
}
void Do_Nothing(void)
{ }
void myKeyboard(unsigned char key, int x, int y)
{
    if (key == 'E' || key == 'e')
        rotate = false;
    if (key == 'r' || key == 'R')
        rotate = true;
    if (key == 'F' || key == 'f')
        dang *= 1.5;
    if (key == 'B' || key == 'b')
        dang /= 1.5;
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
    glutKeyboardFunc(myKeyboard);
    glutMainLoop();
    return 0;
}

