//<<<<<<<<<<<<<<<<<<<<<<< Include >>>>>>>>>>>>>>>>>>>>

#include <windows.h>
#include <gl/glut.h>

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>

void myInit(void)
{
//Initialize the settings
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>

void myDisplay(void)
{
//what we are going to display on the screen
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
    glutInitWindowSize(640,480); // set window size
    glutInitWindowPosition(100, 150); // set window position on the screen
    glutCreateWindow("Empty window"); // open the screen window
    glutDisplayFunc(myDisplay); // register the redraw function
    myInit( ); //user defined
    glutMainLoop( ); // OpenGL loop
    return 0;
}
