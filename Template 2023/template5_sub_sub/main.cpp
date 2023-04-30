#include <windows.h>
#include<GL/glut.h>
#define COLOR 1
#define SPEED 2

#define RED 1
#define GREEN 2
#define BLUE 3
#define BLACKGRAY 4

#define HIGH 1
#define MEDIUM 2
#define LOW 3

#define BLACK 1
#define GRAY  2


float angle = 0.0, inc=0.1;
float vx=0,vy=1,vz=1;
float red=0.0, blue=0.0, green=0.0;
int swidth=500, sheight=500;
void Init(void) {
   	glClearColor(1,1,1,0);
   	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,float(swidth)/float(sheight),0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,3.0,
		      0.0,0.0,0.0,
			  0.0,1.0,0.0);

}
void Display_TeaPot(void)
{ 	glColor3d(red,green,blue); // the rgb color
    glPushMatrix();
   	glRotated(angle,vx,vy,vz);
	glutWireTeapot(1.0); // the teapot
	glPopMatrix();
}
void myDisplay(void) {
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Display_TeaPot();
	angle=angle+inc;
	glutSwapBuffers();
}
void process_Menu_Color(int option) {
	switch (option) {
		case RED : red = 1.0; green = 0.0; blue = 0.0; break;
		case GREEN : red = 0.0; green = 1.0; blue = 0.0; break;
		case BLUE : red = 0.0; green = 0.0; blue = 1.0; break;
				}
}
void process_Menu_BlackGray(int option)
{
switch (option)
{
		case BLACK : red = 0.0; green = 0.0; blue = 0.0; break;
		case GRAY : red = 0.5; green = 0.5; blue = 0.5; break;
}
}
void process_Menu_Speed(int option) {
	switch (option) {
		case LOW : inc=0.1; break;
		case MEDIUM: inc=1;  break;
		case HIGH : inc=10; break;
		}
}
void process_Menu_Events(int option)
{

}
void createGLUTMenus() {
	int submenu3 = glutCreateMenu(process_Menu_BlackGray);
	glutAddMenuEntry("Black",BLACK);
	glutAddMenuEntry("Gray",GRAY);
	int submenu1 = glutCreateMenu(process_Menu_Color);
	glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Green",GREEN);
	glutAddSubMenu("Black/Gray",submenu3);
	int submenu2 = glutCreateMenu(process_Menu_Speed);
	glutAddMenuEntry("Low",LOW);
	glutAddMenuEntry("Medium",MEDIUM);
	glutAddMenuEntry("High",HIGH);
	int menu=glutCreateMenu(NULL);
    glutAddSubMenu("Color",submenu1);
    glutAddSubMenu("Speed",submenu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(swidth,sheight);
    glutCreateWindow("Example 3 new Menu");
	Init();
	glutDisplayFunc(myDisplay);
	glutIdleFunc(myDisplay);
	createGLUTMenus();
	glutMainLoop();}
