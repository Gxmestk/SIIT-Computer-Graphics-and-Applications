#include <windows.h>
#include <gl/glut.h>
#include <time.h>
GLfloat angle=0, vx=0, vy=0, vz=1;
GLfloat eyex=2, eyey=2, eyez=2;
GLfloat lookx=0, looky=0, lookz=0;
GLfloat upx=0, upy=1, upz=0;

void Time_Delay(GLint dur) //time delay
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}

void Display_TeaPot(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotated(angle,vx,vy,vz);
    glutWireTeapot(1.0); // the teapot size=1
    glPopMatrix();
    angle++;
    glutSwapBuffers();
    Time_Delay(50);
}
void MyInit()
{
    glClearColor(1.0, 1.0, 1.0,0.0); // the background is white
    glColor3d(0,0,1); // the rgb color
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    gluPerspective(45, 1.33, .01, 10000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
}
void mydisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Display_TeaPot();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize(400,400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Example 9 Animation");
    MyInit();
    glutDisplayFunc(mydisplay);
    glutIdleFunc(mydisplay);
    glutMainLoop();
}
