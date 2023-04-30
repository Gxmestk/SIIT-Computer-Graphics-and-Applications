#include <windows.h>
#include <gl/glut.h>

GLfloat angle=0, vx=0, vy=1, vz=0;
float inc=0.25;
void Display_TeaPot(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    angle=angle+inc;
    glPushMatrix();
    glRotated(angle,vx,vy,vz);
    glutWireTeapot(1.0); // the teapot size=1
    glPopMatrix();
}
void MyInit()
{
    glClearColor(1.0, 1.0, 1.0,0.0); // the background is white
    glColor3d(0,0,1); // the rgb color
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(30, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void Do_Nothing(void)
{ }
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Display_TeaPot();
    glutSwapBuffers();
}
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(myDisplay);
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            glutIdleFunc(Do_Nothing);
        break;
    default:
        break;
    }
}
void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 's':
        glutIdleFunc(myDisplay);
        break;
    case 'e':
        glutIdleFunc(Do_Nothing);
        break;
        break;
    default:
        break;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Example 2");
    MyInit();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(mouse);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
}
