#include <windows.h>
#include <gl/glut.h>
void Display_TeaPot(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutWireTeapot(1.0); // the teapot size=1
    glFlush();
}
void MyInit()
{
    glClearColor(1.0, 1.0, 1.0,0.0); // the background is white
    glColor3d(0,0,1); // the rgb color
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
//glOrtho(-2,2,-2,2,0,5);//swap
    gluPerspective(45, 1.33, .01, 10000); //swap, change the view angle
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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Example 9 Teapot. Perspective view");
    MyInit();
    glutDisplayFunc(mydisplay);
    glutMainLoop();
}
