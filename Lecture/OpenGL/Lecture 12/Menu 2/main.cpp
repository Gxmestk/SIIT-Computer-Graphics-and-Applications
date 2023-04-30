#include<windows.h>
#include<GL/glut.h>
#define RED 1
#define GREEN 2
#define BLUE 3
#define WHITE 4
#define HIGH 1
#define MEDIUM 2
#define LOW 3

float angle = 0.0, dangle=0.05;
float red=0.0, blue=0.0, green=0.0;
int swidth=500, sheight=500;
float ratio= (float) swidth/ sheight;

void Init(void)
{
    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ratio,0.1,1000);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Display_TeaPot();
    angle+=dangle;
    glutSwapBuffers();
}
void processMenuEvents(int option)
{
    switch (option)
    {

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
    case WHITE :
        red = 1.0;
        green = 1.0;
        blue = 1.0;
        break;

    }
}
void Menu_Red_Intensity(int option)
{
    switch (option)
    {

    case HIGH :
        red = 1.0;
        green = 0.0;
        blue = 0.0;
        break;
    case MEDIUM :
        red = 0.5;
        green = 0.0;
        blue = 0.0;
        break;
    case LOW :
        red = 0.25;
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
        dangle=0.1;
        break;
    case MEDIUM:
        dangle=1;
        break;
    case HIGH :
        dangle=10;
        break;
    }

}
void createGLUTMenus()
{
    int submenu1 = glutCreateMenu(Menu_Red_Intensity);
    glutAddMenuEntry("High",HIGH);
    glutAddMenuEntry("Medium",MEDIUM);
    glutAddMenuEntry("Low", LOW);

    int submenu2 = glutCreateMenu(process_Menu_Speed);
    glutAddMenuEntry("Low",LOW);
    glutAddMenuEntry("Medium",MEDIUM);
    glutAddMenuEntry("High",HIGH);

    int menu=glutCreateMenu(processMenuEvents);
    glutAddSubMenu("Red",submenu1);
    glutAddSubMenu("Speed",submenu2);
    glutAddMenuEntry("Blue",BLUE);
    glutAddMenuEntry("Green",GREEN);
    glutAddMenuEntry("White",WHITE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(swidth,sheight);
    glutCreateWindow("Example 2. Menu and submenu.");
    Init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(myDisplay);
    createGLUTMenus( );
    glutMainLoop();
}
