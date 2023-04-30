#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

double shiftx,shifty,shiftz;//position of the triangle
//function Trajectory() changes these global variables
double angle=0, dangle=0.01; // animation parameters
double t=0, dt=0.0005;
//piecewise linear interpolation points
double xp[]= {-1,0,0,1,1,2,2,3};
double yp[]= {-1,-1,0,0,1,1,2,2};
double zp[]= {0,0,0,0,0,0,0,0};
int n=(int)sizeof(xp)/sizeof(double);//number of points
bool move=false, rotate=false; // start/stop animation
//--------------interpolation-------------------
double f(double *p,double t)// interpolation based on the array p;
{
    int i;
    double returnf;
    for (i=1; i<=n-1; i++)
        if ((t<=i)&&(t>=i-1))
        {
            returnf=p[i]*(t-i+1)+p[i-1]*(i-t);
            break;
        }
    return returnf;
}
double x(double t)
{
    return f(xp,t);   // x- interpolation
}
double y(double t)
{
    return f(yp,t);   //y interpolation
}
double z(double t)
{
    return f(zp,t); // z interpolation
}
//----------------------------------------------

void Trajectory()//changes the global variables shiftx, shifty, shiftz to move the triangle
{
    shiftx=x(t);
    shifty=y(t);
    shiftz=z(t);
}
void DrawTrajectory()
{
    double t,dt=0.5;//local t and dt
    double xx,yy,zz;
    int i;
    glColor3d(0,0,1);
    glBegin(GL_LINE_STRIP);
    for (t=0; t<=n-1; t=t+dt)
        glVertex3d(x(t),y(t),z(t));
    glEnd();
}
void draw_Points()// plot the interpolation points
{
    int i;
    glColor3d(0,0,0);
    glPointSize(5);
    glBegin(GL_POINTS);
    for (i=0; i<=n-1; i++)
    {
        glVertex3d(xp[i],yp[i],zp[i]);
    }
    glEnd();
}
void draw_1Point(double x, double y, double z)
{
    glColor3d(0,0,0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3d(x,y,z);
    glEnd();
}
void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION); //set the projection matrix
    glLoadIdentity();
    gluPerspective(15, 1.0, .01, 10000);
    gluLookAt(15.0,15.0,15.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW); // set the modelview matrix
    glLoadIdentity();//ready to apply translations and rotations
}
void display_Triangle(double R)
//draw equilateral triangle, radius=R in the plane (x,y) (z=0)
{
    double step=2*M_PI/3;//angular step 120 degrees
    int i;
    double x,y,z;
    glColor3d(0,0,1);//blue color
    glBegin(GL_TRIANGLES);
    for (i=0; i<=2; i++)
    {
        x=R*cos(step*i);//the triangle is in the plane x,y (z=0)
        y=R*sin(step*i);
        z=0;
        glVertex3d(x,y,z);
    }
    glEnd();
}
void display_Move()// animation function
{
    glPushMatrix();
    glRotated(angle,0,1,0);
    draw_Points();
    DrawTrajectory();
    Trajectory();
    glTranslated(shiftx,shifty,shiftz);
    display_Triangle(0.3);
    glPopMatrix();
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_Move();
    if (move)
        t+=dt;//increment if move=true
    if (rotate)
        angle+=dangle;//increment if rotate=true
    if ((fabs(t)>=n-1) || (t<0) )
        dt=-dt;//turn back
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) //mouse control function
{
    if ((button==GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        if (move)
            move=false;
        else
            move=true;//switch between true and false
    if ((button==GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
        if (rotate)
            rotate=false;
        else
            rotate=true;//switch between true and false
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Example 0");
    myInit();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
