#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include <time.h>
#define RED 1
#define BLUE 2
#define STOP 3
#define START 4
#define BLACK 5

bool flag=false;
int menu_cur=1;
float angle = 0.0, dangle=0.05;
float red=0.0, green=0.0, blue=0.0;
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
void output_Menu(int menu)
{
    switch(menu)
    {
    case 1:
        output_Text(-0.5,1.4,0,"Menu 1");
        break;
    case 2:
        output_Text(-0.5,1.4,0,"Menu 2");
        break;
    case 3:
        output_Text(-0.5,1.4,0,"Menu 3");
        break;
    }
}
void Display_TeaPot()
{
    glColor3d(red,green,blue); // the rgb color
    glPushMatrix();
    glRotated(angle,0,1,1); //rotate around 0,1,1
    glutWireTeapot(1.0); // the teapot
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
    output_Menu(menu_cur);
    Display_TeaPot();
    angle+=dangle;
}
void processMenuEvents(int option) //option is the menu item # generated by the menu
{
    switch (option) //all options are here
    {
    case RED :
        red = 1.0;
        green = 0.0;
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
    case STOP :
        dangle=0;
        break;
    case START :
        dangle=0.05;
        break;

    }

}
void processMenuStatus(int status, int x, int y) //check whether the menu is in use
{
    if (status == GLUT_MENU_IN_USE)
        flag = true;
    else
        flag = false;

}
void SpecialKeys(int c, int x, int y)
{
    if ((c == GLUT_KEY_F1)&&(!flag)) // F1 pressed and the menu is not in use
    {
        glutChangeToMenuEntry(1,"Red",RED);
        glutChangeToMenuEntry(2,"Blue",BLUE);
        while (glutGet(GLUT_MENU_NUM_ITEMS)>2)//remove all menu items >2
            glutRemoveMenuItem(3);
        menu_cur=1;
    }
    if ((c == GLUT_KEY_F2)&&(!flag)) // F2 pressed and the menu is not in use
    {
        glutChangeToMenuEntry(1,"Red",RED);
        glutChangeToMenuEntry(2,"Blue",BLUE);
        glutAddMenuEntry("Stop",STOP); //3
        glutAddMenuEntry("Start",START);//4
        while (glutGet(GLUT_MENU_NUM_ITEMS)>4)
            glutRemoveMenuItem(5);//remove all menu items >4
        menu_cur=2;
    }
    if ((c == GLUT_KEY_F3)&&(!flag)) // F3 pressed and the menu is not in use
    {
        glutChangeToMenuEntry(1,"Black",BLACK);
        glutChangeToMenuEntry(2,"Red",RED);
        while (glutGet(GLUT_MENU_NUM_ITEMS)>2)//remove all menu items >2
            glutRemoveMenuItem(3);
        menu_cur=3;
    }
}
void createGLUTMenus() //create menus
{
    int menu=glutCreateMenu(processMenuEvents);//the initial menu
    glutAddMenuEntry("Red",RED);
    glutAddMenuEntry("Blue",BLUE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(swidth,sheight);
    glutCreateWindow("Example M0. Modifying the menu");
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutSpecialFunc(SpecialKeys);
    glutMenuStatusFunc(processMenuStatus);
    createGLUTMenus();
    glutMainLoop();
    return 0;
}