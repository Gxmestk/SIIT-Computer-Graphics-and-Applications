#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
GLfloat x=1.0,y=1.0,z=1.0;
GLfloat lx=0.0,ly=0.0,lz=0.0;
float ni=25, nj=25;
GLfloat angle=0, inc_angle=0.01;
GLfloat ratio;
bool rotate=false;
GLfloat increment=0.1, angleincrement=0.01;//increments for changing the camera position
GLfloat diffuseMaterial[4] = {0.0, 0.0, 1.0, 0.0 };
GLfloat DiffuseLight[4]= {1,1,1.0,0};
GLfloat light_position[] = {0.0, 10.0, 10.0, 1.0 };
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0 };
void output_Text(float x, float y, char *text)
{
    int len, i;
    glPushMatrix();
    glRotated(45,0,1,0);
    glRasterPos3f(x, y, 0);
    len = (int)strlen(text);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
    }
    glPopMatrix();
}
void initlights(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
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
    gluPerspective(90,ratio,1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z,
              lx,ly,lz,
              0.0,2.0,0.0);

}
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
float nx(float u,float v)
{
    return -2*u;
}
float ny(float u,float v)
{
    return 1;
}
float nz(float u,float v)
{
    return 2*v;
}
void initScene()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_FLAT);
}
float a=-1, b=1; //interval for u and v
float stepi=(b-a)/(ni-1),
      stepj=stepi;
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
            ui=a+i*stepi;
            vj=a+j*stepj;
            uip1=a+(i+1)*stepi;
            vjp1=a+(j+1)*stepj;
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
//draw quads with the normals
            glColor4fv(diffuseMaterial);
            glBegin(GL_QUADS);
            glNormal3f(nx(ui,vj),ny(ui,vj),nz(ui,vj));
            glVertex3f(xij,yij,zij);
            glNormal3f(nx(uip1,vj),ny(uip1,vj),nz(uip1,vj));
            glVertex3f(xip1j,yip1j,zip1j);
            glNormal3f(nx(uip1,vjp1),ny(uip1,vjp1),nz(uip1,vjp1));
            glVertex3f(xip1jp1,yip1jp1,zip1jp1);
            glNormal3f(nx(ui,vjp1),ny(ui,vjp1),nz(ui,vjp1));
            glVertex3f(xijp1,yijp1,zijp1);
            glEnd();
//draw normals
            float alpha=0.1; //length of the normal
            glColor3f(1,0,0);
            glBegin(GL_LINE_LOOP);
            glVertex3f(xij,yij,zij);
            glVertex3f(xij+alpha*nx(ui,vj),yij+alpha*ny(ui,vj),zij+ alpha*nz(ui,vj));
            glEnd();
        }
    }
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotated(angle,0,1,0);
    displaySurface();
    glPopMatrix();
    if (rotate)
        angle=angle+inc_angle;
    output_Text(-7, -5, "R-rotate, S-stop");
    glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
    case 'R':
        rotate=true;
        break;
    case 's':
    case 'S':
        rotate=false;
        break;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,360);
    glutCreateWindow("Example 6 Parametric Surface");
    initlights();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(changeSize);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return(0);
}
