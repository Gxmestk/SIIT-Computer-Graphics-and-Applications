#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>

float angle=0,dangle=0; //fan rotation
float anglep=60, danglep=5; //zoom parameters
float ax[3]= {3,0,0};
float ay[3]= {0,3,0};
float az[3]= {0,0,3}; //axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3]) //plot vector
{
    float zero[3]= {0,0,0};
    plot_Arrow(zero,v);
}
void plot_Axis()
{
    glColor3f(0,0,0);
    plot_Vector(ax);
    plot_Vector(ay);
    plot_Vector(az);
}
void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0); // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluPerspective(anglep, 1, .01, 1000);//perspective view
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock()

            - start_time) < dur)
    {

    }
}
void line() //a line from (0,0,0) to (3,3,3)
 {
glColor3f(0,0,0);
glBegin(GL_LINE_STRIP);
glVertex3f(0,0,0);
glVertex3f(0,0,3);
glEnd();
}
void fan( )
{
    int a;
    glColor3f(1,0,0);
    glPushMatrix();
    glTranslatef(0,1,0);
    glLineWidth(3);
    for (a=0; a<=7; a++) //plot 8 radial lines each 45 degree
    {
        line();
        glRotatef(45,0,1,0);
    }
    glPopMatrix();
    glLineWidth(1);
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    plot_Axis();
    glPushMatrix();
    glRotatef(angle, 0, 1, 0);
    fan();
    glutSwapBuffers();
    glPopMatrix();
    angle=angle+dangle;
    Time_Delay(50);
}
void Do_Nothing(void)
{


}
void processNormalKeys(unsigned char key, int x, int y) //Zoom !
{
    switch (key)
    {
    case '+':
        anglep-=danglep;
        break;
    case '-':
        anglep+=danglep;
        break;
    }
    myInit3d(); //we need reinitialize gluPerspective
}
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            dangle=1;
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            dangle=0;
        break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(480, 480); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Fan"); // open the screen window
    glutDisplayFunc(myDisplay); //the display function
    glutIdleFunc(myDisplay);
    glutMouseFunc(mouse); // the mouse event function
    glutKeyboardFunc(processNormalKeys);
    myInit3d(); //initialize settings
    glutMainLoop(); // go into the perpetual loop
}
