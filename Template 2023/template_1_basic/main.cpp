#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#define RED 0
#define BLUE 99
#define ROTATE 2
#define STOP 3
#define ZOOMIN 4
#define ZOOMOUT 5


bool text=true;
GLfloat red=1, green=0, blue=0;
GLfloat angle=0, dangle=0.0;
GLfloat zoom=60., dz=10.;
GLfloat ColorR=1, ColorG=0,ColorB=0;
bool flag;

void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while ((clock() - start_time) < dur)
    {
    }
}

void output_Text(float x, float y, float z, char *text) //output a text at x,y,z
{
    int len, i;
    glColor3f(0, 0, 0); //black text
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void output_Number(float x, float y, float z, double v) //output a number at x,y
{
    int len, i;
    char text [20]= {'\0'};
    sprintf(text, "%lf", v); //converts v to the string "text"
    output_Text(x,y,z,text);
}

void myInit2d(void)
{
    glClearColor(1.0,1.0,1.0,0.0);     // set white background color
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluOrtho2D(-50.0, 50.0, -50.0, 50.0);//set your coordinate system
    //the coordinate system and window in your assigment can be different
    glMatrixMode(GL_MODELVIEW);       //set some additional parameters
    glLoadIdentity();
}

void myInit3d(void)
{
    glClearColor(1,1,1,0);
    glColor3f(1.0, 0.0, 0.0);          // set the drawing color red
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // reset the Current Modelview Matrix
    gluPerspective(zoom, 1.0, .01, 1000);
    //the coordinate system, the window and glLookAt in your assignment can be totally different
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(40.0, 40.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void draw_Origin()
{
    glColor3f(0,0,0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(0,0,0);
    glEnd();
}

void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(ColorR,ColorG,ColorB);

    glPushMatrix();
    glTranslated(20,20,0);
    glRotated(angle,0,0,1);
    glRecti(-5,-5,5,5);//draw a red rectangle
    glPopMatrix();
    angle+=dangle;
    glColor3f(0.9, 0.9, 0.9);
    glutSolidTeapot(15.0);  //draw the teapot again as the wireframe
    glColor3f(red, green, blue);          // set the drawing color
    glutWireTeapot(15.0);  //draw the wireframe teapot
    output_Text(-250,-240,15,"Right click for the menu. F1-color of the rect");
    draw_Origin();
    glutSwapBuffers();
    Time_Delay(50);
}
void doNothing(void)
{
}
// reshape callback
void myReshape (int w, int h)
{

}
//mouse callback
void myMouse(int button, int state, int x, int y)
{
}
// keyboard callback
void myKeyboard(unsigned char key, int x, int y)
{
}

// motion callback
void myMotion(int x, int y)
{
}

void SpecialKeys(int key, int x, int y)
{
    if ((key == GLUT_KEY_F1)&&(!flag))
    {
        ColorR=1-ColorR;
    }
}

void Menu_Color(int option)
{
    switch (option)
    {
    case RED:
        red=1;
        green=0;
        blue=0;
        break;
    case BLUE:
        red=0;
        green=0;
        blue=1;
        break;
    case ROTATE:
        dangle=1.0;
        break;
    case STOP:
        dangle=0.0;
        break;
    case ZOOMIN:
        zoom-=dz;
        myInit3d();
        break;
    case ZOOMOUT:
        zoom+=dz;
        myInit3d();
        break;
    default:
        break;
    }
}
void createGLUTMenus()
{
    int menu = glutCreateMenu(Menu_Color);
    glutAddMenuEntry("Teapot Red",RED);
    glutAddMenuEntry("Teapot Blue",BLUE);
    glutAddMenuEntry("Stop Rect",STOP);
    glutAddMenuEntry("Rotate Rect",ROTATE);
    glutAddMenuEntry("Zoom in",ZOOMIN);
    glutAddMenuEntry("Zoom out",ZOOMOUT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void processMenuStatus(int status, int x, int y)
{
    //flag=true -> menu is in use
    if (status == GLUT_MENU_IN_USE)
        flag = true;
    else
        flag = false;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("OpenGL template");
    /* Use myInit2d() or myInit3d() for initialization */
    //.myInit2d();
    myInit3d();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glutIdleFunc(myDisplay);
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);
    glutMotionFunc(myMotion);
    createGLUTMenus();
    glutMenuStatusFunc(processMenuStatus);
    glutSpecialFunc(SpecialKeys);
    glutMainLoop();
}

