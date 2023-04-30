#include <windows.h>
#include <GL/glut.h> // (or others, depending on the system in use)
#include <cstdlib>
#include <stdio.h>
bool start=false;
int wx=500,wy=500;
GLfloat minx=-1.,miny=-1.,maxx=1.,maxy=1.;
GLfloat mx,my;//math coordinates
void Draw_Triangle(float cornerX, float cornerY, float size, float color[])
{
    // draw triangle in math coordinates
    glBegin (GL_POLYGON);
    glColor3f (color[0], color[1],color[2]); // Set the drawing color to red.
    glVertex2f(cornerX,cornerY);
    glVertex2f(cornerX+size,cornerY);
    glVertex2f(cornerX+size/2,cornerY+size);
    glEnd ( );
    glFlush ( );
}
void DoNothing(void)
{
    if (!start)
    {
//clear the screen if the window has been changed
        start = true;
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT); // Clear the display window.

    }
    glFlush();
}
void My_Drawing(float X, float Y)//draw triangle with the center at X,Y
{
    float Color[3];// random color
    Color[0]=rand()%1000/1000.0;
    Color[1]=rand()%1000/1000.0;
    Color[2]=rand()%1000/1000.0;
    Draw_Triangle(mx,my,0.3,Color);
}
void Convert(int x, int y)//converts the screen coordinates into the math coordinates
{
    mx=maxx*x/wx+minx*(wx-x)/wx;
    y=wy-y;
    my=maxy*y/wy+miny*(wy-y)/wy;
}
// on mouse
void mouse(int button, int state, int x, int y)
{
    Convert(x,y);//get the new math coordinates mx,my
    if (button == GLUT_LEFT_BUTTON && state== GLUT_DOWN)
        My_Drawing(mx,my);// draw the shape (triangle) in the new math coordinates
}
//on window reshape
void Reshape(GLint width, GLint height)   // GLsizei for non-negative integer
{
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height)
    {
        minx=-1.0 * aspect; //new math limits passed for conversion
        maxx=1.0 * aspect;
        miny=-1.0;
        maxy=1.0;
    }
    else
    {
        minx=-1.0; // new math limits passed for conversion
        maxx=1.0;
        miny=-1.0/aspect;
        maxy=1.0/aspect;
    }
    gluOrtho2D(minx, maxx, miny, maxy); //new math coordinates have been set up
    wx=width;//new wx, wy are passed
    wy=height;
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
}
int main (int argc, char** argv)
{
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
    glutInitWindowPosition (0,0); // Set top-left display-window position.
    glutInitWindowSize (500, 500); // Set display-window width and height.
    glutCreateWindow ("Experimental Window"); // Create display window.
    glutDisplayFunc (DoNothing); // Send graphics to display window.
    glutReshapeFunc(Reshape);
    glutMouseFunc(mouse);
    glutMainLoop ( ); // Display everything and wait.
}
