#include<windows.h>
#include <GL\glut.h>
#include <math.h>

GLfloat t=0, dt=0.01,angle=0, dangle=1, tmax=50;

void myInit3d(void)
{
    //9 lines
    glClearColor(1,1,1,0);
    glColor3f(0.0, 0.0, 0.0);          // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0.01, 1000);
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(80.0, 50.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

float trajectoryx(float t)
{
    //1~3 lines
    return t;
}

float trajectoryy(float t)
{
    //1~3 lines
    return 10*sin(t)+t;
}
float trajectoryz(float t)
{
    //1~3 lines
    return t;
}
void DrawPoint(GLint x, GLint y, GLint z)
{
    //5 lines
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(6);
    glBegin(GL_POINTS);
    glVertex3i(x,y,z);
    glEnd();
}

void Draw_Axis() //draw the coordinate axes
{
    //8~10 lines
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(40,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,40,0);
    glVertex3f(0,0,0);
    glVertex3f(0,0,40);
    glEnd();
}

void drawTrajectory(void) // draw the trajectory
{
    //10-12 lines
    float t, dt,x,y,z;
    dt=0.01;
    glBegin(GL_LINE_STRIP); // draw f(x)
    for (t = 0; t < tmax; t= t+dt)
    {
        x=trajectoryx(t);
        y=trajectoryy(t);
        z=trajectoryz(t);
        glVertex3f(x,y,z);
    }
    glEnd();
}

void draw_TeaPot(void)
{
    int i;
    glColor3f(0.8,0.8,0.9);
    glutSolidTeapot(8);
    glColor3f(0,0,0);
    glutWireTeapot(8);
}

void Move_TeaPot()
{
    //6-8 lines
    glPushMatrix();
    glTranslated(trajectoryx(t),trajectoryy(t),trajectoryz(t));
    glRotated(angle,0,1,0);
    draw_TeaPot();
    DrawPoint(0,0,0);
    glPopMatrix();
    DrawPoint(0,0,0);
}

void myDisplay(void)
{
    //7-8 lines
    glClear(GL_COLOR_BUFFER_BIT);
    t=t+dt;
    angle=angle+dangle;
    drawTrajectory();
    Draw_Axis();
    Move_TeaPot();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);          // 8 lines
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500);     // set window size
    glutInitWindowPosition(50, 50); // set window position on screen
    glutCreateWindow("Problem 4"); // open the screen window
    glutDisplayFunc(myDisplay); //register the display function
    glutIdleFunc(myDisplay);     // register the mouse event function
    myInit3d();                              //initialize settings
    glutMainLoop(); 	        // go into the perpetual loop
}
