#include <windows.h>
#include <GL/glut.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

float t1=0, dt1 =0.001, Tmax=20; //coordinate along the trajectory
int swidth=500, sheight=500; //window
bool move =false; // sphere moves or stops
int tred=1, tgreen=0, tblue=0;//sphere color
//screen text and axes drawing functions
void out_Text(float x, float y, float z, char* text)//prints text on the screen
{
    int k, len;
    glColor3f(0,0,0);
    len=strlen(text);//length of the string here you need <string.h>
    glRasterPos3f(x,y,z);//text output position
    for (k = 0; k <=len; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[k]);
}
float ax[3]= {5,0,0};
float ay[3]= {0,5,0};
float az[3]= {0,0,5}; //axes
void plot_Arrow(float v1[3], float v2[3]) //plot arrow
{
    glPointSize(10);
    glBegin(GL_LINES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glEnd();
}
void plot_Vector(float v[3]) //plot vector
{
    float zero[3]= {0,0,0};
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
void Time_Delay(GLint dur) //time delay
{
    clock_t start_time;
    start_time = clock();
    while((clock() - start_time) < dur )
    { }
}
void init(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5,5,-5,5,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0,1.0,1.0,
              0.0,0.0,0.0,
              0.0,1.0,0.0);

}
plot_Menu_Color()
{
    glPushMatrix();
    glRotated(45,0,1,0);//we need to rotate the text otherwise it look skewed
    glTranslated(4.5,4,1);
    glColor3f(1,0,0);
    glRectd(-2.5,-0.5,0.0,0.0); //red rectangle
    out_Text(-3.5,-0.5,0,"start");
    glColor3f(0,0,0);
    glTranslated(0,-0.5,0);
    glRectd(-2.5,-0.5,0.0,0.0); //black rectangle
    out_Text(-3.5,-0.5,0,"stop");
    glPopMatrix();
}
float sx(float t, float R) //the spiral
{
    return R*sin(t) ;
}
float sy(float t, float R)
{
    return t/10;
}
float sz(float t, float R)
{
    return R*cos(t);
}
void plot_Trajectory() //plot the spiral Rad=1
{
    float x,y,z,t,dt=0.01;
    glBegin(GL_LINE_STRIP);
    for(t = 0; t <=Tmax; t+=dt)
    {
        glColor3f(0.0, 0.0, 0.0);
        x = sx(t,1);
        y = sy(t,1);
        z = sz(t,1);
        glVertex3f(x,y,z);
    }
    glEnd();
}
void plot_Sphere() //translate along the spiral
{
    float x,y,z;
    x=sx(t1,1);
    y=sy(t1,1);
    z=sz(t1,1);
    glPushMatrix();
    glTranslatef(x,y,z);
    glColor3f(tred,tgreen,tblue);
    glutSolidSphere(1.0,20,20);
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(1.0+0.001,10,10);
    glPopMatrix();
}
void display_All()
{
    //display all at t1
    glPushMatrix(); // send the preceding transformation matrix to stack
    plot_Axis();
    plot_Trajectory();
    plot_Sphere();
    out_Text(-1.3,-4.55,3.8,"Left click on the red/black rectangle: start/stop");
    glPopMatrix();
}
void display(void) //animation if move=true
{
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    display_All();
    plot_Menu_Color();
    if (move)
        t1+=dt1;
    if (t1>Tmax)
        dt1=-dt1; //reverse
    if (t1<0)
        dt1=-dt1;
    glutSwapBuffers();
}
void my_Mouse(int button, int state, int x, int y1)
{
    unsigned char data[4];
    int y=500-y1;
    if ((button==GLUT_LEFT_BUTTON)&&(state == GLUT_DOWN))
    {
        //on left click read the pixel at x,y, red =data[0], green=data[1], blue= data[2]
// the color range is 0-255
        glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,data);
        if ((data[0]==255)&&(data[1]==0)&&(data[2]==0))
            move=true; //on red pixel
        if ((data[0]==0)&&(data[1]==0)&&(data[2]==0))
            move=false; //on black pixel
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Problem ");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutMouseFunc(my_Mouse);
    glutMainLoop();
    return 0;
}
