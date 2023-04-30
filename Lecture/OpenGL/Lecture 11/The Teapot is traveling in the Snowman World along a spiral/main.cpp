#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

const GLfloat Pi=3.1415926535;
GLfloat ratio1=1.33;
GLfloat x=0.0,y=0.1,z=5.0;
GLfloat lx=0.0,ly=0.0,lz=-1.0,angle=0;//position and orientation of the camera
GLfloat increment=0.1, angleincrement=0.01;//increments for changing the camera position
GLfloat ang=0, sangleincrement=1;//angle and increment for revolving the sphere and the torus
GLfloat R=0.5;

void Time_Delay(int dur)
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}
float t1=-120,dt1=0.01; //the trajectory parameters (spiral)
GLfloat trajectoryx(GLfloat t) //spiral trajectory
{
    return sin(t);
}
GLfloat trajectoryy(GLfloat t)
{
    return cos(t);
}
GLfloat trajectoryz(GLfloat t)
{
    return t/10;
}
void DrawTrajectory()
{
    GLfloat xt,yt,zt,t,dt;
    glColor3d(0,0,1);
    dt=0.1;
    glPointSize(5);
    glBegin(GL_LINE_STRIP);
    for (t=-120; t<=120; t=t+dt)
    {
        xt=trajectoryx(t);
        yt=trajectoryy(t);
        zt=trajectoryz(t);
        glVertex3d(xt,yt,zt);
    }
    glEnd();
}
void Display_TeaPot() //travelling teapot
{
    float r,g,b,xt,yt,zt;
    r=1;
    g=0;
    b=1;
    t1=t1+dt1;//increment t1
    glColor3d(r,g,b);
    xt=trajectoryx(t1);
    yt=trajectoryy(t1);
    zt=trajectoryz(t1);
    glPushMatrix();
    glTranslated(xt,yt,zt); //follow the trajectory
    glutWireTeapot(1.0); // the teapot
    glPopMatrix();
    Time_Delay(1);
}
void changeSize(GLint w, GLint h) //window resize
{
    if(h == 0)
        h = 1;
    ratio1 = 1.0 * w / h; // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);// Set the viewport to be the entire window
    gluPerspective(45,ratio1,1,1000); // Set the clipping volume
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
              x + lx,y + ly,z + lz,
              0.0,1.0,0.0);

}
void Draw_Magic_Ball(void)
{
    glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(-2,R,0); //position of the sphere
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
    glColor3f(0.9, 0.9, 0.9);// Draw Body !!!!
    glTranslatef(0.0,0.75, 0.0);
    glutSolidSphere(0.75,20,20);
    glTranslatef(0.0, 1.0, 0.0);// Draw Head
    glutSolidSphere(0.25,20,20);
    glPushMatrix();// Draw Eyes
    glColor3f(0.0,0.0,0.0);
    glTranslatef(0.05, 0.10, 0.18);
    glutSolidSphere(0.05,10,10);
    glTranslatef(-0.1, 0.0, 0.0);
    glutSolidSphere(0.05,10,10);
    glPopMatrix();// Draw Nose
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
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawGround();// Draw different objects
    Draw_Magic_Ball();
    DrawDonut();
    Draw36SnowMan();
    DrawTrajectory();//teapot trajectory
    Display_TeaPot();//teapot
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
