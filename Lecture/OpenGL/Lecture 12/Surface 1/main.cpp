#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

GLfloat angle=0.0,ratio, angle2;//angle - camera, angle2- object(surface)
GLfloat x=0.0,y=0.0,z=3.0;
GLfloat lx=0.0,ly=0.0,lz=-1.0;
int ni=25, nj=25;//number of points for discretizing the surface
float a1=-1, b1=1;
float a2=-1, b2=1;
float stepi=(b1-a1)/(ni-1);
float stepj=(b2-a2)/(nj-1); // step in the u and v direction.
GLfloat increment=0.1, angleincrement=0.01;//increments for changing the camera position
bool text=true;//output the text on the screen
bool rotate=false;
GLfloat inc_angle2=0.1, mouse_angle2=5,inc_inc_angle2=0.01;

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
void changeSize(GLsizei w, GLsizei h)
{
// Prevent a divide by zero, when window is too short
// (you cant make a window of zero width).
    if(h == 0)
        h = 1;
    ratio = 1.0 * w / h;
// Reset the coordinate system before modifying
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
// Set the viewport to be the entire window
// Set the clipping volume
    gluPerspective(60,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx,y + ly,z + lz,
              0.0,1.0,0.0);

}

//surface components
float sx(float u,float v)
{
    return u;
}
float sy(float u,float v)
{
    return u*u-v*v;
}
float sz(float u,float v)
{
    return v;
}
void initScene()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_FLAT);
}
void displaySurface()
{
    int i, j;
    float ui,vj,uip1,vjp1;
    float xij,yij,zij;
    float xip1j,yip1j,zip1j;
    float xijp1,yijp1,zijp1;
    float xip1jp1,yip1jp1,zip1jp1;

    for (j = 0; j <= nj-1; j++)
    {
        for (i = 0; i <= ni-1; i++)
        {
            ui=a1+i*stepi;
            vj=a2+j*stepj;
            uip1=a1+(i+1)*stepi;
            vjp1=a2+(j+1)*stepj;
            xij=sx(ui,vj);
            yij=sy(ui,vj);
            zij=sz(ui,vj);
            xip1j=sx(uip1,vj);
            yip1j=sy(uip1,vj);
            zip1j=sz(uip1,vj);
            xip1jp1=sx(uip1,vjp1);
            yip1jp1=sy(uip1,vjp1);
            zip1jp1=sz(uip1,vjp1);
            xijp1=sx(ui,vjp1);
            yijp1=sy(ui,vjp1);
            zijp1=sz(ui,vjp1);
            glColor3f(0.9, 0.9, 0.9);//almost white
            glBegin(GL_QUADS); //solid surface
            glVertex3f(xij,yij,zij);
            glVertex3f(xip1j,yip1j,zip1j);
            glVertex3f(xip1jp1,yip1jp1,zip1jp1);
            glVertex3f(xijp1,yijp1,zijp1);
            glEnd();
            glColor3f(0.0, 0.0, 1.0);//blue wire
            glBegin(GL_LINE_LOOP);
            glVertex3f(xij,yij,zij);
            glVertex3f(xip1j,yip1j,zip1j);
            glVertex3f(xip1jp1,yip1jp1,zip1jp1);
            glVertex3f(xijp1,yijp1,zijp1);
            glEnd();
        }
    }
}

void display(void)// display function
{
    glClearColor(0.7,0.7,0.7,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (text)
        output_Text(-3,1.5,0,"Use left/right up/down arrows and pgup/pgdn to navigate. R-rotate, S-stop.");

    glPushMatrix();
    glRotated(angle2,0,1,0);
    displaySurface();
    glPopMatrix();
    if (rotate)
        angle2=angle2+inc_angle2;
    glutSwapBuffers();
}
void orientMe(float ang)
{
    lx = sin(ang);
    lz = -cos(ang);
    glLoadIdentity();
    gluLookAt(x, y, z,
              x+lx,y+ly,z+lz,
              0.0,1.0,0.0);

}
void moveMeFlat(float increment)
{
    x = x + lx*increment;
    z = z + lz*increment;
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx,y + ly,z + lz,
              0.0,1.0,0.0);

}
void moveMeUp(float increment)
{
    y=y-increment;
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx,y+ly,z + lz,
              0.0,1,0.0);

}
void inputKey(int key, int x, int y)
{
    //camera control
    text=false;//do not show the text anymore
    switch (key)
    {
    case GLUT_KEY_LEFT :
        angle -= angleincrement;
        orientMe(angle);
        break;
    case GLUT_KEY_RIGHT :
        angle +=angleincrement;
        orientMe(angle);
        break;
    case GLUT_KEY_UP :
        moveMeFlat(increment);
        break;
    case GLUT_KEY_DOWN :
        moveMeFlat(-increment);
        break;
    case GLUT_KEY_PAGE_UP:
        moveMeUp(increment);
        break;
    case GLUT_KEY_PAGE_DOWN:
        moveMeUp(-increment);
        break;
    }
}



void processNormalKeys(unsigned char key, int x, int y)
{
    text=false;
    switch (key)
    {

    case 'r':
    case 'R':
        rotate=true;
        inc_angle2=0.1;
        break;
    case 's':
    case 'S':
        rotate=false;
        inc_angle2=0.1;
        break;
    case 'a':
    case 'A':
        if (rotate)
            inc_angle2=inc_angle2+inc_inc_angle2;
        break;
    case 'd':
    case 'D':
        if (rotate)
            inc_angle2=inc_angle2-inc_inc_angle2;
        break;
    default:
        break;
    };
    if (inc_angle2<=0)
        inc_angle2=0.0;//D can not turn inc_angle2 to negative
//and rotate in a different direction)
}

void mouse(GLint button, GLint state, GLint x, GLint y)
{
    text=false;
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
            angle2=angle2+mouse_angle2;
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
            angle2=angle2-mouse_angle2;
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,360);
    glutCreateWindow("Example 1. Plot a parametric surface");
    glutSpecialFunc(inputKey);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);
    glutMouseFunc(mouse);
    glutMainLoop();
    return(0);
}
