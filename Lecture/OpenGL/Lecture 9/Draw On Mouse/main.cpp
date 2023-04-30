#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
bool start = false;
GLint wx=500;
GLint wy=500;
void draw_Triangle(GLfloat cornerX, GLfloat cornerY, GLfloat size)
{
    glBegin(GL_POLYGON);
    glColor3f(1,0,0); // Set the drawing color to red.
    glVertex2f(cornerX, cornerY);
    glVertex2f(cornerX+size, cornerY);
    glVertex2f(cornerX+size/2, cornerY+size);
    glEnd();
    glFlush(); // Process all OpenGL routines as quickly as possible.
}
void draw_Rectangle(GLfloat X,GLfloat Y,GLint size)
{
    glColor3f (0,0,1);
    glBegin (GL_POLYGON);
    glVertex2f(X-size/2,Y-size/2);
    glVertex2f(X+size/2,Y-size/2);
    glVertex2f(X+size/2,Y+size/2);
    glVertex2f(X-size/2,Y+size/2);
    glEnd ( );
    glFlush ( ); // Process all OpenGL routines as quickly as possible.
}
void ClearOrdoNothing(void)
{
    if (!start)
    {
        start = true;
        glClear(GL_COLOR_BUFFER_BIT); // Clear display window.

        glFlush();
    }
}
void mouse(GLint button, GLint state, GLint x, GLint y)
{
    if (button ==GLUT_LEFT_BUTTON && state== GLUT_DOWN)
        draw_Triangle(x, wy-y,30);
    else if (button ==GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
        draw_Rectangle(x,wy-y,20);
}
void resize(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0*w, 0.0, 1.0*h);
    wx=w;
    wy=h;//new math coordinates and viewport
    start=false;//clear the window
}
void myInit(void)
{
    glClearColor(1, 1, 1, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, wx, 0.0, wy); // set the word coordinate system
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wx, wy);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Ex_6");
    myInit();
    glutDisplayFunc(ClearOrdoNothing);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutMainLoop();
}
