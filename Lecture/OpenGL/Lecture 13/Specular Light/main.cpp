#include <windows.h>
#include <GL/glut.h>

GLfloat swidth=500, sheight=500;

GLfloat ax[3]= {5,0,0};
GLfloat ay[3]= {0,5,0};
GLfloat az[3]= {0,0,5}; //axes

GLfloat light_position[] = {0.0, 0.0, 4.0, 1};// position of the light

GLfloat Light[] = {1.0, 1.0, 1.0, 0.0}; //white light

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };

GLfloat ColorTeapot[]= {1,0,1}; //purple
GLfloat ColorSphere[]= {0,1,0}; //green

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
    if (Lp[3]==1.0) //shows the source only if the light is positional
    {
        glPushMatrix();
        glTranslatef(Lp[0],Lp[1],Lp[2]);
        if ((Lp[0]==1) and (Lp[1]==1) and (Lp[3]==1))
            glColor4f(0,0,0,0);
        else
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
    gluLookAt(5.0,5.0,5.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    plot_Axis();
    glutSwapBuffers();
}
void initlights(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //set up the light position
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light);//this sets the diffuse light
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light);//this sets the ambient light

    glEnable(GL_LIGHTING);//enable lighting
    glEnable(GL_LIGHT0); //enable light 0

    glEnable(GL_DEPTH_TEST);//enables the depth buffer:

    glColorMaterial(GL_FRONT, GL_DIFFUSE);//diffuse light is reflected by the front face

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_COLOR_MATERIAL);//enable reflection by material

    glShadeModel(GL_SMOOTH);//smooth shades
}
void display(void)
{
    glColor3fv(ColorTeapot);//purple teapot
    glutSolidTeapot(1.5);
    display_Light_Source(light_position,Light);
    glPushMatrix();
    glTranslated(0,3,2);
    glColor3fv(ColorSphere);//green sphere 2
    glutSolidSphere(0.5,15,15);
    glPopMatrix();
    plot_Axis();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Example 2. Specularity");
    init();
    initlights ();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
