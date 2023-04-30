#include <windows.h>
#include<GL/glut.h>
#include<stdio.h>
#include <time.h>
#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACK 4
#define HIGH 1
#define MEDIUM 2
#define LOW 3
#define MENU1 1
#define MENU2 2

float angle = 0.0, inc=0.1; //changed by the menus
float red=0.0, blue=0.0, green=0.0;
int swidth=500, sheight=500;
int menu1, menu2;
bool flag;// indicated whether the menu is in use
int cur_menu=1;//current menu

void output_Text(float x, float y, float z, char *text) //output a text at x,y
{
    int len, i,ii;
    glRasterPos3f(x, y, z);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
}
void Output_CurMenu(int menu)
{
    glColor3f(0,0,0);
    switch (menu)
    {
    case MENU1:
        output_Text(0.0,1.4,0,"Color menu");
        break;
    case MENU2:
        output_Text(0.0,1.4,0,"Speed menu");
        break;
    }
    output_Text(0.0,1.5,0,"F1- switch the menus");
}
void Init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,float(swidth)/float(sheight),0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,3.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

}
void Display_TeaPot(void)
{
    glColor3d(red,green,blue); // the rgb color
    glPushMatrix();
    glRotated(angle,0,1,1);
    glutWireTeapot(1.0); // the teapot
    glPopMatrix();
}
void myDisplay(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Display_TeaPot();
    angle=angle+inc;
    Output_CurMenu(cur_menu);
    glutSwapBuffers();
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
        inc=0.01;
        break;
    case MEDIUM:
        inc=0.5;
        break;
    case HIGH :
        inc=1;
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
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    menu2 = glutCreateMenu(process_Menu_Speed);
    glutAddMenuEntry("Low",LOW);
    glutAddMenuEntry("Medium",MEDIUM);
    glutAddMenuEntry("High",HIGH);
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
    if ((c == GLUT_KEY_F1)&&(!flag)) // F1 pressed and menu is not in use
    {
        cur_menu = glutGetMenu();//which menu is in use ?
        switch(cur_menu)
        {
        case MENU1:
            glutSetMenu(menu2);
            cur_menu=menu2;
            break;
        case MENU2:
            glutSetMenu(menu1);
            cur_menu=menu1;
            break;
        }
        glutAttachMenu(GLUT_RIGHT_BUTTON);// attach the menu to the mouse button

    }

}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(swidth,sheight);
    glutCreateWindow("Example 4. Swap two menus");
    Init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    glutMenuStatusFunc(processMenuStatus);
    glutSpecialFunc(processSpecialKeys);
    createGLUTMenus();
    glutMainLoop();
}
