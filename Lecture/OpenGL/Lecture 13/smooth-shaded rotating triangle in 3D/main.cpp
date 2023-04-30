#include <windows.h>
#include <GL/glut.h>
#include <time.h>
GLfloat ang=0,dang=1;
void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur)
    {
    }
}
void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); //reset the current Projection Matrix
    gluPerspective(45, 1.33, .01, 1000);//perspective view
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();// reset the current Modelview Matrix
    glEnable(GL_DEPTH_TEST);//close objects obstruct far objects
}
void Draw_Triangle()
{
    glShadeModel(GL_SMOOTH);
    glPushMatrix();
    glRotated(ang,1,1,0);
    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0); //the red green and blue vertices
    glVertex3f(0, 0, 0);
    glColor3f(0,1,0);
    glVertex3f(20, 0, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 20, 0);
    glEnd();
    glPopMatrix();
    ang=ang+dang;
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Draw_Triangle();
    glutSwapBuffers();
    Time_Delay(10);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Example 0 Triangle");
    myInit3d();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutMainLoop();
}
