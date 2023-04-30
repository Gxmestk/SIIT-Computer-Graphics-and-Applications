#include <windows.h>
#include <GL/glut.h>
GLdouble angle = 0, dangle=20;
GLfloat position[] = { 0.0, 1.0, 0.0, 1.0 };// light position
GLfloat Light[] = {1.0, 1.0, 1.0, 0.0}; //white light

float ax[3]= {5,0,0};
float ay[3]= {0,5,0};
float az[3]= {0,0,5}; //axes

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
void plot_Arrow(float v1[3], float v2[3]) //plot arrows
{
    glPointSize(10);
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3]) //plot a vector
{
    float zero[3]= {0,0,0};
    plot_Arrow(zero,v);
}
void plot_Axis() //plot axes
{
    glColor3f(1,0,0);
    plot_Vector(ax);
    glColor3f(0,1,0);
    plot_Vector(ay);
    glColor3f(0,0,1);
    plot_Vector(az);
}
void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glShadeModel (GL_SMOOTH);
    glEnable(GL_LIGHTING);//enable lighting
    glEnable(GL_LIGHT0); //enable light 0
    glEnable(GL_DEPTH_TEST);
//enables the depth buffer: closer objects will obstruct objects located farther
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light);//this sets the
    glColorMaterial(GL_FRONT, GL_DIFFUSE);//diffuse light is reflected by the front face
    glEnable(GL_COLOR_MATERIAL);//enable reflection by material
    glEnable(GL_NORMALIZE);//automatically normalized normals
}
void display_Rectangle()
{
    float alpha=0.5;
    float v1[3]= {1, 0, -1};
    float v2[3]= {1, 0, 1};
    float v3[3]= {-1, 0, 1};
    float v4[3]= {-1, 0, -1};
    float n[3]= {0,1,0};
    glPushMatrix();
    glPointSize(10);
    glColor3f (0.0, 1.0, 0.0);//green
    glBegin(GL_QUADS);
    glNormal3fv(n);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v4);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3f(v1[0]+alpha*n[0],v1[1]+alpha*n[1], v1[2]+ alpha*n[2]);
    glVertex3fv(v2);
    glVertex3f(v2[0]+alpha*n[0],v2[1]+alpha*n[1], v2[2]+ alpha*n[2]);
    glVertex3fv(v3);
    glVertex3f(v3[0]+alpha*n[0],v3[1]+alpha*n[1], v3[2]+ alpha*n[2]);
    glVertex3fv(v4);
    glVertex3f(v4[0]+alpha*n[0],v4[1]+alpha*n[1], v4[2]+ alpha*n[2]);
    glEnd();
    glPopMatrix();
}
void Light_Rotation()
{
    glPushMatrix ();
    glRotated (angle, 1.0, 0.0, 0.0);//rotate the light
    glLightfv (GL_LIGHT0, GL_POSITION, position); //setup the light
    glTranslatef(position[0],position[1],position[2]);//translate the cube (not the light)
    glutSolidCube (0.1);//light indicator, shows the light position
    glPopMatrix ();
}
void display(void)
{
    glClearColor(1,1,1,0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Light_Rotation();
    display_Rectangle();
    plot_Axis();
    output_Text(-2, -3, "Right-left click - rotate the light.");
    glutSwapBuffers();
}
void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,4.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

}
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
        {
            angle += dangle;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
        {
            angle -= dangle;
        }
        break;
    default:
        break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Example 5. Rotated light");
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
