#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>

void output_Text(float x, float y, char *text)
{  int len, i;
  glColor3f(0, 0, 0); //red text
  glRasterPos3f(x, y, 0);
  len = (int)strlen(text);
  for (i = 0; i < len; i++) {
  glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
  }
}
float ax[3]={25,0,0}; float ay[3]={0,25,0}; float az[3]={0,0,25};//axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
     glVertex3fv(v1);
     glVertex3fv(v2);
     glEnd();
    }
void plot_Vector(float v[3]) //plot vector
{
float zero[3]={0,0,0};
plot_Arrow(zero,v);
}
void plot_Axes()
{
glColor3f(0,0,0);
plot_Vector(ax);
plot_Vector(ay);
plot_Vector(az);
}
void draw_1Point(double x, double y, double z)//plot a single point
{
glColor3d(1,1,0);
glPointSize(10);
glBegin(GL_POINTS);
glVertex3d(x,y,z);
glEnd();
}
double shiftx,shifty,shiftz;//function Trajectory() changes
// these global variables
double angle=0, dangle=0.01;
double t=0, dt=0.0005;
//piecewise linear interpolation points
double xp[10];
double yp[10];
double zp[10];
int n=10;
float R=3;
void Create_Points()
{ float step=2*M_PI/6; int i;
for (i=0;i<=5;i++)
{
xp[i]=R*cos(step*i);
yp[i]=0;
zp[i]=R*sin(step*i);
}
xp[6]=xp[0];
yp[6]=yp[0];
zp[6]=zp[0];
xp[7]=0;
yp[7]=0;
zp[7]=0;
xp[8]=0;
yp[8]=2;
zp[8]=0;
xp[9]=0;
yp[9]=4;
zp[9]=0;
}
bool move=false, rotate=false;
//--------------interpolation------------------- function
double f(double *p,double t)
{
int i;
double returnf;
for (i=1;i<=n-1;i++)
if ((t<=i)&&(t>=i-1))
{
returnf=p[i]*(t-i+1)+p[i-1]*(i-t);
break;
}
return returnf;
}

double x(double t)//x interpolation
{return f(xp,t);}
double y(double t)//y interpolation
{return f(yp,t);}
double z(double t)//z interpolation
{return f(zp,t);}
//----------------------------------------------
void Trajectory()//changes global variables shiftx, shifty, shiftz
{
shiftx=x(t);
shifty=y(t);
shiftz=z(t);
}
void DrawTrajectory() //plots the trajectory
{
double t,dt=0.5;//local t and dt
double xx,yy,zz;
int i;
glColor3d(0,0,1);
glBegin(GL_LINE_STRIP);
for (t=0;t<=n-1;t=t+dt)
glVertex3d(x(t),y(t),z(t));
glEnd();
}
void draw_Points() //plots the 8 anchor points
{
int i;
glColor3d(0,0,0);
glPointSize(5);
glBegin(GL_POINTS);
for (i=0;i<=n-1;i++)
{
glVertex3d(xp[i],yp[i],zp[i]);
}
glEnd();
}
void myInit()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glMatrixMode(GL_PROJECTION); //set the projection matrix
glLoadIdentity();
gluPerspective(25, 1.0, .01, 10000);
gluLookAt(15.0,12.0,12.0, 0.0,0.0,0.0, 0.0,1.0,0.0);
glMatrixMode(GL_MODELVIEW); // set the modelview matrix
glLoadIdentity();//ready to apply translations and rotations
glEnable(GL_DEPTH_TEST);// close objects obstract far objects
}
void display_Sphere(double R)
{
if (dt>=0) glColor3f(0.8,0.8,0.8); else glColor3f(0,0,0);
glutSolidSphere(R,10,10);
glColor3f(1,0,0);
glutWireSphere(R+0.01,20,20);//+0.01to see lines better
}
void display_Move()
{
glPushMatrix();
draw_Points();
DrawTrajectory();
Trajectory();
glTranslated(shiftx,shifty,shiftz);
display_Sphere(0.75);
glPopMatrix();
//plot_Axes();
draw_1Point(0,0,0);
output_Text(-5,-10,"left click-move/stop the sphere");
}
void myDisplay(void)
{glClearColor(1,1,1,0);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
display_Move();
if (move) t+=dt;//increment if move=true
angle+=dangle;
if ((fabs(t)>=n-1) || (t<0) ) dt=-dt;//turn back
glutSwapBuffers();
}
void mouse(int button, int state, int x, int y) //press the right button
{
if ((button==GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
if (move) move=false; else move=true;//switch between true and false
}
int main(int argc, char **argv)
{   Create_Points();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(500,500);
	glutCreateWindow("Exam problem");
	myInit();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
	}
