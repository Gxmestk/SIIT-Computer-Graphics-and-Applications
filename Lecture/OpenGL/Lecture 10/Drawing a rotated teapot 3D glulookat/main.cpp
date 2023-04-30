#include <windows.h>
#include <gl/glut.h>

GLfloat angle=0, vx=0, vy=1, vz=0;//parameters of the rotation
GLfloat eyex=2, eyey=2, eyez=2; //your position
GLfloat lookx=0, looky=0, lookz=0; // we look at this point
GLfloat upx=0, upy=1, upz=0; //the “up” vector

void Display_TeaPot(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); // the current is the projection matrix
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100);// math coordinates
    glMatrixMode(GL_MODELVIEW); // the current is the modelview matrix
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, upx, upy, upz); // position
    glRotated(angle,vx,vy,vz); // rotation
    glutWireTeapot(1.0); // the standard OpenGL function, the teapot size=1
    glFlush();
}
void MyInit()
{
    glClearColor(1.0, 1.0, 1.0,0.0); // the background is white
    glColor3d(0,0,1); // the drawing color

}
void mydisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    Display_TeaPot();
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Teapot Transformations");
    MyInit();
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}
