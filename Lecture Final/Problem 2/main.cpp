#include <windows.h>
#include <GL/glut.h>
#include <math.h>

GLsizei screen_height = 500;
int px1=25, py1=25, px2=475, py2=475; // initial position of both squares complete this line
bool grab1=false, grab2=false;
unsigned char data[4];
float R=50;
unsigned char Red[3]= {255,0,0},Blue[3]= {0,0,255}, Black[3]= {0,0,0}, Purple[3]= {255,0,255};
float red[3]= {1,0,0}, blue[3]= {0,0,1}, black[3]= {0,0,0}, purple[3]= {1,0,1};
bool touch=false;//contact variable

void Circle(float R,float x, float y, float color[3]) //circle
{
    int i;
    int n=100;
    float step=2*M_PI/n;
    float t,x1,y1; //10-12 lines
    glColor3fv(color);
    glBegin(GL_TRIANGLE_FAN);
    for (i=0; i<=n; i++)
    {
        t=step*i;
        x1=x+R*cos(t);
        y1=y+R*sin(t);
        glVertex2f(x1,y1);
    }
    glEnd();
}

void Check_touch() //check contact
{
    if (sqrt(pow(px1-px2,2)+pow(py1-py2,2))<=2*R)
        touch=true;
    else
        touch=false;
}

void reDraw(void) // draw two 50x50 squares centered at (px1,py1) and (px2,py2)
{
    //appr 6 lines
    Check_touch();
    glClear(GL_COLOR_BUFFER_BIT);
    if (touch)
        Circle(R,px1,py1,red);
    else
        Circle(R,px1,py1,purple); //complete this line
    if (touch)
        Circle(R,px2,py2,black);
    else
        Circle(R,px2,py2,blue);////complete this line
    glutSwapBuffers();
}

void reShape(GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity( );
    gluOrtho2D(0.0, w, 0.0, h);
    screen_height = h;
    reDraw();
}

void myMove(int x, int y) // move a square that is grabbed
{
    if (grab1)
    {
        px1=x;
        py1=screen_height-y;
        reDraw();
    }
    else //appr 4 lines
        if (grab2)
        {
            px2=x;
            py2=screen_height-y;
            reDraw();
        }
}

void myRead(GLfloat x, GLfloat y) // check if a square is grabbed
{
    glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE, data);//read pixel
    grab1=false;
    grab2=false;
    if ((data[0]==Red[0])&& (data[1]==Red[1])&&(data[2]==Red[2]))
        grab1=true;
//3 lines here
    if (data[0]==Purple[0] && data[1]==Purple[1] && data[2]==Purple[2])
        grab1=true;
    if ((data[0]==Blue[0])&&(data[1]==Blue[1])&& data[2]==Blue[2])
        grab2=true;
    if ((data[0]==Black[0])&&(data[1]==Black[1])&& Black[2]==0)
        grab2=true;
}

void mouse(int button, int state, int x, int y)
{
    if (state== GLUT_DOWN)
        myRead(x,screen_height-y);
}

void Init(void)
{
    glClearColor(1, 1, 1, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Problem 2");
    Init();
//4 lines here
    glutDisplayFunc(reDraw);
    glutReshapeFunc(reShape);
    glutMouseFunc(mouse);
    glutMotionFunc(myMove);
    glutMainLoop();
}
