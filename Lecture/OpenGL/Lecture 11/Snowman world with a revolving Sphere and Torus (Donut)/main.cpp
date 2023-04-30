#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

GLfloat ratio=1.33;
GLfloat x=0.0,y=2.0,z=5.0;
GLfloat lx=0.0,ly=0.0,lz=-1.0,angle=0;//position and orientation of the camera
GLfloat increment=0.1, angleincrement=0.01;//increments for changing the camera position
GLfloat ang=0, sangleincrement=1;//angle and increment for revolving the sphere and the torus
GLfloat R=0.5;

void changeSize(GLint w, GLint h) //window resize
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
    glTranslatef(-2,1,0); //position of the sphere
    glRotatef(ang,0,1,0); //revolve the sphere
    glutWireSphere(R,50,50);
    glPopMatrix();
    ang=ang+sangleincrement;
}
void DrawDonut(void)
{
    glPushMatrix();
    glTranslated(2.4,1.2,-6);//position of the torus
    glRotated(ang,0,1,0); //revolve the torus
    glColor3f(1,0,0);
    glutWireTorus(0.2,0.8,20,20); //red wire torus
    glColor3f(0,0,1);
    glutSolidTorus(0.2,0.8,20,20);//blue solid torus at the same position
    glPopMatrix();
}
void DrawSnowMan()
{
    glColor3f(1.0, 1.0, 1.0f);
// Draw Body
    glTranslatef(0.0,0.75, 0.0f);
    glutSolidSphere(0.75,20,20);
// Draw Head
    glTranslatef(0.0f, 1.0, 0.0f);
    glutSolidSphere(0.25,20,20);
// Draw Eyes
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(0.05, 0.10, 0.18);
    glutSolidSphere(0.05,10,10);
    glTranslatef(-0.1, 0.0, 0.0);
    glutSolidSphere(0.05,10,10);
    glPopMatrix();
// Draw Nose
    glColor3f(1.0, 0.5, 0.5);
    glRotatef(0.0,1.0, 0.0, 0.0);
    glutSolidCone(0.08,0.5,10,2);
}
void Draw36SnowMan(void)
{
    for(int i = -3; i < 3; i++)

        for(int j=-3; j < 3; j++)
        {
            glPushMatrix();
            glTranslatef(i*10.0,0,j * 10.0);
            DrawSnowMan();
            glPopMatrix();
        }

}
void DrawGround(void)
{
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0, 100.0);
    glVertex3f( 100.0, 0.0, 100.0);
    glVertex3f( 100.0, 0.0, -100.0);
    glEnd();
}
void DrawWorld(void)
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawGround();
// Draw objects
    Draw_Magic_Ball();
    DrawDonut();
    Draw36SnowMan();
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
    glutSpecialFunc(inputKey);
    glutDisplayFunc(DrawWorld);
    glutIdleFunc(DrawWorld);
    glutReshapeFunc(changeSize);
    glutMainLoop();
    return(0);
}
