#include <windows.h>
#include <GL/glut.h>
GLfloat swidth=500, sheight=500;
GLfloat ax[3]= {5,0,0};
GLfloat ay[3]= {0,5,0};
GLfloat az[3]= {0,0,5}; //axes
GLfloat light_position[] = {0.0, 0.0, 1.5, 1.0};// position of the light 0-no position
GLfloat Light[] = {0.0, 0.0, 1.0, 0.0}; //color of the light (blue)
GLfloat LightD[]= {0,0,0,0}; //no diffuse light
GLfloat ColorS[]= {1,1,1}; //color of the sphere
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
void display_Light_Source(GLfloat Lp[4], GLfloat Lc[4])//light position and light color
{
    // display the light source
    if (Lp[3]==1.0) //shows the source if the light is positional- dummy source
    {
        glPushMatrix();
        glTranslatef(Lp[0],Lp[1],Lp[2]);
        glColor4fv(Lc);
        glutWireSphere(0.25,10,10);
        glPopMatrix();
    }
}
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,swidth/sheight,0.1,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0, 0.0,0.0,0.0,0.0,1.0,0.0);
    glClearColor (1.0, 1.0, 1.0, 0.0);
}
void initlights(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set up the light position
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightD);//this the diffuse light=black
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light);//this sets the ambient light
    glEnable(GL_LIGHTING);//enable lighting
    glEnable(GL_LIGHT0); //enable light 0
    glEnable(GL_DEPTH_TEST);//the depth test
    glColorMaterial(GL_FRONT, GL_AMBIENT);//the light is reflected by the front face
    glEnable(GL_COLOR_MATERIAL);//enable reflection by material
    glShadeModel(GL_SMOOTH);//smooth shades
}
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3fv(ColorS);//white sphere
    glutSolidSphere(1,15,15);
    display_Light_Source(light_position,Light);
    plot_Axis();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Example 1. Ambient Light");
    init();
    initlights ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
