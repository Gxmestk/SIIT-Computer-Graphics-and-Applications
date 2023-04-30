/*
* Implementing reshape to ensure same aspect ratio between the
* clipping-area and the viewport.
*/
#include <windows.h>
#include <GL/glut.h>
/* Initialize OpenGL Graphics */
void initGL()
{
// Set the background color
    glClearColor(0.0, 0.0, 0.0, 0.0); // Black
}
void my_Display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
// Define shapes enclosed within a pair of glBegin and glEnd
    glBegin(GL_QUADS); // Each set of 4 vertices form a quad
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(-0.8, 0.1); // Define vertices in counter-clockwise (CCW) order
    glVertex2f(-0.2, 0.1); // so that the normal (front-face) is facing you
    glVertex2f(-0.2, 0.7);
    glVertex2f(-0.8, 0.7);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex2f(-0.7, -0.6);
    glVertex2f(-0.1, -0.6);
    glVertex2f(-0.1, 0.0);
    glVertex2f(-0.7, 0.0);
    glColor3f(0.2, 0.2, 0.2); // Dark Gray
    glVertex2f(-0.9, -0.7);
    glColor3f(1.0, 1.0, 1.0); // White
    glVertex2f(-0.5, -0.7);
    glColor3f(0.2, 0.2, 0.2); // Dark Gray
    glVertex2f(-0.5, -0.3);
    glColor3f(1.0, 1.0, 1.0); // White
    glVertex2f(-0.9, -0.3);
    glEnd();
    glBegin(GL_TRIANGLES); // Each set of 3 vertices form a triangle
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex2f(0.1, -0.6);
    glVertex2f(0.7, -0.6);
    glVertex2f(0.4, -0.1);
    glColor3f(1.0, 0.0, 0.0); // Red
    glVertex2f(0.3, -0.4);
    glColor3f(0.0, 1.0, 0.0); // Green
    glVertex2f(0.9, -0.4);
    glColor3f(0.0, 0.0, 1.0); // Blue
    glVertex2f(0.6, -0.9);
    glEnd();
    glBegin(GL_POLYGON); // These vertices form a closed polygon
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glVertex2f(0.4, 0.2);
    glVertex2f(0.6, 0.2);
    glVertex2f(0.7, 0.4);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.4, 0.6);
    glVertex2f(0.3, 0.4);
    glEnd();
    glFlush(); // Render now
}
// Handler for the window re-size event
void reshape(GLint width, GLint height)
{
// Compute aspect ratio of the new window
    if (height == 0)
        height = 1; // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height; //convert to GLfloat
// Set the viewport to cover the new window
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); // projection matrix
    glLoadIdentity(); // Reset the projection matrix
// Set the aspect ratio of the clipping area to match the viewport
    if (width >= height)
    {
// aspect >= 1, set the height from -1 to 1, with the larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else
    {
// aspect < 1, set the width to -1 to 1, with the larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitWindowSize(640, 480); // Set the window's initial width & height - non-square
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("Viewport Transform"); // Create window with the given title
    glutDisplayFunc(my_Display); // Register callback handler for window re-paint event
    glutReshapeFunc(reshape); // Register callback handler for window re-size event
    initGL(); // Our OpenGL initialization
    glutMainLoop(); // Enter the infinite event-processing loop
    return 0;
}
