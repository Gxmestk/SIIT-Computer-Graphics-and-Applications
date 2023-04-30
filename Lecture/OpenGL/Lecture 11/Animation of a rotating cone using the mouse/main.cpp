#include <windows.h>
#include<GL/glut.h>
#include <time.h>
#include <string.h>
#include <stdio.h>


bool move=false;
float angle = 0.0, inc=1; //the rotation angle
float vx=0,vy=0,vz=1;//the rotation vector
void output_Text(float x, float y, float z, char *text) //output a text at x,y
{
    int len, i;
    glColor3f(0, 0, 0); //black
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);//output text[i] on the screen
    }
}
float ax[3]= {25,0,0};
float ay[3]= {0,25,0};
float az[3]= {0,0,25}; //axes
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

void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur)
    {
    }
}
void Rotate_Cone()//display teapot
{
    glPushMatrix();
    glRotated(angle,vx,vy,vz);
    glColor3d(1,0,0); // red color
    glutWireCone(1.0,2,20,20); //
    glPopMatrix();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    output_Text(-8,-10,0,"Left click start, right click-stop");
    Rotate_Cone();
    plot_Axis();
    if (move)
        angle=angle+inc;
    glutSwapBuffers();//sends to the screen
    Time_Delay(50);
}
void Do_Nothing(void)
{ }
void mouse(GLint button, GLint state, GLint x, GLint y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            move=true;
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            move=false;
        break;
    default:
        break;

    }

}
void Init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,1.33,0.01,1000);
    gluLookAt(0,5.0,5.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1,1,1,0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Example 1 Cone Animation");
    Init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutMouseFunc(mouse);
    glutMainLoop();
}
