#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display();
void reshape(int, int);

void init()
{
    glClearColor(0.2, 0.3, 0.8, 1.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200, 100);

    glutInitWindowSize(500, 500);

    glutCreateWindow("Ractangle");

    glutReshapeFunc(reshape);

    glutDisplayFunc(display);

    init();

    glutMainLoop();

    return 0;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    // glPointSize(20);
    glBegin(GL_RECTANGLE);

    
        glColor3f(1.0, 0.0, 0.0);
        glVertex2d(-3, 1);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2d(-4, -1);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(3, -1);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2d(3, 1);

    glEnd();

    glutSwapBuffers();
}

void reshape(int x, int y)
{
    glViewport(0, 0, x, y);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(-10, 10, -10, 10);

    glMatrixMode(GL_MODELVIEW);
}