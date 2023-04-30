#include <windows.h>
#include <GL\glut.h>
#include <time.h>
#include <math.h>
#define XAXIS 1
#define YAXIS 2
#define ZAXIS 3
#define REVERSE 4
#define START 5
#define STOP 6


float angle=0,dangle=0.1, dangleold=0.1;//the rotation angle
float xa=1, ya=0, za=0; //the current rotation axis
void DrawPoint(GLint x, GLint y)
{
    glColor3f(0.0, 0.0, 1.0); // set the drawing color blue
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); // set white background color
    glMatrixMode(GL_PROJECTION); //set some additional parameters
    glLoadIdentity();
    gluOrtho2D(-30, 30.0, -30, 30.0);//set your coordinate system
    glMatrixMode(GL_MODELVIEW); //set some additional parameters
    glLoadIdentity();
}
void myInit3d(void)
{
    glClearColor(1,1,1,0);//clear color= white
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current MODELVIEW Matrix
    gluPerspective(30, 1, .01, 1000);
//the coordinate system, the window and glLookAt in your assignment
//can be different or you will design them yourself
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(30.0, 30.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void Time_Delay(GLint dur) //time delay
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}
float zero[3]= {0,0,0};
float ax[3]= {10,0,0};
float ay[3]= {0,10,0};
float az[3]= {0,0,10}; //axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3]) //plot vector
{
    plot_Arrow(zero,v);
}
void plot_Axis()
{
    glColor3f(0,0,0);
    plot_Vector(ax);
    plot_Vector(ay);
    plot_Vector(az);
}
void Draw_Rect(void)
{
    int i;
    glColor3f(1,0,0); //rectangle 10x10
    glRecti(-5,-5,5,5);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP); //border of the rectangle
    glVertex3f(-5,-5,0);
    glVertex3f(-5,5,0);
    glVertex3f(5,5,0);
    glVertex3f(5,-5,0);
    glEnd();
}
void Move_Rect()
{
    glPushMatrix();
    glRotated(angle,xa,ya,za); //rotation axis
    Draw_Rect();
    glPopMatrix();
}
void Draw_Cir(void)
{
    int i;
    float xr,yr;
    int Np=100;
    glColor3d(0,0,1);
    float R=5*sqrt(2); // radius = half of the diagonal of the rectangle
    glBegin(GL_LINES);
    for(i=0; i <= Np; i++) //draw the circle
    {
        xr=R*cos(2*M_PI/Np*i);
        yr=R*sin(2*M_PI/Np*i);
        glVertex2f(xr,yr);
    }
    glEnd();
}
void myDisplay(void) //animation
{
    glClear(GL_COLOR_BUFFER_BIT);
    Move_Rect();
    Draw_Cir();
    angle=angle+dangle;
    plot_Axis();
    glutSwapBuffers();
    Time_Delay(5);
}
void Menu(int option)
{
    switch (option)
    {
    case XAXIS:
        xa=1;
        ya=0;
        za=0;
        break;
    case YAXIS:
        xa=0;
        ya=1;
        za=0;
        break;
    case ZAXIS:
        xa=0;
        ya=0;
        za=1;
        break;
    case REVERSE:
        dangle=-dangle;
        break;
    case STOP:
        dangleold=dangle;
        dangle=0;
        break;
    case START:
        if (dangleold!=0)
            dangle=dangleold;
        else
            dangle=0.1;
        break;//save the old angle
    }
}
void createGLUTMenus()
{
    int menu = glutCreateMenu(Menu);
    glutAddMenuEntry("x-axis",XAXIS);
    glutAddMenuEntry("y-axis",YAXIS);
    glutAddMenuEntry("z-axis",ZAXIS);
    glutAddMenuEntry("Reverse",REVERSE);
    glutAddMenuEntry("Start",START);
    glutAddMenuEntry("Stop",STOP);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("example 5"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
    glutIdleFunc(myDisplay); // register the mouse event function
    myInit3d();
    createGLUTMenus(); //initialize settings
    glutMainLoop(); // go into the perpetual loop
}
