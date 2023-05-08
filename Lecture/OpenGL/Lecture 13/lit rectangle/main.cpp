#include <windows.h>
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

int w=500, h=500;
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 1.0, 0.0 };
GLfloat DiffuseLight[4]= {1,1,1.0,0};
GLfloat light_position[] = {0.0, 5.0, 0.0, 1.0 };
float angle=0;
GLfloat ax[3]= {5,0,0};
GLfloat ay[3]= {0,5,0};
GLfloat az[3]= {0,0,5}; //axes
// auxiliary functions to plot axes
void plot_Arrow(GLfloat v1[3], GLfloat v2[3]) //plot arrow
{
    glPointSize(10);
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(GLfloat v[3]) //plot vector
{
    GLfloat zero[3]= {0,0,0};
    plot_Arrow(zero,v);
}
void plot_Axis()
{
    glColor3f(1,0,0);
    plot_Vector(ax);
    glColor3f(0,1,0);
    plot_Vector(ay);
    glColor3f(0,0,1);
    plot_Vector(az);
}
void displayRectangle()
{
    glPushMatrix();
    glTranslated(1, 0, 0);
    glRotated(angle,0,0,1);

    glPointSize(10);

    glColor4fv(diffuseMaterial);

    glBegin(GL_QUADS);//normals and points

    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glNormal3f(0, 1, 0);//
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glEnd();

    glPopMatrix();
}
void initlights(void)
{
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
}
void display_Light_Source(GLfloat Lp[4], GLfloat Lc[4])//light position and light color
{
    // display the light source
    if (Lp[3]==1.0) //shows the source only if the light is positional
    {
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslatef(Lp[0],Lp[1],Lp[2]);
        glColor4f(0,0,0,0);//changed to black
        glutWireSphere(0.25,10,10);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
}
void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    displayRectangle();
    display_Light_Source(light_position,DiffuseLight);
    plot_Axis();
    glutSwapBuffers();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5, 5, -5,5,-5, 5);
    gluLookAt(1,1,1,0,0,0,0,1,0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Example 4. Lit rectangle with normals.");
    initlights();
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}
