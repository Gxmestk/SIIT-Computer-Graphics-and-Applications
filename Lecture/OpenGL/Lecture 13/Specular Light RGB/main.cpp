#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
int w=500, h=500;

GLfloat colorM[4] = { 0.0, 0.0, 0.0, 1.0 };//material color
GLfloat DiffuseLight[4]= {1,1,1,0};

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
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0 }; //specular light
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0 }; //directional diagonal light
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 25.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}
void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'r':
    case 'R':
        colorM[0] += 0.01;
        if (colorM[0] > 1.0)
            colorM[0] = 0.0;
        glColor4fv(colorM);
        break;
    case 'g':
    case 'G':
        colorM[1] += 0.01;
        if (colorM[1] > 1.0)
            colorM[1] = 0.0;
        glColor4fv(colorM);
        break;
    case 'b':
    case 'B':
        colorM[2] += 0.01;
        if (colorM[2] > 1.0)
            colorM[2] = 0.0;
        glColor4fv(colorM);
        break;
        break;
    default:
        break;
    }
    printf("red=%f, greed=%f, blue=%f\n",
           colorM[0],colorM[1],colorM[2]);
}
void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSolidSphere(1.0, 20, 16);
    output_Text(-1.3,-1.3,"Press R,G or B to change the material color");
    glutSwapBuffers();
}
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5,1.5,-10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor4fv(colorM);
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Example 3. Change the material color interactively.");
    initlights();
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return 0;
}
