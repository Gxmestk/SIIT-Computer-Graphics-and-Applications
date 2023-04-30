#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
bool start = false;
GLint wx=500;
GLint wy=500;
GLfloat X=250,Y=150;
GLfloat Size=100;
GLfloat Color[]= {0,0,1,0};
void Print_Text(float x, float y, float z, char* text)//prints text on the screen
{
    int k, len;
    len=strlen(text);//length of the string here you need <string.h>
    glColor3f(0.9,0.9,0.9);
    glRasterPos3f(x,y,z);//text output position
    for (k = 0; k <=len; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[k]);
}
void draw_Rectangle(GLfloat X, GLfloat Y,GLfloat size)
{
    glBegin (GL_POLYGON);
    glVertex2f(X-size/2,Y-size/2);
    glVertex2f(X+size/2,Y-size/2);
    glVertex2f(X+size/2,Y+size/2);
    glVertex2f(X-size/2,Y+size/2);
    glEnd ( );
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4fv(Color);
    draw_Rectangle(X,Y,Size);
    Print_Text(220,150,0,"click me");
    glFlush();
}
void mouse(GLint button, GLint state, GLint x, GLint y)
{
    float Y1=wy-Y;
    if ((button==GLUT_LEFT_BUTTON) and (state==GLUT_DOWN))
    {
        if ((x>=X-Size/2) && (x<=X+Size/2) && (y>=Y1-Size/2) && (y<=Y1+Size/2))
        {
            Color[0]=rand()%1000/1000.0;
            Color[1]=rand()%1000/1000.0;
            Color[2]=rand()%1000/1000.0;
        }
    }
    myDisplay();
}
void resize(int w, int h)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, w, h);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0*w, 0.0, 1.0*h);
    wx=w;
    wy=h;
}
void myInit(void)
{
    glClearColor(1, 1, 1, 0);
    glColor4fv(Color);
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
    glutCreateWindow("example 12");
    myInit();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutMainLoop();
}
