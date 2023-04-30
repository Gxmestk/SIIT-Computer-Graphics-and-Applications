#include <windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <stdio.h>

float ConvertX(int,int);
float ConvertY(int,int);
void Draw_Triangle(float, float, float, float color[]);
void Memo_Triangle(int, int, float, float color[]);
void Delete_Triangle();
void reDraw();
int wx=500,wy=500;
int memx[100];//keep cornerX here
int memy[100];//keep cornerY here
int memwx[100];//keep cornerX here
int memwy[100];//keep cornerY here
float memco[3][100];//keep color
int memc=0; //triangle counter
GLfloat minx=-1.,miny=-1.,maxx=1.,maxy=1.; // all coordinates are mapped onto [-1,1]x[-1,1]

void Memo_Triangle(int cornerX, int cornerY, float size, float color[])
{
    //memorize the triangle
    int i;
    printf("memorycounterMemo=%d\n",memc);
    if (memc<100)
    {
        memx[memc]=cornerX;
        memy[memc]=cornerY;
        memco[0][memc]=color[0];
        memco[1][memc]=color[1];
        memco[2][memc]=color[2];
        memwx[memc]=wx;
        memwy[memc]=wy;
        i=memc;
        printf("RGBmem=%f,%f,%f\n",memco[0][i],memco[1][i],memco[2][i]);
        memc++;
    }
}
void Delete_Triangle()
{
    //delete triangle
    if (memc!=0)
        memc--;
    reDraw();
}
void Draw_Triangle(float cornerX, float cornerY, float size, float color[])
{
    glBegin (GL_POLYGON);
    glColor3f (color[0], color[1],color[2]); // Set the drawing color to red.
    glVertex2f(cornerX,cornerY);
    glVertex2f(cornerX+size,cornerY);
    glVertex2f(cornerX+size/2,cornerY+size);
    glEnd ( );
}
void DoNothing(void)
{
}
void My_Drawing(float X, float Y, float Color[])
{
    Draw_Triangle(X,Y,0.3,Color);//draw the triangle
}
void reDraw()
{
    float mx,my;
//redraw all triangles
    int i;
    float colord[3];
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    printf("memorycounterRedraw=%d\n",memc);
    for (i=0; i<memc; i++)
    {
        printf("RGB=%f,%f,%f\n",memco[0][i],memco[1][i],memco[2][i]);
        colord[0]=memco[0][i];
        colord[1]=memco[1][i];
        colord[2]=memco[2][i];
        mx=ConvertX(memx[i],memwx[i]);
        my=ConvertY(memy[i],memwy[i]);
        Draw_Triangle(mx,my,0.3,colord);//draw the triangle
    }
    glutSwapBuffers();
}
float ConvertX(int x, int wx)
{
    float mx ;
//transform screen coordinates x,y into the math coordinates mx,my
    mx=maxx*x/wx+minx*(wx-x)/wx;
    return mx;
}
float ConvertY(int y, int wy)
{
    float my,y1;
    y1=wy-y;
    my=maxy*y1/wy+miny*(wy-y1)/wy;
    return my;
}
void mouse(int button, int state, int x, int y)
{
    float mx,my;
//on mouse click transform x,y into mx,my, draw and memorize the triangle
    float Color[3];
    if (button == GLUT_LEFT_BUTTON && state== GLUT_DOWN)
    {
//random color
        Color[0]=(float)(rand()%1000/1000.);
        Color[1]=(float)(rand()%1000/1000.);
        Color[2]=(float)(rand()%1000/1000.);
        Memo_Triangle(x,y,0.3,Color); //memorize the triangle
        mx=ConvertX(x,wx);
        my=ConvertY(y,wy);
    };
    if (button == GLUT_RIGHT_BUTTON && state== GLUT_DOWN)
        Delete_Triangle();
    reDraw();
}
void Reshape(GLint width, GLint height)   // GLsizei for non-negative integer
{
    if (height == 0)
        height = 1; // To prevent divide by 0
//keep the aspect ratio -----------------------------------
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
    {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
        minx=-1.0 * aspect;
        maxx=1.0 * aspect;
        miny=-1.0;
        maxy=1.0;
    }
    else
    {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
        minx=-1.0;
        maxx=1.0;
        miny=-1.0/aspect;
        maxy=1.0/aspect;
    }
//keep the aspect ratio -----------------------------------
    wx=width; //pass the width and height to main
    wy=height;
    reDraw();//redraw available triangles if the window has been resized
}
int main (int argc, char** argv)
{
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); // Setdisplay mode.
    glutInitWindowPosition (0,0); // Set top-left display-window position.
    glutInitWindowSize (500, 500); // Set display-window width and height.
    glutCreateWindow ("Example 11"); // Create display window.
    glutDisplayFunc (DoNothing); // Send graphics to display window.
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouse);
    glutMainLoop ( ); // Display everything and wait.
}
