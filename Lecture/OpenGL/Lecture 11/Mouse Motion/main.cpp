#include <windows.h>
#include <gl/glut.h>
#include <string.h>
#include <stdio.h>

GLfloat inc=0.1; //angle increment
GLfloat angle=0; //rotation angle
GLint yprev=0;
void output_Text(float x, float y, float z, char *text) //output a text at x,y,z,
//we will use several versions of this function at the upcoming lectures and labs
{
    int len, i;
    glColor3f(0, 0, 1); //blue text
    glRasterPos3f(x, y, z);
    len = (int) strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}
void Rot_Teapot()
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    angle=angle+inc; //angle increment positive or negative
    glPushMatrix();
    glRotatef(angle,0,0,1);//positive rotation around z when x rotates to y
    glColor3f(1.0,0.0,0.0);
    glutSolidTeapot(3.0);
    glColor3f(0.0,0.0,0.0);
    glutWireTeapot(3.0);
    glPopMatrix();
}
void Init(void)
{
    glClearColor(1.0, 1.0, 1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //
    gluPerspective(30, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(15.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void myDisplay(void)
{
    Rot_Teapot();
    output_Text(0, -3, 4,"Move the mouse up or down, right click to stop");
    glutSwapBuffers();// instead of glFlush, use GLUT_DOUBLE
}
void Do_Nothing()
{ }
void motion(int x, int y)
{
    if (y<yprev)
        inc=0.1;
    else
        inc=-0.1;
    yprev=y;
    glutIdleFunc(myDisplay);
}
void mouse(int button, int state, int x, int y)
{
    if (button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        glutIdleFunc(Do_Nothing);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );//this
    glutInitWindowSize(480,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Example 4");
    glutDisplayFunc(myDisplay);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    Init();
    glutMainLoop();
}
