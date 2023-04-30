#include<windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include <time.h>
#define RED 1 //these are numbers denoted RED, GREEN, BLUE, BLACK for convenience
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define TRANSPARENT 5
#define SOLID 6
GLfloat alpha=0.4;
float angle = 0.0, dangle=0.05;
float red=0.0, green=0.0, blue=0.0;//variables changed by the menu
int swidth=500,sheight=500;
float ratio= (float)swidth/(float)sheight;
void output_Text(float x, float y, float z, char *text) //output a text at x,y
{
    int len, i;
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}

void Display_TeaPot()
{
    glColor3d(0,0.0,0.0); // the rgb color+transparency
    glutWireSphere(0.3,20,20);//sphere inside the teapot
    glColor4d(0.9,0.9,0.9,alpha); // the rgb color+transparency
    glPushMatrix();
    glRotated(angle,0,1,1); //rotate around 0,1,1
    glutSolidTeapot(1.0); // the teapot
    glColor4d(red,green,blue, alpha); // the rgb color
    glutWireTeapot(1.01); // the wire teapot is a bit bigger
    glPopMatrix();
    glutSwapBuffers();
}
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ratio,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,3.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    output_Text(-0.5,1.5,0,"Right click for the menu.");
    Display_TeaPot();
    angle+=dangle;
}
void processMenuEvents(int option) //option is the menu item # generated by the menu
{
    switch (option) //red green blue are global variables
    {
    case RED :
        red = 1.0;
        green = 0.0;
        blue = 0.0;
        break;
    case GREEN :
        red = 0.0;
        green = 1.0;
        blue = 0.0;
        break;
    case BLUE :
        red = 0.0;
        green = 0.0;
        blue = 1.0;
        break;
    case BLACK :
        red = 0.0;
        green = 0.0;
        blue = 0.0;
        break;
    case TRANSPARENT:
        alpha=0.5;
        break;
    case SOLID:
        alpha=1.0;
        break;
    }

}
void createGLUTMenus() //create menus
{
    int menu=glutCreateMenu(processMenuEvents);//call processMenuEvents on menu click
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    glutAddMenuEntry("SOLID",SOLID);
    glutAddMenuEntry("TRANSPARENT",TRANSPARENT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(swidth,sheight);
    glutCreateWindow("Example M1'. Transparent object");///ter the window is created
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    createGLUTMenus();
    glutMainLoop();
}