#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define HIGH 1
#define MEDIUM 2
#define LOW 3
#define TEAPOT 1
#define SPHERE 2
#define CUBE 3
#define MENU1 1
#define MENU2 2
#define MENU3 3

GLfloat ratio;
GLfloat x=0.0,y=0,z=3.0;//eye coordinates
GLfloat angle=0, inc_angle=0.1; //rotation angle
GLfloat red=1, green=0, blue=0;
bool flag;//menu is in use
int menu1, menu2, menu3, cur_menu;
GLint object=1;//1- teapot, 2 -sphere, 3 -cube

void output_Text(float x, float y, char *text)
{
    glColor3f(0, 0, 0);//text color red
    glRasterPos3f(x, y, 0);
    int len, i;
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}
void Output_CurMenu()
{
    if (cur_menu==menu1)
        output_Text(
            -1.0,
            -1.2,"Color menu");

    if (cur_menu==menu2)
        output_Text(
            -1.0,
            -1.2,"Speed menu");

    if (cur_menu==menu3)
        output_Text(
            -1.0,
            -1.2,"Object menu");

    output_Text(
        -1.0,-1.3,"F1- switch the menu");

}
void changeSize(GLsizei w, GLsizei h)
{
// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
    if(h == 0)
        h = 1;
    ratio = 1.0f * w / h;
// Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
// Set the clipping volume
    gluPerspective(60,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z
              ,
              x,y,z
              -
              1
              ,
              0.0,1.0,0.0);
}
void displayObject()
{
    glPushMatrix();
    glRotated(angle,0,1,0);
    glColor3f(red,green,blue);
    switch(object)
    {
    case TEAPOT:
        glutWireTeapot(1);
        break;
    case SPHERE:
        glutWireSphere(1,20,20);
        break;
    case CUBE:
        glutWireCube(1.5);
        break;
    }
    glPopMatrix();
}
void display(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    displayObject();
    Output_CurMenu();
    angle+=inc_angle;
    glutSwapBuffers();
}
void Do_Nothing()
{
}
void process_Menu_Color(int option)
{
    switch (option)
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
    }

}
void process_Menu_Speed(int option)
{
    switch (option)
    {
    case LOW :
        inc_angle=0.1;
        break;
    case MEDIUM:
        inc_angle=0.5;
        break;
    case HIGH :
        inc_angle=0.8;
        break;

    }
}
void process_Menu_Object(int option)
{
    switch (option)
    {
    case TEAPOT :
        object=1;
        break;
    case SPHERE :
        object=2;
        break;
    case CUBE :
        object=3;
        break;
    }
}
void createGLUTMenus()
{
    menu1=glutCreateMenu(process_Menu_Color);
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("Black",BLACK);
    menu2=glutCreateMenu(process_Menu_Speed);
    glutAddMenuEntry("Low",LOW);
    glutAddMenuEntry("Medium",MEDIUM);
    glutAddMenuEntry("High",HIGH);
    menu3=glutCreateMenu(process_Menu_Object);
    glutAddMenuEntry("TeaPot",TEAPOT);
    glutAddMenuEntry("Sphere",SPHERE);
    glutAddMenuEntry("Cube",CUBE);
    cur_menu=menu3;
    glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void processMenuStatus(int status, int x, int y)
{
    if (status == GLUT_MENU_IN_USE)
        flag = true;
    else
        flag = false;
//check whether the menu is in use
// if it is in use you can not swap between them
}
void processSpecialKeys(int c, int x, int y)
{
    if ((c == GLUT_KEY_F1)&&(!flag)) // F1 pressed and a menu is not in use
    {
        cur_menu = glutGetMenu();// which menu is in use ?
        switch(cur_menu)
        {
        case MENU3:
            glutSetMenu(menu2);
            cur_menu=menu2;
            break;
        case MENU2:
            glutSetMenu(menu1);
            cur_menu=menu1;
            break;
        case MENU1:
            glutSetMenu(menu3);
            cur_menu=menu3;
            break;
        }
        glutAttachMenu(GLUT_RIGHT_BUTTON);// attach the menu to the mouse button
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(600,600);
    glutCreateWindow("Example M5");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(changeSize);
    glutMenuStatusFunc(processMenuStatus);
    glutSpecialFunc(processSpecialKeys);
    createGLUTMenus();
    glutMainLoop();
    return(0);
}
