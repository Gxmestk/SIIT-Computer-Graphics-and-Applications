#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

GLfloat A=0.0;//rotation angle
GLfloat angle_inc=0.01;//increment
GLfloat Deg=M_PI/180;//convert degree to radians
GLfloat A1=90*Deg, A2=210*Deg, A3=330*Deg;
GLfloat R=1;//radius of the circle.

GLfloat xS1=R*cos(A1);//coordinates of ?
GLfloat yS1=R*sin(A1);
GLfloat xS2=R*cos(A2);
GLfloat yS2=R*sin(A2);
GLfloat xS3=R*cos(A3);
GLfloat yS3=R*sin(A3);
GLfloat zS=0;

float p1[]= {xS1,yS1,zS}; //coordinates of ?
float p2[]= {xS2,yS2,zS};
float p3[]= {xS3,yS3,zS};

void changeSize(GLsizei w, GLsizei h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,1,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1, 1, 5,
              0,0,0,
              0.0,1.0,0.0);
}

void initScene()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_FLAT);
}

void display_Circle(float RC, float x, float y, float z)
{
    float t, dt=0.1, xc,yc;
//x,y,z, center of the circle, RC - radius
//here appr. 6 lines change the text color  to see the solution
    glPushMatrix();
    glTranslated(x,y,z);
    glBegin(GL_LINES);
    for (t=0; t<2*M_PI; t+=dt )
    {
        xc=R*sin(t);
        yc=R*cos(t);
        glVertex3f(xc,yc,0);
    }
    glEnd();
    glPopMatrix();
}

void display_Triangle()
{
    int i;
//appr 4~5 lines
    glBegin(GL_LINE_LOOP);
    glVertex3fv(p1);
    glVertex3fv(p2);
    glVertex3fv(p3);
    glEnd();
}

void Draw_Axis()
{
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
    glEnd();
}

void DrawPoint(GLint x, GLint y, GLint z)
{
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(8);
    glBegin(GL_POINTS);
    glVertex3f(x,y,z);
    glEnd();
}

void Rotate_Shapes()
{
    //appr 10 lines
    glPushMatrix();
    glRotated(A,0,1,0);
    glColor3f(0,0,0);
    display_Circle(R,xS1,yS1,zS);
    display_Circle(R,xS2,yS2,zS);
    display_Circle(R,xS3,yS3,zS);
    display_Triangle();
    DrawPoint(0,0,0);
    glPopMatrix();
    Draw_Axis();
}

void display(void)
{
    //draw scene approximately 5 lines
    glClearColor(1.0, 1.0, 1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Rotate_Shapes();
    A+=angle_inc;
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
// appr. 6 lines
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("Problem 1");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(changeSize);
    glutMainLoop();
    return(0);
}
