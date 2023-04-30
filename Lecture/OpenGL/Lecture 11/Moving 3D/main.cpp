#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

GLfloat ratio=1.33;
GLfloat x=0.0,y=2.0,z=10.0;//original eye position
GLfloat lx=0.0,ly=0.0,lz=-1.0, angle=0;//original orientation
GLfloat increment=0.1, angleincrement=0.01;//increments on the position and orientation
GLfloat ang=0, sangleincrement=1;//for sphere
GLfloat R=2.5;//radius of the sphere

void output_Text(float x, float y, float z, char *text) //output a text at x,y
{
    int len, i;
    glColor3f(0, 0, 0); //black
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
    if(h == 0)
        h = 1;
    ratio = 1.0 * w / h;
// Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
// Set the clipping volume
    gluPerspective(45,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx,y + ly,z + lz,
              0.0,1.0,0.0);

}
void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}

void Draw_Magic_Ball(void)
{
    glPushMatrix();
    glColor3f(1,0,0);
    glRotatef(ang,0,1,0);
//glTranslatef(-2,1,0);
    glutWireSphere(R,50,50);
    glPopMatrix();
    ang=ang+sangleincrement;
}
void initScene()
{
    glEnable(GL_DEPTH_TEST);
}
void DrawWorld(void)
{
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    output_Text(-7,5.5,0,"Use left/right up and down arrows to navigate");
// Draw ground
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0, 100.0);
    glVertex3f( 100.0, 0.0, 100.0);
    glVertex3f( 100.0, 0.0, -100.0);
    glEnd();
// Draw objects

    Draw_Magic_Ball();
    Time_Delay(50);
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
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,360);
    glutCreateWindow("My First Virtual world 3D");
    initScene();
    glutSpecialFunc(inputKey);
    glutDisplayFunc(DrawWorld);
    glutIdleFunc(DrawWorld);
    glutReshapeFunc(changeSize);
    glutMainLoop();
    return(0);
}
